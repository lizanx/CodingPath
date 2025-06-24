# 1 "SimpleSection.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 406 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "SimpleSection.c" 2
# 11 "SimpleSection.c"
int printf(const char *format, ...);

int global_init_var = 84;
int global_uninit_var;


void func1(int i)
{
    printf("%d\n", i);
}

int main(void)
{
    static int static_var = 85;
    static int static_var2;

    int a = 1;
    int b;
    func1(static_var + static_var2 + a + b);

    return a;
}
