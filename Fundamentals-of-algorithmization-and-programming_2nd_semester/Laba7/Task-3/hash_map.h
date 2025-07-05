#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <functional>
#include <string>
#include <vector>
#include "deque.h"

namespace sml {

template <typename Key, typename Value>
class HashMap {
   public:
    HashMap(int size) : size_(size) { buckets_ = new Deque<Entry>[size_]; }

    ~HashMap() { delete[] buckets_; }

    void Insert(const Key& key, const Value& value) {
        int index = Hash(key);

        // check for exist
        bool found = false;

        for (size_t i = 0; i < buckets_[index].size(); ++i) {
            if (buckets_[index][i].key == key) {
                // Replace the value
                buckets_[index][i].value = value;
                found = true;
                break;
            }
        }

        // add new
        if (!found) {
            buckets_[index].push_back(Entry(key, value));
        }
    }

    bool Remove(const Key& key) {
        int index = Hash(key);

        for (size_t i = 0; i < buckets_[index].size(); ++i) {
            if (buckets_[index][i].key == key) {
                // temp deque
                Deque<Entry> temp;

                for (size_t j = 0; j < buckets_[index].size(); ++j) {
                    if (j != i) {
                        temp.push_back(buckets_[index][j]);
                    }
                }

                buckets_[index] = std::move(temp);
                return true;
            }
        }

        return false;
    }

    Value* Find(const Key& key) {
        int index = Hash(key);

        for (size_t i = 0; i < buckets_[index].size(); ++i) {
            if (buckets_[index][i].key == key) {
                return &(buckets_[index][i].value);
            }
        }

        return nullptr;
    }

    size_t GetBucketSize(int bucket_index) const {
        if (bucket_index < 0 || bucket_index >= size_) {
            return 0;
        }
        return buckets_[bucket_index].size();
    }

    Key GetKeyAt(int bucket_index, size_t position) const {
        if (bucket_index < 0 || bucket_index >= size_ ||
            position >= buckets_[bucket_index].size()) {
            throw std::out_of_range("Invalid bucket or position");
        }
        return buckets_[bucket_index][position].key;
    }

    std::vector<Key> GetAllKeys() const {
        std::vector<Key> keys;
        for (int i = 0; i < size_; ++i) {
            for (size_t j = 0; j < buckets_[i].size(); ++j) {
                keys.push_back(buckets_[i][j].key);
            }
        }
        return keys;
    }

    template <typename OutputFunc>
    void Print(OutputFunc output) {
        output("Hash Map Contents:");

        for (int i = 0; i < size_; ++i) {
            std::string bucket_str = "Bucket " + std::to_string(i) + ": [";

            for (size_t j = 0; j < buckets_[i].size(); ++j) {
                bucket_str += std::to_string(buckets_[i][j].key);
                if (j < buckets_[i].size() - 1) {
                    bucket_str += ", ";
                }
            }

            bucket_str += "]";
            output(bucket_str);
        }

        output("");
    }

    int GetSize() const { return size_; }

   protected:
    struct Entry {
        Key key;
        Value value;

        Entry(const Key& k, const Value& v) : key(k), value(v) {}
    };

    // arr of deques
    Deque<Entry>* buckets_;
    int size_;

   private:
    int Hash(const Key& key) const { return std::hash<Key>{}(key) % size_; }
};

}  // namespace sml

#endif	// HASH_MAP_H
