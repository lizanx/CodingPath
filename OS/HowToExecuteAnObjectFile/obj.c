int add5(int num)
{
    return num + 5;
}

int add10(int num)
{
    int res = add5(num);
    return add5(res);
}
