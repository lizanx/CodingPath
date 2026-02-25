#include <algorithm>
#include <print>
#include <utility>
#include <vector>

namespace
{
    class DataObj
    {
    private:
        char _value;

    public:
        DataObj(char value);
        ~DataObj() = default;
        DataObj(const DataObj &other);
        DataObj(DataObj &&other);
        DataObj &operator=(const DataObj &other);
        DataObj &operator=(DataObj &&other);

        char GetValue() const;
    };

    DataObj::DataObj(char value) : _value{value}
    {
    }

    DataObj::DataObj(const DataObj &other)
    {
        std::println("<Copy ctor>");
        _value = other._value;
    }

    DataObj::DataObj(DataObj &&other)
    {
        std::println("<Move ctor>");
        _value = other._value;
        other._value = '-';
    }

    DataObj &DataObj::operator=(const DataObj &other)
    {
        std::println("<Copy assignment>");
        _value = other._value;
        return *this;
    }

    DataObj &DataObj::operator=(DataObj &&other)
    {
        std::println("<Move assignment>");
        _value = other._value;
        other._value = '-';
        return *this;
    }

    char DataObj::GetValue() const
    {
        return _value;
    }
}

int main()
{
    std::vector<int> intVec{1, 2, 3, 4, 5, 6, 7};
    auto iter = std::shift_left(std::begin(intVec), std::end(intVec), 3);
    if (iter != std::end(intVec))
        std::println("Shift int vector returned: {}", *iter);
    std::println("IntVec:");
    for (const int i : intVec)
        std::println("\t{}", i);
    std::println();

    std::vector<DataObj> dataVec{};
    dataVec.emplace_back('a');
    dataVec.emplace_back('b');
    dataVec.emplace_back('c');
    dataVec.emplace_back('d');
    dataVec.emplace_back('e');
    dataVec.emplace_back('f');
    dataVec.emplace_back('g');
    auto dataIter = std::shift_right(std::begin(dataVec), std::end(dataVec), 5);
    if (dataIter != std::end(dataVec))
        std::println("Shift data-obj vector returned: {}", dataIter->GetValue());
    std::println("DataVec:");
    for (const auto &data : dataVec)
        std::println("\t{}", data.GetValue());
}
