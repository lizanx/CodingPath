#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>
#include <errno.h>

/* from https://elixir.bootlin.com/linux/v5.11.6/source/arch/x86/include/asm/elf.h#L51 */
#define R_X86_64_PLT32 4

typedef union
{
    const Elf64_Ehdr *hdr;
    const uint8_t *base;
} objhdr;

/* obj.o memory address */
static objhdr obj;

/* sections table */
static const Elf64_Shdr *sections;
static const char *shstrtab;

/* symbols table */
static const Elf64_Sym *symbols;
/* number of entries in the symbols table */
static int num_symbols;
static const char *strtab;

static uint64_t page_size;

/* runtime base address of the imported code */
static uint8_t *text_runtime_base;

static inline uint64_t page_align(uint64_t n)
{
    return (n + page_size - 1) & ~(page_size - 1);
}

static const Elf64_Shdr *lookup_section(const char *name)
{
    size_t name_len = strlen(name);

    // Number of entries in the sections table is encoded in the ELF header
    for (Elf64_Half i = 0; i < obj.hdr->e_shnum; ++i)
    {
        // Sections table entry doesn't contain the string name of the section.
        // Instead, the 'sh_name' parameter is an offset in the '.shstrtab' section,
        // which points to a string name.
        const char *section_name = shstrtab + sections[i].sh_name;
        size_t section_name_len = strlen(section_name);

        if (name_len == section_name_len && strcmp(name, section_name) == 0)
        {
            // Ignore sections with 0 size.
            if (sections[i].sh_size)
                return sections + i;
        }
    }

    return NULL;
}

static void *lookup_function(const char *name)
{
    size_t name_len = strlen(name);

    // Loop through all symbols in the symbol table.
    for (int i = 0; i < num_symbols; ++i)
    {
        // Consider only function symbols.
        if (ELF64_ST_TYPE(symbols[i].st_info) == STT_FUNC)
        {
            // Symbol table entry doesn't contain the string name of the symbol.
            // Instead, the 'st_name' parameter is an offset in the '.strtab' section,
            // which points to a string name.
            const char *function_name = strtab + symbols[i].st_name;
            size_t function_name_len = strlen(function_name);

            if (name_len == function_name_len && strcmp(name, function_name) == 0)
            {
                // 'st_value' is an offset in bytes of the function from the beginning of the '.text' section.
                return text_runtime_base + symbols[i].st_value;
            }
        }
    }

    return NULL;
}

static uint8_t *section_runtime_base(const Elf64_Shdr *section)
{
    const char *section_name = shstrtab + section->sh_name;
    size_t section_name_len = strlen(section_name);

    if (strlen(".text") == section_name_len && strcmp(section_name, ".text") == 0)
        return text_runtime_base;

    fprintf(stderr, "No runtime base address for %s\n", section_name);
    exit(ENOENT);
}

static void do_text_relocations()
{
    // We actually cheat here - the name '.rela.text' is a convention, but not a rule:
    // to figure out which section should be patched by these relocations, we would need
    // to examine the rela_text_hdr, but we skip it for simplicity.
    const Elf64_Shdr *rela_text_hdr = lookup_section(".rela.text");
    if (!rela_text_hdr)
    {
        fputs("Failed to find '.rela.text' section.\n", stderr);
        exit(ENOEXEC);
    }

    int num_relocations = rela_text_hdr->sh_size / rela_text_hdr->sh_entsize;
    const Elf64_Rela *relocations = (Elf64_Rela *)(obj.base + rela_text_hdr->sh_offset);

    for (int i = 0; i < num_relocations; ++i)
    {
        int symbol_idx = ELF64_R_SYM(relocations[i].r_info);
        int type = ELF64_R_TYPE(relocations[i].r_info);

        // Where to patch '.text'.
        uint8_t *patch_offset = text_runtime_base + relocations[i].r_offset;
        // Symbol, with respect to which the relocation is performed.
        uint8_t *symbol_address = section_runtime_base(&sections[symbols[symbol_idx].st_shndx]) + symbols[symbol_idx].st_value;

        switch (type)
        {
        case R_X86_64_PLT32:
            // L + A - P, 32 bit output.
            *((uint32_t *)patch_offset) = symbol_address + relocations[i].r_addend - patch_offset;
            printf("Calculated relocation: 0x%08x\n", *((uint32_t *)patch_offset));
            break;
        default:
            break;
        }
    }
}

static void load_obj(void)
{
    struct stat st;

    int fd = open("obj.o", O_RDONLY);
    if (fd <= 0)
    {
        perror("Cannot open obj.o\n");
        exit(errno);
    }

    if (fstat(fd, &st))
    {
        perror("Failed to get obj.o info.\n");
        exit(errno);
    }

    obj.base = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (obj.base == MAP_FAILED)
    {
        perror("Maping obj.o failed.\n");
        exit(errno);
    }

    close(fd);
}

static void parse_obj(void)
{
    // The sections table offset is encoded in ELF header.
    sections = (const Elf64_Shdr *)(obj.base + obj.hdr->e_shoff);
    // Index of ".shstrtab" in the sections table is encoded in the ELF header,
    // so we can find it without actually using a name lookup.
    shstrtab = (const char *)(obj.base + sections[obj.hdr->e_shstrndx].sh_offset);

    // Find the '.symtab' entry in the sections table.
    const Elf64_Shdr *symtab_hdr = lookup_section(".symtab");
    if (!symtab_hdr)
    {
        fputs("Failed to find '.symtab'\n", stderr);
        exit(ENOEXEC);
    }
    symbols = (const Elf64_Sym *)(obj.base + symtab_hdr->sh_offset);
    num_symbols = symtab_hdr->sh_size / symtab_hdr->sh_entsize;

    const Elf64_Shdr *strtab_hdr = lookup_section(".strtab");
    if (!strtab_hdr)
    {
        fputs("Failed to find '.strtab'\n", stderr);
        exit(ENOEXEC);
    }
    strtab = (const char *)(obj.base + strtab_hdr->sh_offset);

    page_size = sysconf(_SC_PAGESIZE);

    // Find the '.text' entry in the sections table.
    const Elf64_Shdr *text_hdr = lookup_section(".text");
    if (!text_hdr)
    {
        fputs("Failed to find '.text'\n", stderr);
        exit(ENOEXEC);
    }

    // Allocate memory for '.text' copy(round it up to whole pages).
    text_runtime_base = mmap(NULL, page_align(text_hdr->sh_size),
                             PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (text_runtime_base == MAP_FAILED)
    {
        perror("Failed to allocate memory for '.text'.\n");
        exit(errno);
    }

    // Copy contents of ".text" section from the ELF file.
    memcpy(text_runtime_base, obj.base + text_hdr->sh_offset, text_hdr->sh_size);

    do_text_relocations();

    // Make the ".text" copy readonly and executable.
    if (mprotect(text_runtime_base, page_align(text_hdr->sh_size), PROT_READ | PROT_EXEC))
    {
        perror("Failed to make '.text' executable.\n");
        exit(errno);
    }
}

static void execute_funcs(void)
{
    int (*add5)(int);
    int (*add10)(int);

    add5 = lookup_function("add5");
    if (!add5)
    {
        fputs("Failed to find add5 function.\n", stderr);
        exit(ENOENT);
    }
    puts("Executing add5...");
    printf("add5(%d) = %d\n", 42, add5(42));

    add10 = lookup_function("add10");
    if (!add10)
    {
        fputs("Failed to find add10 function.\n", stderr);
        exit(ENOENT);
    }
    puts("Executing add10...");
    printf("add10(%d) = %d\n", 42, add10(42));
}

int main(void)
{
    load_obj();
    parse_obj();
    execute_funcs();

    return EXIT_SUCCESS;
}
