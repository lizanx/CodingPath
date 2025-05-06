#include <string>

extern void TestCalcSumTwoInts();
extern void TestCalcMultiplyTwoInts();
extern void TestProgram();

int main(int argc, char *argv[])
{
    using std::string;

    if (argc < 2 || argv[1] == string{"1"})
        TestCalcSumTwoInts();
    if (argc < 2 || argv[1] == string{"2"})
        TestCalcMultiplyTwoInts();
    if (argc < 2 || argv[1] == string{"3"})
        TestProgram();

    return 0;
}
