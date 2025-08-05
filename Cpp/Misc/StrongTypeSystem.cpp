#include <iostream>

namespace
{
using UserID = int;

template <typename TUnderlying, typename TTag> class StrongTypeWrapper
{
  public:
    explicit StrongTypeWrapper(TUnderlying value) : _value{value}
    {
    }
    explicit operator TUnderlying() const
    {
        return _value;
    }
    TUnderlying get() const
    {
        return _value;
    }
    void set(TUnderlying value)
    {
        _value = value;
    }

  private:
    TUnderlying _value;
};
} // namespace

int main()
{
    UserID uid{1};
    uid = 5;     // OK: implicitly converted from int
    int u = uid; // OK: implicit conversion to int

    struct GroupIdTag
    {
    };
    using GroupID = StrongTypeWrapper<int, GroupIdTag>;
    GroupID gid{1};
    std::cout << "gid = " << gid.get() << "\n";
    std::cout << "gid = " << static_cast<int>(gid) << "\n";
    // gid = 2; // Compiling error: no implicit conversion.
    // int g = gid; // Compiling error: no implicit conversion.
    int g1 = static_cast<int>(gid);
    int g2 = gid.get();
    std::cout << "g1 = " << g1 << ", g2 = " << g2 << "\n";
}
