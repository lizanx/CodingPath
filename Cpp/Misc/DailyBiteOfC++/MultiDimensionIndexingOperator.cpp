#include <iostream>
#include <stdexcept>
#include <vector>

namespace
{
    class TwoDimensionArray
    {
    public:
        TwoDimensionArray(size_t rows, size_t cols) : _rows{rows}, _cols{cols}
        {
            _data.resize(_rows * _cols);
            for (int i{}; i < _rows * _cols; ++i)
            {
                _data[i] = i;
            }
        }

        int &operator[](size_t row, size_t col)
        {
            size_t index = row * _cols + col;
            if (index >= _rows * _cols)
                throw std::runtime_error{"Invalid position."};
            return _data[index];
        }

    private:
        size_t _rows;
        size_t _cols;
        std::vector<int> _data;
    };
}

int main()
{
    TwoDimensionArray arr{5, 7};
    std::cout << arr[1, 2] << " " << arr[2, 3] << "\n";
}
