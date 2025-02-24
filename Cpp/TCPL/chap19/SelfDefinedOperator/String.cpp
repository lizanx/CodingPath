#include "String.hpp"
#include <cstring>
#include <stdexcept>

namespace self_def_str
{
    String::String() : m_size{}, m_small_str{}, m_large_str{}, m_str{m_small_str}
    {
    }

    String::String(const char *str) : m_size{strlen((str))}
    {
        if (m_size <= SMALL_STR_SIZE)
        {
            strcpy(m_small_str, str);
            m_small_str[m_size] = '\0';
            m_large_str = nullptr;
            m_str = m_small_str;
        }
        else
        {
            m_large_str = new char[m_size + 1];
            strcpy(m_large_str, str);
            m_large_str[m_size] = '\0';
            m_str = m_large_str;
        }
    }

    String::String(const String &str) : m_size{str.m_size}
    {
        if (m_size <= SMALL_STR_SIZE)
        {
            strcpy(m_small_str, str.m_str);
            m_small_str[m_size] = '\0';
            m_large_str = nullptr;
            m_str = m_small_str;
        }
        else
        {
            m_large_str = new char[m_size + 1];
            strcpy(m_large_str, str.m_large_str);
            m_large_str[m_size] = '\0';
            m_str = m_large_str;
        }
    }

    String::String(String &&str) : m_size{str.m_size}
    {
        if (m_size <= SMALL_STR_SIZE)
        {
            strcpy(m_small_str, str.m_small_str);
            m_small_str[m_size] = '\0';
            m_large_str = nullptr;
            m_str = m_small_str;
        }
        else
        {
            m_large_str = str.m_large_str;
            m_str = m_large_str;
        }

        str.m_large_str = nullptr;
        str.m_small_str[0] = '\0';
        str.m_str = m_small_str;
        str.m_size = 0;
    }

    String::~String()
    {
        if (m_large_str)
            delete[] m_large_str;
    }

    String &String::operator=(const String &str)
    {
        if (m_large_str)
        {
            delete[] m_large_str;
            m_large_str = nullptr;
        }

        m_size = str.m_size;
        if (m_size <= SMALL_STR_SIZE)
        {
            strcpy(m_small_str, str.m_small_str);
            m_small_str[m_size] = '\0';
            m_str = m_small_str;
        }
        else
        {
            m_large_str = new char[m_size + 1];
            strcpy(m_large_str, str.m_large_str);
            m_large_str[m_size] = '\0';
            m_str = m_large_str;
        }

        return *this;
    }

    String &String::operator=(String &&str)
    {
        if (m_large_str)
        {
            delete[] m_large_str;
            m_large_str = nullptr;
        }

        m_size = str.m_size;
        if (m_size <= SMALL_STR_SIZE)
        {
            strcpy(m_small_str, str.m_small_str);
            m_small_str[m_size] = '\0';
            m_str = m_small_str;
        }
        else
        {
            m_large_str = str.m_large_str;
            m_str = m_large_str;
        }

        str.m_large_str = nullptr;
        str.m_small_str[0] = '\0';
        str.m_str = str.m_small_str;
        str.m_size = 0;

        return *this;
    }

    char &String::operator[](int i)
    {
        if (i < 0 || i >= m_size)
            throw std::out_of_range{"String index out of range"};

        return m_str[i];
    }

    char String::operator[](int i) const
    {
        if (i < 0 || i >= m_size)
            throw std::out_of_range{"String index out of range"};

        return m_str[i];
    }

    String &String::operator+=(const String &str)
    {
        if (m_size + str.m_size <= SMALL_STR_SIZE)
        {
            strcpy(m_small_str + m_size, str.m_small_str);
            m_size += str.m_size;
            m_small_str[m_size] = '\0';
        }
        else
        {
            char *new_str = new char[m_size + str.m_size + 1];
            strcpy(new_str, m_str);
            strcpy(new_str + m_size, str.m_str);
            new_str[m_size + str.m_size] = '\0';

            m_size += str.m_size;
            if (m_large_str)
                delete[] m_large_str;
            m_large_str = new_str;
            m_str = m_large_str;
        }

        return *this;
    }

    String &String::operator+=(const char *str)
    {
        String tmp{str};
        *this += tmp;
        return *this;
    }

    size_t String::size() const
    {
        return m_size;
    }

    const char *String::cStr() const
    {
        return m_str;
    }

    String operator+(const String &s1, const String &s2)
    {
        String tmp{s1};
        tmp += s2;
        return tmp;
    }

    std::ostream &operator<<(std::ostream &os, const String &str)
    {
        os << str.cStr();

        return os;
    }
}
