// Compile this file with "-fPIC" option.

int add5(int num)
{
    return num + 5;
}

int add10(int num)
{
    int res = add5(num);
    return add5(res);
}

const char *get_hello(void)
{
    return "Hello, world!";
}

static int var = 5;

int get_var(void)
{
    return var;
}

void set_var(int num)
{
    var = num;
}
