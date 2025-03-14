#include <iostream>
#include <memory>

namespace
{
    class Point
    {
    public:
        Point() : Point{1, 1}
        {
            // std::cout << "Point default initialized to {1, 1}\n";
        }
        Point(int x, int y) : _x{x}, _y{y}
        {
            std::cout << "Point initialized to {" << _x << ", " << _y << "}\n";
        }
        int X() const { return _x; }
        int Y() const { return _y; }

    private:
        int _x;
        int _y;
    };

    std::ostream &operator<<(std::ostream &os, Point p)
    {
        os << "Point{" << p.X() << ", " << p.Y() << "}";
        return os;
    }
}

int main()
{
    // Ctor called
    std::cout << "===== Allocated via 'new' =====\n";
    std::unique_ptr<Point[]> points1{
        new Point[3]{}};
    for (int i{}; i < 3; ++i)
    {
        // This will print "Point{1, 1}" since all points are default initialized.
        std::cout << points1[i] << "\n";
    }

    // Ctor not called
    std::cout << "===== Allocated via 'get_temporary_buffer' =====\n";
    auto [points2, allocatedCnt] = std::get_temporary_buffer<Point>(3);
    if (allocatedCnt != 3)
    {
        std::cerr << "Failed to get temporary buffer!\n";
        return EXIT_FAILURE;
    }
    for (int i{}; i < 3; ++i)
    {
        // This will print "Point{0, 0}"(or some other uninitialized random value) since none of points is initialized!
        std::cout << points2[i] << "\n";
    }
    std::return_temporary_buffer(points2);

    return EXIT_SUCCESS;
}
