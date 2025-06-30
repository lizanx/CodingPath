// Calling convention customization are usually available only on X86.
// On X86_64/ARM, calling convention is defined by system ABI, considered not customizable.
extern void __attribute__((fastcall)) foo(int a, int b);

int main()
{
    foo(1, 3);
    return 0;
}
