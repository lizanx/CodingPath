#include <print>

namespace
{
    class Shape
    {
    public:
        virtual ~Shape() {}
    };

    class Circle : public Shape
    {
    public:
        Circle()
        {
            std::println("Circle()");
        }

        ~Circle() override
        {
            std::println("~Circle()");
        }
    };

    class Rectangle : public Shape
    {
    public:
        Rectangle()
        {
            std::println("Rectangle()");
        }

        ~Rectangle() override
        {
            std::println("~Rectangle()");
        }
    };

    class Result
    {
    public:
        Result()
        {
            std::println("Result()");
        }

        ~Result()
        {
            std::println("~Result()");
        }
    };

    Result ProcessShape(const Shape &s1, const Shape &s2)
    {
        std::println("Processing shapes...");
        return Result{};
    }

    void NormalTmpObjLifetime()
    {
        std::println("<<<<< NormalTmpObjLifetime >>>>>");
        ProcessShape(Circle{}, Rectangle{});
    }

    void ExtendedTmpObjLifetime()
    {
        std::println("<<<<< ExtendedTmpObjLifetime >>>>>");
        const Result &s = ProcessShape(Circle{}, Rectangle{});
    }

}

int main()
{
    NormalTmpObjLifetime();
    std::println();
    ExtendedTmpObjLifetime();

    return 0;
}
