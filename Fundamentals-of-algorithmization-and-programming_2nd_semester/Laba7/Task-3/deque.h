#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>

constexpr size_t kBucketSize = 64;
constexpr size_t kGrowFactor = 2;

namespace sml {
template <typename T>
class Deque {
    struct Bucket {
        alignas(T) uint8_t data[sizeof(T) * kBucketSize];

        Bucket() { std::memset(data, 0, sizeof(data)); }

        ~Bucket() {}
    };

    Bucket** buckets_;
    size_t capacity_;
    size_t size_;
    struct DeqIndx {
        size_t bucket;
        size_t index;
    } first_, last_;  // indx of front and end of container

    // ptr to element at a specific bucket, indx
    T* element_at(size_t bucket, size_t index) {
        return reinterpret_cast<T*>(&buckets_[bucket]->data[index * sizeof(T)]);
    }

    const T* element_at(size_t bucket, size_t index) const {
        return reinterpret_cast<const T*>(
            &buckets_[bucket]->data[index * sizeof(T)]);
    }


    void advance_back() {
        if (++last_.index == kBucketSize) {
            last_.index = 0;
            ++last_.bucket;

            if (last_.bucket >= capacity_) {
                increase_size();
            }
        }
    }


    void advance_front() {
        if (++first_.index == kBucketSize) {
            first_.index = 0;
            ++first_.bucket;

            if (first_.bucket >= capacity_) {
                increase_size();
            }
        }
    }


    void retreat_front() {
        if (first_.index == 0) {
            first_.index = kBucketSize - 1;
            first_.bucket =
                (first_.bucket == 0 ? capacity_ - 1 : first_.bucket - 1);
        } else {
            --first_.index;
        }
    }


    void retreat_back() {
        if (last_.index == 0) {
            last_.index = kBucketSize - 1;
            last_.bucket =
                (last_.bucket == 0 ? capacity_ - 1 : last_.bucket - 1);
        } else {
            --last_.index;
        }
    }


    void allocate_buckets(size_t new_cap) {
        buckets_ = new Bucket*[new_cap];
        for (size_t i = 0; i < new_cap; ++i) {
            buckets_[i] = new Bucket();
        }
    }


    void increase_size() {
        size_t old_cap = capacity_;
        size_t used_buckets = (size_ + kBucketSize - 1) / kBucketSize;
        capacity_ *= kGrowFactor;
        Bucket** new_buckets = new Bucket*[capacity_]();

        size_t mid = (capacity_ - used_buckets) / 2;

        for (size_t i = 0; i < used_buckets; ++i) {
            size_t old_idx = (first_.bucket + i) % old_cap;
            new_buckets[mid + i] = buckets_[old_idx];
        }
        for (size_t i = 0; i < capacity_; ++i) {
            if (!new_buckets[i]) {
                new_buckets[i] = new Bucket();
            }
        }

        delete[] buckets_;
        buckets_ = new_buckets;
        first_.bucket = mid;
        last_.bucket = mid + used_buckets - 1;
    }


   public:
    Deque() : capacity_(2), size_(0) {
        allocate_buckets(capacity_);
        first_ = {0, 0};
        last_ = {0, 0};
    }

    // copy constructor
    Deque(const Deque& other) : capacity_(other.capacity_), size_(other.size_) {
        allocate_buckets(capacity_);

        first_.bucket = other.first_.bucket;
        first_.index = other.first_.index;
        last_.bucket = other.last_.bucket;
        last_.index = other.last_.index;

        size_t src_bucket = other.first_.bucket;
        size_t src_index = other.first_.index;
        size_t dst_bucket = first_.bucket;
        size_t dst_index = first_.index;


        for (size_t i = 0; i < size_; ++i) {
            new (element_at(dst_bucket, dst_index))
                T(*other.element_at(src_bucket, src_index));

            if (++src_index == kBucketSize) {
                src_index = 0;
                ++src_bucket;
            }

            if (++dst_index == kBucketSize) {
                dst_index = 0;
                ++dst_bucket;
            }
        }
    }

    // move constructor
    Deque(Deque&& other) noexcept
        : buckets_(other.buckets_),
          capacity_(other.capacity_),
          size_(other.size_),
          first_(other.first_),


          last_(other.last_) {
        other.buckets_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    //copy assigment operator
    Deque& operator=(const Deque& other) {


        if (this != &other) {
            Deque tmp(other);
            swap(tmp);
        }
        return *this;
    }

    //move assigment operator
    Deque& operator=(Deque&& other) noexcept {


        if (this != &other) {
            clear();
            for (size_t i = 0; i < capacity_; ++i) {
                delete buckets_[i];
            }
            delete[] buckets_;

            buckets_ = other.buckets_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            first_ = other.first_;
            last_ = other.last_;

            other.buckets_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    ~Deque() {
        clear();


        for (size_t i = 0; i < capacity_; ++i) {
            delete buckets_[i];
        }
        delete[] buckets_;
    }


    void clear() {
        // fix needed
        while (!empty()) {
            pop_back();
        }
    }


    void push_back(const T& value) {
        if (size_ == capacity_ * kBucketSize) {
            increase_size();
        }

        new (element_at(last_.bucket, last_.index)) T(value);
        ++size_;
        advance_back();
    }


    void push_front(const T& value) {
        if (size_ == capacity_ * kBucketSize) {
            increase_size();
        }

        retreat_front();
        new (element_at(first_.bucket, first_.index)) T(value);
        ++size_;
    }


    void pop_back() {
        if (size_ == 0) {
            return;
        }

        retreat_back();
        // Call destructor on the element
        element_at(last_.bucket, last_.index)->~T();
        --size_;
    }


    void pop_front() {
        if (size_ == 0) {
            return;
        }

        element_at(first_.bucket, first_.index)->~T();
        advance_front();
        --size_;
    }

    T& operator[](size_t idx) {


        if (idx >= size_) {
            throw std::out_of_range("Index out of range");
        }

        size_t relative_pos = idx;
        size_t curr_bucket = first_.bucket;
        size_t curr_index = first_.index;

        // navigate to right position


        while (relative_pos > 0) {
            if (curr_index + relative_pos < kBucketSize) {
                curr_index += relative_pos;
                break;
            } else {
                relative_pos -= (kBucketSize - curr_index);
                curr_index = 0;
                curr_bucket = (curr_bucket + 1) % capacity_;
            }
        }

        return *element_at(curr_bucket, curr_index);
    }

    const T& operator[](size_t idx) const {


        if (idx >= size_) {
            throw std::out_of_range("Index out of range");
        }

        size_t relative_pos = idx;
        size_t curr_bucket = first_.bucket;
        size_t curr_index = first_.index;


        while (relative_pos > 0) {
            if (curr_index + relative_pos < kBucketSize) {
                curr_index += relative_pos;
                break;
            } else {
                relative_pos -= (kBucketSize - curr_index);
                curr_index = 0;
                curr_bucket = (curr_bucket + 1) % capacity_;
            }
        }

        return *element_at(curr_bucket, curr_index);
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        return *element_at(first_.bucket, first_.index);
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        return *element_at(first_.bucket, first_.index);
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        DeqIndx tmp = last_;
        retreat_back();
        auto& result = *element_at(last_.bucket, last_.index);
        last_ = tmp;  // Restore original position
        return result;
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        DeqIndx tmp = last_;
        DeqIndx back_pos = last_;


        if (back_pos.index == 0) {
            back_pos.index = kBucketSize - 1;
            back_pos.bucket =
                (back_pos.bucket == 0) ? capacity_ - 1 : back_pos.bucket - 1;
        } else {
            --back_pos.index;
        }
        return *element_at(back_pos.bucket, back_pos.index);
    }


    bool empty() const { return size_ == 0; }


    size_t size() const { return size_; }
    class Iterator {
       private:
        Deque* container_;
        size_t position_;

       public:
        Iterator(Deque* container, size_t position)
            : container_(container), position_(position) {}

        T& operator*() const { return (*container_)[position_]; }

        Iterator& operator++() {
            ++position_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++position_;
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return position_ == other.position_ ||
                   (position_ >= container_->size_ &&
                    other.position_ >= container_->size_);
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };


    Iterator begin() { return Iterator(this, 0); }


    Iterator end() { return Iterator(this, size_); }

    void swap(Deque& other) noexcept {
        std::swap(buckets_, other.buckets_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(first_, other.first_);
        std::swap(last_, other.last_);
    }
};
}  // namespace sml

#endif	// DEQUE_H
