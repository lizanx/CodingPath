namespace OperatorOverloadingInterface;

class Point : IGenericArithmetic<Point, double>
{
    public double X { get; set; }
    public double Y { get; set; }

    public Point(double x, double y)
    {
        X = x;
        Y = y;
    }

    public Point()
        : this(0.0, 0.0) { }

    public static Point operator +(Point p, double n) => new Point(p.X + n, p.Y + n);

    public static Point operator -(Point p, double n) => new Point(p.X - n, p.Y - n);

    public static Point operator *(Point p, double n) => new Point(p.X * n, p.Y * n);

    public static Point operator /(Point p, double n)
    {
        if (n == 0)
            throw new DivideByZeroException();

        return new Point(p.X / n, p.Y / n);
    }

    public override string ToString() => $"Point({X}, {Y})";
}
