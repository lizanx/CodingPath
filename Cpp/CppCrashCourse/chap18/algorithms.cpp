#include <algorithm>
#include <string>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

const vector<string> languages{
    "C++",
    "C",
    "C#",
    "Python",
    "Go",
    "Kotlin",
    "Rust",
    "HTML",
    "Javascript"
};

TEST_CASE("all_of")
{
    REQUIRE(all_of(languages.cbegin(), languages.cend(),
            [](const auto& str){ return !str.empty(); }));
    REQUIRE_FALSE(all_of(languages.cbegin(), languages.cend(),
            [](const auto& str){ return str[0] == 'C'; }));
}

TEST_CASE("any_of")
{
    REQUIRE(any_of(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.size() <= 1; }));
    REQUIRE_FALSE(any_of(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.empty(); }));
}

TEST_CASE("none_of")
{
    REQUIRE(none_of(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.empty(); }));
    REQUIRE_FALSE(none_of(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.size() > 5; }));
}

TEST_CASE("for_each")
{
    size_t charCnt{};
    for_each(languages.cbegin(), languages.cend(),
            [&charCnt](const string& str){ charCnt += str.size(); });
    REQUIRE(charCnt == 38);
}

TEST_CASE("for_each_n")
{
    size_t charCnt{};
    for_each_n(languages.cbegin(), 3, [&charCnt](const string& str){ charCnt += str.size(); });
    REQUIRE(charCnt == 6);
}

TEST_CASE("find find_if find_if_not")
{
    auto itr = find(languages.cbegin(), languages.cend(), "C#");
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "C#");

    itr = find_if(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.size() > 5; });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Python");

    itr = find_if_not(languages.cbegin(), languages.cend(),
            [](const string& str){
                return str.find('C') != string::npos;
            });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Python");
}

TEST_CASE("find_end")
{
    array<string, 2> searchedElements{ "Go", "Kotlin" };
    array<size_t, 2> searchedLengths{ 4, 4 };

    auto itr = find_end(languages.cbegin(), languages.cend(),
            searchedElements.cbegin(), searchedElements.cend());
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Go");

    itr = find_end(languages.cbegin(), languages.cend(),
            searchedLengths.cbegin(), searchedLengths.cend(),
            [](const string& str, const size_t& size){ return str.size() == size; });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Rust");
}

TEST_CASE("find_first_of")
{
    array<string, 2> androidLanguages{ "Kotlin", "Java" };

    auto itr = find_first_of(languages.cbegin(), languages.cend(),
            androidLanguages.cbegin(), androidLanguages.cend());
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Kotlin");

    array<string, 3> cFamilyLanguages{ "c#", "c++", "c" };
    itr = find_first_of(languages.cbegin(), languages.cend(),
            cFamilyLanguages.cbegin(), cFamilyLanguages.cend(),
            [](const string& s1, const string& s2){
                string lowercaseS1{ s1 };
                transform(lowercaseS1.begin(), lowercaseS1.end(), lowercaseS1.begin(), ::tolower);
                return lowercaseS1 == s2;
            });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "C++");
}

TEST_CASE("adjacent_find")
{
    const auto itr = adjacent_find(languages.cbegin(), languages.cend(),
            [](const string& s1, const string& s2){
                return s1.size() > 1 && s2.size() > 1 && s1[1] == s2[1];
            });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == languages[4]);
}

TEST_CASE("count count_if")
{
    const auto cLangCnt = count(languages.cbegin(), languages.cend(), "C");
    REQUIRE(cLangCnt == 1);

    const auto cStyleCnt = count_if(languages.cbegin(), languages.cend(),
            [](const string& str){ return !str.empty() && str.front() == 'C'; });
    REQUIRE(cStyleCnt == 3);
}

TEST_CASE("mismatch")
{
    const vector<string> cStyle = { "C++", "C", "Csharp" };

    auto itr = mismatch(languages.cbegin(), languages.cend(),
            cStyle.cbegin(), cStyle.cend());
    REQUIRE_FALSE(itr.first == languages.cend());
    REQUIRE_FALSE(itr.second == cStyle.cend());
    REQUIRE(*itr.first == "C#");
    REQUIRE(*itr.second == "Csharp");
}

TEST_CASE("equal")
{
    const vector<string> cStyle = { "c++", "c", "c#" };
    const vector<string> langCopy{ languages };

    REQUIRE_FALSE(equal(languages.cbegin(), languages.cend(), cStyle.cbegin(), cStyle.cend()));
    REQUIRE(equal(languages.cbegin(), languages.cend(), langCopy.cbegin(), langCopy.cend()));
    REQUIRE(equal(languages.cbegin(), languages.cbegin() + 3, cStyle.cbegin(), cStyle.cend(),
            [](const string& s1, const string& s2){ return s1.size() == s2.size(); }));
}

TEST_CASE("is_permutation")
{
    const vector<string> languagesReordered{
        "Go",
        "Kotlin",
        "Rust",
        "Python",
        "HTML",
        "Javascript",
        "C++",
        "C",
        "C#",
    };
    REQUIRE(is_permutation(languages.cbegin(), languages.cend(),
            languagesReordered.cbegin(), languagesReordered.cend()));
}

TEST_CASE("search")
{
    const vector<string> searchLang = {
        "Go",
        "Kotlin",
        "Rust",
    };
    const auto itr = search(languages.cbegin(), languages.cend(),
            searchLang.cbegin(), searchLang.cend());
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Go");
}

TEST_CASE("copy")
{
    vector<string> greeting = { "Hello", "world" };
    vector<string> greetingCopy{};
    copy(greeting.cbegin(), greeting.cend(), back_inserter(greetingCopy));
    REQUIRE(greetingCopy.size() == 2);
    REQUIRE(greetingCopy[0] == greeting[0]);
    REQUIRE(greetingCopy[1] == greeting[1]);
}

TEST_CASE("copy_n")
{
    vector<string> greeting = { "Hello", "world" };
    vector<string> greetingCopy{ "greeting" };
    copy_n(greeting.cbegin(), greeting.size(), back_inserter(greetingCopy));
    REQUIRE(greetingCopy.size() == 3);
    REQUIRE(greetingCopy[0] == "greeting");
    REQUIRE(greetingCopy[1] == greeting[0]);
    REQUIRE(greetingCopy[2] == greeting[1]);
}

TEST_CASE("copy_backward")
{
    vector<string> greeting = { "Hello", "world" };
    vector<string> greetingCopy{ "greeting", "nice", "to", "meet", "you" };
    copy_backward(greeting.cbegin(), greeting.cend(), greetingCopy.end());
    REQUIRE(greetingCopy.size() == 5);
    REQUIRE(greetingCopy[0] == "greeting");
    REQUIRE(greetingCopy[1] == "nice");
    REQUIRE(greetingCopy[2] == "to");
    REQUIRE(greetingCopy[3] == greeting[0]);
    REQUIRE(greetingCopy[4] == greeting[1]);
}

TEST_CASE("move")
{
    struct MoveDetector
    {
        MoveDetector(): owner{ true } {}
        MoveDetector(const MoveDetector&) = delete;
        MoveDetector(MoveDetector&& other): owner{ true }
        {
            other.owner = false;
        }
        MoveDetector& operator=(const MoveDetector&) = delete;
        MoveDetector& operator=(MoveDetector&& other)
        {
            owner = true;
            other.owner = false;
            return *this;
        }

        bool owner;
    };
    
    vector<MoveDetector> detector1(2);
    vector<MoveDetector> detector2(2);
    move(detector1.begin(), detector1.end(), detector2.begin());
    REQUIRE_FALSE(detector1[0].owner);
    REQUIRE_FALSE(detector1[1].owner);
    REQUIRE(detector2[0].owner);
    REQUIRE(detector2[1].owner);
}

TEST_CASE("swap_ranges")
{
    vector<string> s1{ "The", "king", "is", "dead" };
    vector<string> s2{ "Long", "live", "the", "king" };
    swap_ranges(s1.begin(), s1.end(), s2.begin());
    REQUIRE(s1 == vector<string>{ "Long", "live", "the", "king" });
    REQUIRE(s2 == vector<string>{ "The", "king", "is", "dead" });
}

TEST_CASE("transform")
{    
    string greeting{ "Hello" };
    transform(greeting.begin(), greeting.end(), greeting.begin(), ::toupper);
    REQUIRE(greeting == "HELLO");

    vector<string> greetings{ "Hello", "Hi", "Hey" };
    vector<string> names{ "Gavin", "Echo", "Maria" };
    vector<string> greetPeople{};
    transform(greetings.cbegin(), greetings.cend(), names.cbegin(), back_inserter(greetPeople),
            [](const string& greet, const string& name)
            {
                return greet + ", " + name + "!";
            });
    REQUIRE(greetPeople == vector<string>{
        "Hello, Gavin!",
        "Hi, Echo!",
        "Hey, Maria!"
    });
}

TEST_CASE("replace replace_if")
{
    using namespace std::literals::string_literals;
    vector<string> cLangs{ "C", "C++", "C#" };
    replace(cLangs.begin(), cLangs.end(), "C#"s, "Csharp"s);
    REQUIRE(cLangs == vector<string>{ "C", "C++", "Csharp" });
    
    const auto Ctoc = [](const string& s) {
        if (!s.empty() && s[0] == 'C') return true;
        return false;
    };
    replace_if(cLangs.begin(), cLangs.end(), Ctoc, "D"s);
    REQUIRE(cLangs == vector<string>{ "D", "D", "D" });
}

TEST_CASE("fill fill_n")
{
    using namespace std::literals::string_literals;

    vector<string> v1(3);
    fill(v1.begin(), v1.end(), "Hi");
    REQUIRE(v1 == vector<string>{ "Hi", "Hi", "Hi" });

    vector<string> v2{};
    fill_n(back_inserter(v2), 3, "ok");
    REQUIRE(v2 == vector<string>{ "ok", "ok", "ok" });
}

TEST_CASE("generate generate_n")
{
    int i{};
    const auto generator = [&i]() { return ++i; };

    vector<int> v1(3);
    generate(v1.begin(), v1.end(), generator);
    REQUIRE(v1 == vector<int>{ 1, 2, 3 });

    vector<int> v2{};
    generate_n(back_inserter(v2), 3, generator);
    REQUIRE(v2 == vector<int>{ 4, 5, 6 });
}

TEST_CASE("remove remove_if")
{
    string s{ "Nice To Meet You." };

    auto itr = remove(s.begin(), s.end(), ' ');
    s.erase(itr, s.end());
    REQUIRE(s == "NiceToMeetYou.");

    s = "Nice To Meet You.";
    itr = remove_if(s.begin(), s.end(), [](unsigned char c)
        { return c >= 'A' && c <= 'Z'; });
    s.erase(itr, s.end());
    REQUIRE(s == "ice o eet ou.");
}
