double d = 2.2;
var doubleBytes = BitConverter.GetBytes(d);
foreach (var b in doubleBytes)
{
    Console.WriteLine("Double byte: 0x{0:X}", b);
}

double convertedBackDouble = BitConverter.ToDouble(doubleBytes);
Console.WriteLine("convertedBackDouble = {0}", convertedBackDouble);

byte[] strBytes = new[] { (byte)'A', (byte)'B', (byte)'C' };
string s1 = BitConverter.ToString(strBytes);
Console.WriteLine("s1: {0}", s1);

sbyte[] singedStrBytes = new[] { (sbyte)'A', (sbyte)'B', (sbyte)'C' };
string s2 = ToString(singedStrBytes);
Console.WriteLine("s2: {0}", s2);

unsafe string ToString(sbyte[] data)
{
    string s;
    fixed (sbyte* pdata = data)
    {
        s = new string(pdata);
    }
    return s;
}
