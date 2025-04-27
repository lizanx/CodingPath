extern void FuncDuplicated();
extern void FuncA();
extern void FuncB();

int main()
{
    FuncA();
    FuncB();
    FuncDuplicated();
    return 0;
}
