#ifndef _MY_STRING_HEADER_
#define _MY_STRING_HEADER_

#include <iostream>

namespace self_def_str
{
    class String final
    {
    public:
        String();
        String(const char *str);
        String(const String &str);
        String(String &&str);
        ~String();

        String &operator=(const String &str);
        String &operator=(String &&str);
        char &operator[](int i);
        char operator[](int i) const;
        String &operator+=(const String &str);
        String &operator+=(const char *str);

        size_t size() const;
        const char *cStr() const;

    private:
        static constexpr size_t SMALL_STR_SIZE = 15;
        static constexpr size_t SMALL_STR_BUF_SIZE = SMALL_STR_SIZE + 1;
        size_t m_size;
        char m_small_str[SMALL_STR_BUF_SIZE];
        char *m_large_str;
        char *m_str;
    };

    String operator+(const String &s1, const String &s2);
    std::ostream &operator<<(std::ostream &os, const String &str);
}

#endif /* _MY_STRING_HEADER_ */
