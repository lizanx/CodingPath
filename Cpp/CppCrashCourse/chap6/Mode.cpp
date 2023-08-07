#include <iostream>
#include <map>
#include <concepts>

template<size_t Length, std::integral T>
T mode(const T (&array)[Length])
{
    if (Length <= 0)
        return T{ 0 };

    std::map<T, size_t> counter{};
    for (const auto& e : array)
    {
        if (counter.find(e) == counter.end())
            counter[e] = 1;
        else
            counter[e] += 1;
    }

    T result{ array[0] };
    size_t cnt_max{ 0 };
    for (const auto& [key, value] : counter)
    {
        if (value > cnt_max)
        {
            cnt_max = value;
            result = key;
        }
    }
    return result;
}

int main(void)
{
    int arr1[]{ 1, 2, 3, 3, 3, 2, 1 };
    long arr2[]{ 4, 5, 8, 7, 9, 2, 1, 4, 3, 5, 5 };
    std::cout << mode<sizeof(arr1)/sizeof(arr1[0])>(arr1) << '\n';
    std::cout << mode<sizeof(arr2)/sizeof(arr2[0])>(arr2) << '\n';

    return EXIT_SUCCESS;
}
