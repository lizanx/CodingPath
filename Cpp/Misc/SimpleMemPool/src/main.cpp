#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace
{
    class MemPool
    {
    public:
        MemPool(size_t blockSize, size_t blockCnt) : _blockSize{blockSize}, _blockCnt{blockCnt}
        {
            _pool.resize(_blockSize * _blockCnt);
            for (size_t i{}; i < _blockCnt; ++i)
            {
                FreeBlock *block = reinterpret_cast<FreeBlock *>(_pool.data() + i * _blockSize);
                block->next = _freeList;
                _freeList = block;
            }
        }

        void *Allocate()
        {
            if (!_freeList)
                throw std::bad_alloc{};

            void *addr = _freeList;
            _freeList = _freeList->next;
            return addr;
        }

        void Free(void *addr)
        {
            FreeBlock *block = static_cast<FreeBlock *>(addr);
            block->next = _freeList;
            _freeList = block;
        }

    private:
        struct FreeBlock
        {
            struct FreeBlock *next;
        };

        size_t _blockSize;
        size_t _blockCnt;
        std::vector<char> _pool{};
        FreeBlock *_freeList{};
    };

    struct DataClass
    {
        int x;
        int y;
    };
} // namespace

int main(int argc, char *argv[])
{
    MemPool memPool{sizeof(DataClass), 10};
    std::vector<DataClass *> allocatedData{};
    for (int i{}; i < 10; ++i)
    {
        void *mem = memPool.Allocate();
        if (!mem)
            throw std::runtime_error{"Failed to allocate memory when i == " + std::to_string(i)};
        DataClass *data = new (mem) DataClass{i, i * 10}; // Only calls constructor, no memory allocation!
        std::cout << "Data[" << i << "]: x = " << data->x << ", y = " << data->y << "\n";
        allocatedData.push_back(data);
    }

    void *exceededMem{};
    try
    {
        exceededMem = memPool.Allocate();
        std::cout << "Successfully allocate memory for exceededMem - 1\n";
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Failed to allocate memory for exceededMem - 1\n";
    }

    memPool.Free(allocatedData.back());
    allocatedData.pop_back();

    try
    {
        exceededMem = memPool.Allocate();
        std::cout << "Successfully allocate memory for exceededMem - 2\n";
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Failed to allocate memory for exceededMem - 2\n";
    }

    for (auto data : allocatedData)
    {
        data->~DataClass(); // Call destructor manually!
        memPool.Free(data);
    }
    allocatedData.clear();
}
