#include <algorithm>
#include <concepts>
#include <functional>
#include <generator>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <vector>

namespace
{
    const std::vector<std::string> g_vector{
        "Hello", "**txt", "World", "error", "warning",
        "C++", "****"};

    const std::set<std::string> g_set{
        "Hello", "**txt", "World", "error", "warning",
        "C++", "****"};

    template <typename T, typename TPred>
        requires std::invocable<TPred, T> && std::convertible_to<std::invoke_result_t<TPred, T>, bool>
    auto FilterRaw(const std::vector<T> &vec, TPred p)
    {
        std::vector<T> result{};
        for (auto &&element : vec)
            if (p(element))
                result.push_back(element);
        return result;
    }

    template <typename T, typename TPred>
        requires std::invocable<TPred, T> && std::convertible_to<std::invoke_result_t<TPred, T>, bool>
    auto FilterCopyIf(const std::vector<T> &vec, TPred p)
    {
        std::vector<T> result{};
        std::copy_if(std::begin(vec), std::end(vec), std::back_inserter(result), p);
        return result;
    }

    template <typename T, typename TPred>
        requires std::invocable<TPred, T> && std::convertible_to<std::invoke_result_t<TPred, T>, bool>
    auto FilterRemoveCopyIf(const std::vector<T> &vec, TPred p)
    {
        std::vector<T> result{};
        std::remove_copy_if(std::begin(vec), std::end(vec), std::back_inserter(result), std::not_fn(p));
        return result;
    }

    template <typename T, typename TPred>
        requires std::invocable<TPred, T> && std::convertible_to<std::invoke_result_t<TPred, T>, bool>
    auto FilterRemoveErase(const std::vector<T> &vec, TPred p)
    {
        auto result = vec;
        auto iter = std::remove_if(std::begin(result), std::end(result), std::not_fn(p));
        result.erase(iter, std::end(result));
        return result;
    }

    template <typename T, typename TPred>
        requires std::invocable<TPred, T> && std::convertible_to<std::invoke_result_t<TPred, T>, bool>
    auto FilterEraseIf(const std::vector<T> &vec, TPred p)
    {
        auto result = vec;
        std::erase_if(result, std::not_fn(p));
        return result;
    }

    template <typename T, typename TPred>
        requires std::invocable<TPred, T> && std::convertible_to<std::invoke_result_t<TPred, T>, bool>
    auto FilterRangesCopyIf(const std::vector<T> &vec, TPred p)
    {
        std::vector<T> result{};
        std::ranges::copy_if(vec, std::back_inserter(result), p);
        return result;
    }

    template <typename TContainer, typename TPredicate>
        requires std::invocable<TPredicate, typename TContainer::value_type> && std::convertible_to<std::invoke_result_t<TPredicate, typename TContainer::value_type>, bool>
    auto FilterEraseIfGeneric(const TContainer &container, TPredicate p)
    {
        auto result = container;
        std::erase_if(result, std::not_fn(p));
        return result;
    }

    template <typename TContainer, typename TPredicate>
        requires std::invocable<TPredicate, typename TContainer::value_type> && std::convertible_to<std::invoke_result_t<TPredicate, typename TContainer::value_type>, bool>
    auto FilterRangesCopyIfGeneric(const TContainer &container, TPredicate p)
    {
        TContainer result{};
        std::ranges::copy_if(container, std::back_inserter(result), p);
        return result;
    }

    // C++17 SFINAE
    template <typename T, typename = void>
    struct has_push_back_sfinae : std::false_type
    {
    };
    template <typename T>
    struct has_push_back_sfinae<T,
                                std::void_t<
                                    decltype(std::declval<T>().push_back(
                                        std::declval<typename T::value_type>()))>> : std::true_type
    {
    };
    // C++20 concepts
    template <typename T>
    concept has_push_back_concept = requires(T container, typename T::value_type v) {
        container.push_back(v);
    };

    template <typename TContainer, typename TPredicate>
        requires std::invocable<TPredicate, typename TContainer::value_type> && std::convertible_to<std::invoke_result_t<TPredicate, typename TContainer::value_type>, bool>
    auto FilterCopyIfGeneric(const TContainer &container, TPredicate p)
    {
        TContainer result{};
        if constexpr (has_push_back_concept<TContainer>)
            std::copy_if(std::begin(container), std::end(container), std::back_inserter(result), p);
        else
            std::copy_if(std::begin(container), std::end(container), std::inserter(result, std::begin(result)), p);
        return result;
    }

    template <typename T, std::predicate<const T &> TPred>
    auto FilterRangesFilter(const std::vector<T> &vec, TPred p)
    {
        std::vector<T> result{};
        for (const auto &element : (vec | std::views::filter(p)))
            result.push_back(element);
        return result;
    }

    template <typename T, std::predicate<const T &> TPred>
    auto FilterRangesFilterTo(const std::vector<T> &vec, TPred p)
    {
        return vec | std::views::filter(p) | std::ranges::to<std::vector>();
    }

    template <typename TContainer, std::predicate<const typename TContainer::value_type &> TPred>
    auto FilterRangesFilterToGeneric(const TContainer &container, TPred p)
    {
        return container | std::views::filter(p) | std::ranges::to<TContainer>();
    }

    template <typename T, std::predicate<const T &> TPred>
    std::generator<const T &> FilterLazy(const std::vector<T> &vec, TPred p)
    {
        for (const auto &element : vec)
            if (p(element))
                co_yield element;
    }
}

int main()
{
    auto startWithAsterisk = [](const std::string &s)
    {
        return s.starts_with("*");
    };
    const std::vector<std::string> correctVecResult{"**txt", "****"};
    const std::set<std::string> correctSetResult{"**txt", "****"};

    auto filteredVec = FilterRaw(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterRaw");

    filteredVec = FilterCopyIf(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterCopyIf");

    filteredVec = FilterRemoveCopyIf(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterRemoveCopyIf");

    filteredVec = FilterRemoveErase(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterRemoveErase");

    filteredVec = FilterEraseIf(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterEraseIf");

    filteredVec = FilterRangesCopyIf(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterRangesCopyIf");

    filteredVec = FilterEraseIfGeneric(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterEraseIfGeneric - vec");

    auto filteredSet = FilterEraseIfGeneric(g_set, startWithAsterisk);
    if (filteredSet != correctSetResult)
        std::println("Error FilterEraseIfGeneric - set");

    filteredVec = FilterRangesCopyIfGeneric(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterRangesCopyIfGeneric - vec");

    // filteredSet = FilterRangesCopyIfGeneric(g_set, startWithAsterisk);
    // if (filteredSet != correctSetResult)
    //     std::println("Error FilterRangesCopyIfGeneric - set");

    filteredVec = FilterCopyIfGeneric(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterCopyIfGeneric - vec");

    filteredSet = FilterCopyIfGeneric(g_set, startWithAsterisk);
    if (filteredSet != correctSetResult)
        std::println("Error FilterCopyIfGeneric - set");

    filteredVec = FilterRangesFilter(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterRangesFilter");

    filteredVec = FilterRangesFilterTo(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterRangesFilterTo");

    filteredVec = FilterRangesFilterToGeneric(g_vector, startWithAsterisk);
    if (filteredVec != correctVecResult)
        std::println("Error FilterRangesFilterToGeneric - vec");

    filteredSet = FilterRangesFilterToGeneric(g_set, startWithAsterisk);
    if (filteredSet != correctSetResult)
        std::println("Error FilterRangesFilterToGeneric - set");

    std::vector<std::string> result{};
    for (const auto &str : FilterLazy(g_vector, startWithAsterisk))
        result.push_back(str);
    if (result != correctVecResult)
        std::println("Error FilterLazy");

    return 0;
}
