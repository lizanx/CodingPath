#include <cstdio>
#include <memory>

static constexpr char msg1[] = "I'm completely operational.";
static constexpr char msg2[] = "Stop, Dave.";


struct Hal {
    Hal(const std::shared_ptr<FILE>& file) : file{ file }
    {
        printf("Constructing Hal: use cnt = %ld\n", file.use_count());
    }
    ~Hal()
    {
        fwrite(msg2, sizeof(*msg2), strlen(msg2), file.get());
        printf("Destructing Hal: use cnt = %ld\n", file.use_count());
    }
    void write_status()
    {
        fwrite(msg1, sizeof(*msg1), strlen(msg1), file.get());
    }
    std::shared_ptr<FILE> file;
};

void my_deleter(FILE* file)
{
    printf("Closing file\n");
    fclose(file);
}

int main(int argc, char *argv[])
{
    std::shared_ptr<FILE> file{ fopen("tmp.txt", "w"), my_deleter };
    Hal h1(file);
    Hal h2(file);
    Hal h3(file);
    Hal h4(file);
    h1.write_status();
    h2.write_status();
    h3.write_status();
    h4.write_status();

    printf("Exiting...\n");

    return 0;
}