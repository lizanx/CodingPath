#include <iostream>
#include <utility>

class IShape
{
public:
    virtual double Area() = 0;
    virtual double Perimeter() = 0;
};

class Rectangle : public IShape
{
public:
    Rectangle(double width, double height);
    double Area() override;
    double Perimeter() override;
    virtual std::pair<double, double> CenterOffset();

private:
    double _width;
    double _height;
};

class Square : public Rectangle
{
public:
    explicit Square(double length);
    double Area() override;
    double Perimeter() override;
    std::pair<double, double> CenterOffset() override;
    double ExposedLength;

private:
    double _length;
};

static std::ostream &operator<<(std::ostream &os, const std::pair<double, double> &data)
{
    os << "{" << data.first << ", " << data.second << "}";
    return os;
}

int main(int argc, char *argv[])
{
    using DimensionMethod = double (IShape::*)();                      // Type pointing to class method
    using PositionMethod = std::pair<double, double> (Rectangle::*)(); // Type pointing to class method
    using DoubleMember = double Square::*;                             // Type pointing to class member data

    DimensionMethod dimensionMethod = &IShape::Area;
    PositionMethod positionMethod = &Rectangle::CenterOffset;
    DoubleMember doubleMember = &Square::ExposedLength;

    Rectangle rectangle{3, 4};
    Square square{2};

    IShape *pShape{&rectangle};
    IShape &refShapeRectangle{rectangle};
    IShape &refShapeSquare{square};
    Rectangle *pRectangle{&rectangle};
    Rectangle &refRectangle{rectangle};

    std::cout << "Area of Rectangle{3, 4}: " << rectangle.Area() << " | "
              << pShape->Area() << " | "
              << refShapeRectangle.Area() << " | "
              << (pShape->*dimensionMethod)() << " | "           // use class member pointer
              << (refShapeRectangle.*dimensionMethod)() << " | " // use class member pointer
              << (pRectangle->*dimensionMethod)() << " | "
              << (refRectangle.*dimensionMethod)() << "\n";

    dimensionMethod = &IShape::Perimeter;
    pShape = &square;
    Square *pSquare{&square};
    std::cout << "Perimeter of Square{2}: " << square.Perimeter() << " | "
              << pShape->Perimeter() << " | "
              << refShapeSquare.Perimeter() << " | "
              << (pShape->*dimensionMethod)() << " | "
              << (pSquare->*dimensionMethod)() << " | "
              << (refShapeSquare.*dimensionMethod)() << "\n";

    std::cout << "Center offset of Rectangle{3, 4}: " << rectangle.CenterOffset() << " | "
              << (pRectangle->*positionMethod)() << " | "
              << (refRectangle.*positionMethod)() << "\n";
    //   << (pShape->*positionMethod)() // doesn't compile

    pRectangle = &square;
    std::cout << "Center offset of Square{2}: " << square.CenterOffset() << " | "
              << (pRectangle->*positionMethod)() << " | "
              //   << (refShapeSquare.*positionMethod)() // doesn't compile
              << (pSquare->*positionMethod)() << "\n";

    pShape = &square;
    pRectangle = &square;
    pSquare = &square;
    Square &refSquare{square};
    std::cout << "Exposed length of Square{2}: " << square.ExposedLength << " | "
              // << pShape->*doubleMember // doesn't compile
              //   << pRectangle->*doubleMember // doesn't compile
              << pSquare->*doubleMember << " | "
              << refSquare.*doubleMember << "\n";
    pSquare->*doubleMember = 3;
    std::cout << "Exposed length after modification: " << square.ExposedLength << " | "
              << pSquare->*doubleMember << " | "
              << refSquare.*doubleMember << "\n";
    refSquare.*doubleMember = 4;
    std::cout << "Exposed length after modification: " << square.ExposedLength << " | "
              << pSquare->*doubleMember << " | "
              << refSquare.*doubleMember << "\n";
}

Rectangle::Rectangle(double width, double height) : _width{width}, _height{height}
{
}

double Rectangle::Area()
{
    // std::cout << "Calculating area of rectangle...\n";
    return _width * _height;
}

double Rectangle::Perimeter()
{
    // std::cout << "Calculating perimeter of rectangle...\n";
    return (_width + _height) * 2;
}

std::pair<double, double> Rectangle::CenterOffset()
{
    // std::cout << "Calculating center offset of rectangle...\n";
    return {_width / 2, _height / 2};
}

Square::Square(double length) : Rectangle{0, 0}, ExposedLength{length}, _length{length}
{
}

double Square::Area()
{
    // std::cout << "Calculating area of square...\n";
    return _length * _length;
}

double Square::Perimeter()
{
    // std::cout << "Calculating perimeter of square...\n";
    return _length * 4;
}

std::pair<double, double> Square::CenterOffset()
{
    // std::cout << "Calculating center offset of square...\n";
    return {_length / 2, _length / 2};
}
