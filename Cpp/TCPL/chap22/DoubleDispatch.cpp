#include <iostream>
#include <vector>

class Rectangle;
class Circle;

class IShape
{
public:
    virtual bool Intersect(const IShape &) const = 0;
    virtual bool Intersect(const Rectangle &) const = 0;
    virtual bool Intersect(const Circle &) const = 0;
    virtual ~IShape();
};

class Rectangle : public IShape
{
public:
    bool Intersect(const IShape &) const override;
    bool Intersect(const Rectangle &) const override;
    bool Intersect(const Circle &) const override;
};

class Circle : public IShape
{
public:
    bool Intersect(const IShape &) const override;
    bool Intersect(const Rectangle &) const override;
    bool Intersect(const Circle &) const override;
};

int main(int argc, char *argv[])
{
    Rectangle rectangle{};
    Circle circle{};
    std::vector<std::pair<IShape *, IShape *>> shapePairs{
        {&rectangle, &rectangle},
        {&circle, &circle},
        {&rectangle, &circle},
        {&circle, &rectangle}};

    for (auto shapePair : shapePairs)
    {
        std::cout << ">>>>>\n";
        shapePair.first->Intersect(*shapePair.second);
        std::cout << "<<<<<\n\n";
    }
}

bool Rectangle::Intersect(const IShape &shape) const
{
    std::cout << "Rectangle::Intersect(IShape)\n";
    return shape.Intersect(*this);
}

bool Rectangle::Intersect(const Rectangle &) const
{
    std::cout << "Rectangle::Intersect(Rectangle)\n";
    return true;
}

bool Rectangle::Intersect(const Circle &) const
{
    std::cout << "Rectangle::Intersect(Circle)\n";
    return true;
}

bool Circle::Intersect(const IShape &shape) const
{
    std::cout << "Circle::Intersect(IShape)\n";
    return shape.Intersect(*this);
}

bool Circle::Intersect(const Rectangle &) const
{
    std::cout << "Circle::Intersect(Rectangle)\n";
    return true;
}

bool Circle::Intersect(const Circle &) const
{
    std::cout << "Circle::Intersect(Circle)\n";
    return true;
}

IShape::~IShape()
{
}
