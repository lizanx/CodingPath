struct FibonacciIterator
{
public:
    bool operator!=(int x) const;
    int operator*() const;
    FibonacciIterator& operator++();
private:
    int last{1}, current{1};
};

struct FibonacciRange
{
public:
    explicit FibonacciRange(int);
    FibonacciIterator begin() const;
    int end() const;
private:
    int max;
};