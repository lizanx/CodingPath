#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <syncstream>
#include <random>
#include <shared_mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace
{
    template <typename TKey, typename TValue, typename THash = std::hash<TKey>>
    class ThreadSafeHashTable
    {
    public:
        using KeyType = TKey;
        using ValueType = TValue;
        using HashType = THash;

        ThreadSafeHashTable(unsigned bucketsCnt = 19, const THash &hasher = THash{}) : _buckets(bucketsCnt), _hasher{hasher}
        {
            for (unsigned i{}; i < _buckets.size(); ++i)
                _buckets[i] = std::make_unique<Bucket>();
        }
        ThreadSafeHashTable(const ThreadSafeHashTable &) = delete;
        ThreadSafeHashTable &operator=(const ThreadSafeHashTable &) = delete;

        TValue ValueFor(const TKey &key, const TValue &defaultValue = TValue{}) const
        {
            return GetBucket(key).ValueFor(key, defaultValue);
        }

        void AddOrUpdateMapping(const TKey &key, const TValue &value)
        {
            GetBucket(key).AddOrUpdateMapping(key, value);
        }

        void RemoveMapping(const TKey &key)
        {
            GetBucket(key).RemoveMapping(key);
        }

    private:
        class Bucket
        {
        public:
            TValue ValueFor(const TKey &key, const TValue &defaultValue) const
            {
                std::shared_lock lck{_mutex};
                auto entry = FindEntryFor(key);
                return entry == _data.end() ? defaultValue : entry->second;
            }

            void AddOrUpdateMapping(const TKey &key, const TValue &value)
            {
                std::unique_lock lck{_mutex};
                auto entry = FindEntryFor(key);
                if (entry == _data.end())
                {
                    _data.push_back({key, value});
                }
                else
                {
                    entry->second = value;
                }
            }

            void RemoveMapping(const TKey &key)
            {
                std::unique_lock lck{_mutex};
                auto entry = FindEntryFor(key);
                if (entry != _data.end())
                {
                    _data.erase(entry);
                }
            }

        private:
            using BucketValueType = std::pair<TKey, TValue>;
            using BucketDataType = std::list<BucketValueType>;
            using BucketIteratorType = BucketDataType::iterator;
            BucketDataType _data{};
            mutable std::shared_mutex _mutex{};

            auto FindEntryFor(const TKey &key) const -> decltype(_data.cbegin())
            {
                return std::find_if(_data.begin(), _data.end(), [&key](const BucketValueType &item)
                                    { return item.first == key; });
            }

            BucketIteratorType FindEntryFor(const TKey &key)
            {
                return std::find_if(_data.begin(), _data.end(), [&key](const BucketValueType &item)
                                    { return item.first == key; });
            }
        };

        std::vector<std::unique_ptr<Bucket>> _buckets;
        THash _hasher;

        Bucket &GetBucket(const TKey &key) const
        {
            return *_buckets[_hasher(key) % _buckets.size()];
        }
    };

    int RandInt(int low, int high)
    {
        static std::random_device rd{};
        static std::mt19937 generator{};
        std::uniform_int_distribution distribution{low, high};
        return distribution(generator);
    }
}

int main(int argc, char *argv[])
{
    using std::string;
    std::osyncstream oss{std::cout};
    auto f = [&oss](ThreadSafeHashTable<string, int> &hashTable)
    {
        int loopCnt{};
        while (++loopCnt <= 10)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds{1});

            int operation = RandInt(1, 3);
            int value = RandInt(0, 9);
            string key = std::format("{}", value);
            switch (operation)
            {
            case 1: // Find the key
            {
                int found = hashTable.ValueFor(key, -1);
                if (found >= 0)
                    oss << "✔️ " << found << "\n"; // Exist
                else
                    oss << "⛔ " << value << "\n"; // Non-exist
                break;
            }
            case 2: // Add or update
                hashTable.AddOrUpdateMapping(key, value);
                oss << "+ " << value << "\n";
                break;
            case 3: // Remove
                hashTable.RemoveMapping(key);
                oss << "- " << value << "\n";
                break;
            default:
                oss << "!!!! Unknown operation " << operation << "\n";
            }
        }
    };
    ThreadSafeHashTable<string, int> hashTable{};
    std::vector<std::thread> ts(4);
    for (unsigned i{}; i < ts.size(); ++i)
        ts[i] = std::thread{f, std::ref(hashTable)};
    for (unsigned i{}; i < ts.size(); ++i)
        ts[i].join();

    oss << "\n--- Finished calling f ---\n";
    for (int i{}; i < 10; ++i)
    {
        string key = std::format("{}", i);
        int foundValue = hashTable.ValueFor(key, -1);
        if (foundValue >= 0)
            oss << "✔️ " << foundValue << "\n";
    }

    return 0;
}
