class DefaultClass
{
    public DefaultClass()
    {
        val = 1;
    }

    public override string ToString()
    {
        return $"DefaultClass: val = {val}";
    }

    public int val;
}

struct DefaultStruct
{
    public DefaultStruct()
    {
        val = 2;
    }

    public override string ToString()
    {
        return $"DefaultStruct: val = {val}";
    }

    public int val;
}
