#include <iostream>
#include <exception>

template<size_t Length, typename T>
T max_before(const T (&arr)[Length], size_t end_index)
{
    if (end_index > Length)
        throw std::out_of_range{ "Fail" };

    T max{ arr[0] };
    for (size_t i = 1; i < end_index; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

template<size_t EndIndex, size_t Length, typename T>
T static_max_before(const T (&arr)[Length])
{
    static_assert(EndIndex <= Length, "Out of range index");

    T max{ arr[0] };
    for (size_t i = 1; i < EndIndex; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}


int main(void)
{
    int arr[] { 1, 2, 3, 4, 5, 6, 7 };
    std::cout << max_before<7>(arr, 4) << std::endl;
    // std::cout << max_before<7>(arr, 8) << std::endl;

    std::cout << static_max_before<6, 7>(arr) << std::endl;
    // std::cout << static_max_before<6, 7>(arr) << std::endl;
    
    return EXIT_SUCCESS;
}
