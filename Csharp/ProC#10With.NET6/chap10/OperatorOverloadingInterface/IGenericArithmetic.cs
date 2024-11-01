namespace OperatorOverloadingInterface;

interface IGenericArithmetic<T, TOp>
    where T : IGenericArithmetic<T, TOp>
{
    static abstract T operator +(T a, TOp b);

    static abstract T operator -(T a, TOp b);

    static abstract T operator *(T a, TOp b);

    static abstract T operator /(T a, TOp b);
}
