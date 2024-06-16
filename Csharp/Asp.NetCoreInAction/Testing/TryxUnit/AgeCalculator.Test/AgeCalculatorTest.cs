using System.Collections;
using AgeCalculator;

namespace AgeCalculator.Test;

public class AgeCalculatorTest
{
    [Fact]
    public void TestYears()
    {
        var birth = new DateTime(1994, 9, 22);
        var ageCaculator = new AgeCalculator(birth);

        var years = ageCaculator.Years;
        var expected = DateTime.Now.Year - birth.Year;

        Assert.Equal(expected, years);
    }

    [Theory]
    [InlineData(1994, 9, 22, 30)]
    [InlineData(1997, 11, 22, 27)]
    [ClassData(typeof(AgeCalculatorClassData))]
    [MemberData(nameof(TestData))]
    public void TestYears_Theory(int year, int month, int day, int expected)
    {
        DateTime birth = new(year, month, day);
        var ageCaculator = new AgeCalculator(birth);

        var years = ageCaculator.Years;

        Assert.Equal(expected, years);
    }

    public class AgeCalculatorClassData : IEnumerable<object[]>
    {
        public IEnumerator<object[]> GetEnumerator()
        {
            yield return [2000, 4, 20, 24];
            yield return [1970, 2, 21, 54];
            yield return [1949, 10, 1, 75];
        }

        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    }

    public static IEnumerable<object[]> TestData =>
    [
        [1999, 2, 19, 25],
        [2009, 8, 10, 15],
        [2001, 6, 5, 23]
    ];
}