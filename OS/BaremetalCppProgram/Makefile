.PHONY: all
all: sys

.PHONY: run
run: bochsrc sys
	bochs -qf bochsrc

a.img:
	rm -f a.img
	bximage -q -func=create -hd=4096M $@

sys: a.img mbr.bin kernel_final.bin
	dd if=mbr.bin of=a.img conv=notrunc
	dd if=kernel_final.bin of=a.img bs=512 seek=1 conv=notrunc

mbr.bin: mbr.nas
	nasm mbr.nas -o mbr.bin

kernel.o: kernel.nas
	nasm kernel.nas -f elf -o kernel.o

entry.o: entry.c
	gcc -c -m32 -march=i386 -fno-pic -fno-builtin -nostdlib -fno-stack-protector entry.c -o entry.o

asm_func.o: asm_func.nas
	nasm asm_func.nas -f elf -o asm_func.o

kernel_final.out: kernel.o entry.o asm_func.o
	ld -m elf_i386 -Ttext=0x0 kernel.o entry.o asm_func.o -o kernel_final.out

kernel_final.bin: kernel_final.out
	objcopy -I elf32-i386 -S -R ".eh_frame" -R ".comment" -O binary kernel_final.out $@

.PHONY: clean
clean:
	-rm -f .DS_Store
	-rm -f *.bin 
	-rm -f *.img
	-rm -f *.o
	-rm -f *.out
	-rm -f *.gas
