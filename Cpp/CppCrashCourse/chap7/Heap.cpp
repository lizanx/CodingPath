#include <iostream>
#include <new>

struct Bucket
{
    static constexpr size_t size{ 4096 };
    std::byte data[size];
};

struct Heap
{
    void* allocate(size_t sz)
    {
        if (sz > bucket_cnt)
            throw std::bad_alloc{};
        for (size_t i = 0; i < bucket_cnt; i++)
        {
            if (!used[i])
            {
                used[i] = true;
                return buckets[i].data;
            }
        }
        throw std::bad_alloc{};
    }

    void free(void *p)
    {
        for (size_t i = 0; i < bucket_cnt; i++)
        {
            if (buckets[i].data == p)
            {
                used[i] = false;
                return;
            }
        }
    }

// private:
    static constexpr size_t bucket_cnt{ 10 };
    Bucket buckets[bucket_cnt]{};
    bool used[bucket_cnt]{};
};

static Heap heap{};

void* operator new(size_t sz)
{
    return heap.allocate(sz);
}

void operator delete(void *ptr)
{
    heap.free(ptr);
}

int main(void)
{
    printf("Buckets: %p\n", heap.buckets);

    auto breakfast = new unsigned int{ 0xC0FFEE };
    auto dinner = new unsigned int { 0xDEADBEEF };
    printf("Breakfast: %p 0x%x\n", breakfast, *breakfast);
    printf("Dinner: %p 0x%x\n", dinner, *dinner);
    delete breakfast;
    delete dinner;

    try
    {
        while (true)
        {
            new char;
            printf("Allocated a char.\n");
        }
    }
    catch (const std::bad_alloc&)
    {
        printf("std::bad_alloc caught.\n");
    }
}