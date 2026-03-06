#include <cassert>
#include <print>
#include <spanstream>
#include <vector>

int main()
{
    {
        char buf[] = "10 20 30";
        std::spanstream ss{buf};
        int a{}, b{}, c{};
        ss >> a >> b >> c;
        assert(a == 10);
        assert(b == 20);
        assert(c == 30);
    }

    {
        std::vector<char> data(1024 * 8, '\0');
        std::spanstream ss{data};
        ss << 10 << ' ' << 20 << ' ' << 30;
        assert(std::string{"10 20 30"} == std::string{data.data()});
    }

    {
        // Handle errors -- cumbersome
        std::vector<char> buf(8, '\0');
        std::spanstream ss{buf};
        ss << 1000 << ' '; // len == 5
        auto pos = ss.tellp();
        ss << 1000; // !! no enough space
        if (!ss.good())
        {
            ss.clear();    // clear error flags
            ss.seekp(pos); // seek back
        }
        else
        {
            assert(false);
        }
        while (ss << 'X')
        {
        }
        {
            char strBuf[9] = {'\0'};
            for (size_t i{}; i < std::min(buf.size(), sizeof(strBuf)); ++i)
            {
                std::println("char: {}", buf[i]);
                strBuf[i] = buf[i];
            }

            // Don't construct string directly from 'buf'! It's not '\0'-ended, which causes UB!!!
            assert(std::string{strBuf} == std::string{"1000 XXX"});
        }
    }
}
