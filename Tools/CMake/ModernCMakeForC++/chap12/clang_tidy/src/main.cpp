extern int StartProgram(int argc, const char *argv[]);

int main(int argc, char *argv[])
{
    return StartProgram(argc, (const char **)argv);
}
