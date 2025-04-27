#ifndef SLICE_SLICE_H
#define SLICE_SLICE_H

#pragma once

#include <cstddef>
#include <iostream>
#include <initializer_list>
#include "Iterator.h"
#include "Allocator.h"

namespace sml {

    template<typename T, typename Alloc = Allocator<T>>
    class slice {
        size_t size_;
        size_t capacity_;
        Allocator<T> allocator_;
        T *arr_;

        inline void reallocate();

    public:
        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //        CONSTRUCTOR, COPY CONSTRUCTOR, DESTRUCTOR         \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        slice() noexcept;                    //dont throw exceptions

        slice(size_t size);                  // init slice with n elements

        slice(size_t size, const T &val);    // init slice with n elements  with base value

        template<class Input>
        slice(Input first, Input last);      // init slice with elements in range

        slice(std::initializer_list<T> list);// init_list constructor ({1, 2, ... n})

        slice(const slice<T> &prev);         // copy constructor

        slice(slice<T> &&other) noexcept;    // move constructor, STEEL NOT COPY

        ~slice();                            // noexcept = true for destructors everytime

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        OPERATORS                         \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        slice<T> &operator=(const slice<T> &other);             // copy '=' operator

        slice<T> &operator=(slice<T> &&other);            // move '=' operator

        slice<T> &operator=(std::initializer_list<T> list);    // init_list '=' operator

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        ASSINGS                           \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        void assign(size_t size, const T &value);   // assign size elements with value to the vector

        void assign(std::initializer_list<T>);      // assign new slice with init list

        template<class Input>
        void assign(Input first, Input last);                 // assign old slice to new

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        ITERATORS                         \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        Iterator<T> begin() noexcept {           // return  iterator to slice begin
            return Iterator<T>(arr_);
        }

        const Iterator<T> cbegin() noexcept {    // return const iterator to slice begin
            return Iterator<T>(arr_);
        }

        Iterator<T> rbegin() noexcept {           // return  iterator to reverse slice begin
            return Iterator<T>(arr_ + size_);
        }

        const Iterator<T> crbegin() noexcept {    // return const iterator to reverse slice begin
            return Iterator<T>(arr_ + size_);
        }

        Iterator<T> end() noexcept {             // return iterator to slice end
            return Iterator<T>(arr_ + size_);
        }

        const Iterator<T> cend() noexcept {      // return const iterator to slice end
            return Iterator<T>(arr_ + size_);
        }

        Iterator<T> rend() noexcept {           // return  iterator to reverse slice begin
            return Iterator<T>(arr_);
        }

        const Iterator<T> crend() noexcept {    // return const iterator to reverse slice begin
            return Iterator<T>(arr_);
        }

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        CAPACITY                         \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        bool empty() const;                         // check container empty or not

        size_t size() const;                        // return curr count of elements

        size_t capacity() const;                    // return max possible if elements in container

        void resize(size_t size);                   // change count of storage elements

        void resize(size_t size, const T &val);     // change count of storage elements, new elements with value

        void reserve(size_t minSize);               // request that slice can store >= minSize elements

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        ACCESS TO DATA                    \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        T &operator[](size_t indx);             // access to element
        const T &operator[](size_t Indx) const;

        T &at(size_t indx);                     // access element with bounds check
        const T &at(size_t indx) const;

        T &front();                             // access the 1st element
        const T &front() const;

        T &back();                              // access the last element
        const T &back() const;

        T *data() noexcept;                     // access to element by ptr
        const T *data() const noexcept;

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        ADD TO DATA                       \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        void push_back(const T &elem);          // add element to end of slice with stack copy

        void push_back(T &&elem);               // move element to end of slice without stack copy

        template<class... Many>
        void emplace_back(Many &&...many);      // add element to end of slice without stack copy

        void pop_back();                        // remove element from the and

        void swap(slice<T> &prev);              // swap 2 slices content

        void clear() noexcept;                  // clear container

        template<class... Args>
        Iterator<T> emplace(const T *pos, Args &&... args);              // in-place container insert

        Iterator<T> insert(const T *pos, const T &val);                // insert elements at a certain position

        Iterator<T> insert(const T *pos, T &&val);                     // Moves elements into the container

        Iterator<T> insert(const T *, size_t, const T &);        // insert elements at position

        template<class Input>
        Iterator<T> insert(const T *, Input first, Input last);  // insert elements from range (first, last)

        Iterator<T> insert(const T *, std::initializer_list<T>);  // insert elements from init list

        Iterator<T> erase(const T *pos);                            // erase elements from pos

        Iterator<T> erase(const T *, const T *);                  // erse elements in range

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        COMPARE                           \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        bool operator==(const slice<T> &other) const;      // compare for equality

        bool operator!=(const slice<T> &other) const;      // compare for not equality

        bool operator>=(const slice<T> &other) const;      // compare for more or equal

        bool operator>(const slice<T> &other) const;      // compare for more

        bool operator<=(const slice<T> &other) const;      // compare for less or equal

        bool operator<(const slice<T> &other) const;      // compare for less
    };


    template<typename T, typename Allocator>
    inline void slice<T, Allocator>::reallocate() {
        T *temp = allocator_.allocate(capacity_);

        for (size_t i = 0; i < size_; ++i) { allocator_.construct(temp + i, arr_[i]); }
        for (size_t i = 0; i < size_; ++i) { allocator_.destroy(&arr_[i]); }

        allocator_.deallocate(arr_);
        arr_ = temp;
    }

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //        CONSTRUCTOR, COPY CONSTRUCTOR, DESTRUCTOR         \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

    template<typename T, typename Allocator>
    slice<T, Allocator>::slice() noexcept {    //dont throw exceptions
        capacity_ = 0;
        size_ = 0;
        arr_ = allocator_.allocate(capacity_);
    }

    template<typename T, typename Allocator>
    slice<T, Allocator>::slice(size_t size) {   // init slice with n elements
        capacity_ = size * 2;
        size_ = size;

        arr_ = allocator_.allocate(capacity_);
        for (size_t i = 0; i < size; ++i) { allocator_.construct(arr_ + i, arr_[i]); }
    }

    template<typename T, typename Allocator>
    slice<T, Allocator>::slice(size_t size, const T &val) { // init slice with n elements  with base value
        capacity_ = size * 2;
        size_ = size;

        arr_ = allocator_.allocate(capacity_);
        for (size_t i = 0; i < size; ++i) { allocator_.construct(arr_ + i, val); }
    }

    template<typename T, typename Allocator>
    template<class Input>
    slice<T, Allocator>::slice(Input first, Input last) {    // init slice with elements in range
        size_t count = last - first;
        capacity_ = count * 2;
        size_ = count;

        arr_ = allocator_.allocate(capacity_);
        for (size_t i = 0; i < count; ++i) { allocator_.construct(arr_ + i, *first); }
    }

    template<typename T, typename Allocator>
    slice<T, Allocator>::slice(std::initializer_list<T> list) {    // init_list constructor ({1, 2, ... n};)
        capacity_ = list.size() * 2;

        arr_ = allocator_.allocate(capacity_);
        for (const auto &itm: list) { allocator_.construct(arr_ + size_++, itm); }
    }

    template<typename T, typename Allocator>
    slice<T, Allocator>::slice(const slice<T> &prev) {    // copy constructor
        capacity_ = prev.capacity();
        size_ = prev.size();

        arr_ = allocator_.allocate(capacity_);
        for (size_t i = 0; i < size_; ++i) { allocator_.construct(arr_ + i, prev.arr_[i]); }
    }

    template<typename T, typename Allocator>
    slice<T, Allocator>::slice(slice<T> &&other) noexcept {    // move constructor
        capacity_ = other.capacity();
        size_ = other.size();

        arr_ = allocator_.allocate(capacity_);
        for (size_t i = 0; i < size_; ++i) { allocator_.construct(arr_ + i, std::move(other.arr_[i])); }
    }

    template<typename T, typename Allocator>
    slice<T, Allocator>::~slice() {
        for (size_t i = 0; i < size_; ++i) {
            allocator_.destroy(arr_ + i);
        }
        allocator_.deallocate(arr_, capacity_);
    }

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        OPERATORS                         \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

    template<typename T, typename Allocator>
    slice<T> &slice<T, Allocator>::operator=(const slice<T> &other) {     // copy '=' operator
        if (this == &other) {
            return *this;
        }
        size_ = other.size_;
        if (capacity_ < other.size_) {
            capacity_ = other.size_ * 2;
            reallocate();
        }
        for (size_t i = 0; i < other.size_; ++i) { allocator_.construct(arr_ + i, other.arr_[i]); }

        return *this;
    }

    template<typename T, typename Allocator>
    slice<T> &slice<T, Allocator>::operator=(slice<T> &&other) {    // move '=' operator
        if (this != &other) {
            for (size_t i = 0; i < size_; ++i) { allocator_.destroy(arr_ + i); }
            allocator_.deallocate(arr_, capacity_);

            arr_ = other.arr_, size_ = other.size_, capacity_ = other.capacity_;
            other.arr_ = nullptr, other.size_ = 0, other.capacity_ = 0;
        }

        return *this;
    }

    template<typename T, typename Allocator>
    slice<T> &slice<T, Allocator>::operator=(std::initializer_list<T> list) {    // init_list '=' operator
        for (size_t i = 0; i < size_; ++i) { allocator_.destroy(arr_ + i); }

        if (capacity_ < list.size()) {
            capacity_ = list.size() * 2;
            reallocate();
        }
        size_ = 0;
        for (const auto &item: list) { allocator_.construct(arr_ + size_++, item); }

        return *this;
    }

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        ASSIGN                           \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

    template<typename T, typename Allocator>
    void slice<T, Allocator>::assign(size_t size, const T &value) {   // assign size elements with value to the vector
        if (size > capacity_) {
            capacity_ *= 2;
            reallocate();
        }
        size_ = size;

        for (size_t i = 0; i < size; ++i) { allocator_.construct(arr_ + i, value); }
    }

    template<typename T, typename Allocator>
    void slice<T, Allocator>::assign(std::initializer_list<T> list) {    // assign new slice with init list
        if (list.size() > capacity_) {
            capacity_ *= 2;
            reallocate();
        }
        size_ = 0;

        for (const auto &item: list) {
            arr_[size_++] = item;
        }
    }

    template<typename T, typename Allocator>
    template<class Input>
    void slice<T, Allocator>::assign(Input first, Input last) {    // assign old slice to new
        if (last - first > capacity_) {
            capacity_ *= 2;
            reallocate();
        }
        size_ = last - first;

        for (size_t i = 0; i < size_; ++i) { allocator_.construct(arr_ + i, *first); }
    }

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        CAPACITY                         \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

    template<typename T, typename Allocator>
    bool slice<T, Allocator>::empty() const {                    // check container empty or not
        return size_ == 0;
    }

    template<typename T, typename Allocator>
    size_t slice<T, Allocator>::size() const {                   // return curr count of elements
        return size_;
    }

    template<typename T, typename Allocator>
    size_t slice<T, Allocator>::capacity() const {               // return max possible if elements in container
        return capacity_;
    }

    template<typename T, typename Allocator>
    void slice<T, Allocator>::resize(size_t size) {               // change count of storage elements
        if (size > size_) {
            if (size > capacity_) {
                capacity_ = size;
                reallocate();
            }
            for (size_t i = size_; i < size; ++i) { allocator_.construct(arr_ + i, arr_[i - 1]); }
        } else {
            for (size_t i = size_; i > size; --i) { allocator_.destroy(arr_ + i - 1); }
        }

        size_ = size;
    }

    template<typename T, typename Allocator>
    void slice<T, Allocator>::resize(size_t size,
                                     const T &val) { // change count of storage elements, new elements with value
        if (size > size_) {
            if (size > capacity_) {
                capacity_ = size;
                reallocate();
            }
            for (size_t i = size_; i < size; ++i) { allocator_.construct(arr_ + i, val); }
        } else {
            for (size_t i = size_; i > size; --i) { allocator_.destroy(arr_ + i - 1); }
        }

        size_ = size;
    }

    template<typename T, typename Allocator>
    void slice<T, Allocator>::reserve(size_t minSize) {           // request that slice can store >= minSize elements
        if (capacity_ < minSize) {
            capacity_ = minSize;
            reallocate();
        }
    }


    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        ACCESS TO DATA                    \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

    template<typename T, typename Allocator>
    T &slice<T, Allocator>::operator[](size_t indx) {             // access to element
        return arr_[indx];
    }

    template<typename T, typename Allocator>
    const T &slice<T, Allocator>::operator[](size_t Indx) const {
        return arr_[Indx];
    }

    template<typename T, typename Allocator>
    T &slice<T, Allocator>::at(size_t indx) {                     // access element with bounds check
        if (indx < size_) {
            return arr_[indx];
        } else {
            throw std::out_of_range("accessed pos out of range");
        }
    }

    template<typename T, typename Allocator>
    const T &slice<T, Allocator>::at(size_t indx) const {
        if (indx < size_) {
            return arr_[indx];
        } else {
            throw std::out_of_range("accessed pos out of range");
        }
    }

    template<typename T, typename Allocator>
    T &slice<T, Allocator>::front() {                             // access the 1st element
        if (size_ == 0) {
            throw std::out_of_range("accessed pos out of range");
        } else {
            return arr_[0];
        }
    }

    template<typename T, typename Allocator>
    const T &slice<T, Allocator>::front() const {
        if (size_ == 0) {
            throw std::out_of_range("accessed pos out of range");
        } else {
            return arr_[0];
        }
    }

    template<typename T, typename Allocator>
    T &slice<T, Allocator>::back() {                              // access the last element
        if (size_ == 0) {
            throw std::out_of_range("accessed pos out of range");
        } else {
            return arr_[size_ - 1];
        }
    }

    template<typename T, typename Allocator>
    const T &slice<T, Allocator>::back() const {
        if (size_ == 0) {
            throw std::out_of_range("accessed pos  out of range");
        } else {
            return arr_[size_ - 1];
        }
    }

    template<typename T, typename Allocator>
    T *slice<T, Allocator>::data() noexcept {                     // access to element by ptr
        return arr_;
    }

    template<typename T, typename Allocator>
    const T *slice<T, Allocator>::data() const noexcept {
        return arr_;
    }

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        ADD TO DATA                       \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

    template<typename T, typename Allocator>
    void slice<T, Allocator>::push_back(const T &elem) {          // add element to end of slice with stack copy
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate();
        }

        arr_[size_] = elem;
        ++size_;
    }

    template<typename T, typename Allocator>
    void slice<T, Allocator>::push_back(T &&elem) {               // move element to end of slice without stack copy
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate();
        }

        arr_[size_] = std::move(elem);
        ++size_;
    }

    template<typename T, typename Allocator>
    template<class... Many>
    void slice<T, Allocator>::emplace_back(Many &&...many) {      // add element to end of slice without stack copy
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate();
        }

        new(arr_ + size_) T(std::forward<Many>(many)...);
        ++size_;
    }

    template<typename T, typename Allocator>
    void slice<T, Allocator>::pop_back() {                        // remove element from the and
        allocator_.destroy(arr_ + size_);
        --size_;
    }

    template<typename T, typename Allocator>
    void slice<T, Allocator>::swap(slice<T> &prev) {              // swap 2 slices content
        std::swap(size_, prev.size_);
        std::swap(capacity_, prev.capacity_);
        std::swap(arr_, prev.arr_);
    }

    template<typename T, typename Allocator>
    void slice<T, Allocator>::clear() noexcept {                  // clear container
        for (size_t i = 0; i < size_; ++i) { allocator_.destroy(arr_ + i); }
        size_ = 0;
    }

    template<typename T, typename Allocator>
    template<class... Args>
    Iterator<T> slice<T, Allocator>::emplace(const T *pos, Args &&... args) {              // in-place container insert
        if (pos < arr_ || pos > arr_ + size_) {
            throw std::out_of_range("accessed pos out of range");
        }

        size_t indx = pos - arr_;
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity() * 2;
            reallocate();
            pos = arr_ + indx;
        }

        std::move_backward(arr_ + indx, arr_ + size_, arr_ + size_ + 1);

        allocator_.construct(arr_ + indx, std::forward<Args>(args)...);
        ++size_;

        return Iterator<T>(arr_ + indx);
    }

    template<typename T, typename Allocator>
    Iterator<T>
    slice<T, Allocator>::insert(const T *pos, const T &val) {                // insert elements at a certain position
        auto indx = pos - arr_;

        if (size_ >= capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate();
        }

        for (size_t i = size_; i > indx; --i) { arr_[i] = arr_[i - 1]; }

        arr_[indx] = val;
        ++size_;

        return Iterator<T>(arr_ + indx);
    }

    template<typename T, typename Allocator>
    Iterator<T>
    slice<T, Allocator>::insert(const T *pos, T &&val) {                     // Moves elements into the container
        auto indx = pos - arr_;

        if (size_ >= capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate();
        }

        for (size_t i = size_; i > indx; --i) {
            allocator_.construct(arr_ + i, std::move(arr_[i - 1]));
            allocator_.destroy(arr_ + i - 1);
        }

        arr_[indx] = std::move(val);
        ++size_;

        return Iterator<T>(arr_ + indx);
    }

    template<typename T, typename Allocator>
    Iterator<T>
    slice<T, Allocator>::insert(const T *pos, size_t count, const T &value) {        // insert elements at position
        size_t indx = pos - arr_;
        if (indx > size_) {
            throw std::out_of_range("insert pos out of range");
        }

        while (size_ + count > capacity_) {
            capacity_ = (capacity_ == 0) ? count : capacity_ * 2;
            reallocate();
            pos = arr_ + indx;
        }

        for (size_t i = size_; i > indx; --i) {
            allocator_.construct(arr_ + i + count - 1, std::move(arr_[i - 1]));
            allocator_.destroy(arr_ + i - 1);
        }

        for (size_t j = 0; j < count; ++j) {
            allocator_.construct(arr_ + indx + j, value);
        }
        size_ += count;

        return Iterator<T>(arr_ + indx);
    }

    template<typename T, typename Allocator>
    template<class Input>
    Iterator<T>
    slice<T, Allocator>::insert(const T *pos, Input first, Input last) {  // insert elements from range (first, last)
        size_t indx = pos - arr_;
        if (indx > size_) {
            throw std::out_of_range("insert: pos out of range");
        }

        size_t count = std::distance(first, last);
        while (size_ + count > capacity_) {
            capacity_ = (capacity_ == 0) ? count : capacity_ * 2;
            reallocate();
            pos = arr_ + indx;
        }

        for (size_t i = size_; i > indx; --i) {
            allocator_.construct(arr_ + i + count - 1, std::move(arr_[i - 1]));
            allocator_.destroy(arr_ + i - 1);
        }

        for (size_t j = 0; first != last; ++first, ++j) {
            allocator_.construct(arr_ + indx + j, *first);
        }
        size_ += count;

        return Iterator<T>(arr_ + indx);
    }

    template<typename T, typename Allocator>
    Iterator<T>
    slice<T, Allocator>::insert(const T *pos, std::initializer_list<T> list) {  // insert elements from init list
        return insert(pos, list.begin(), list.end());
    }

    template<typename T, typename Allocator>
    Iterator<T> slice<T, Allocator>::erase(const T *pos) {                            // erase elements from pos
        size_t indx = pos - arr_;

        if (indx >= size_) {
            throw std::out_of_range("erase position out of range");
        }

        allocator_.destroy(arr_ + indx);
        for (size_t i = indx; i < size_ - 1; ++i) {
            allocator_.construct(arr_ + i, std::move(arr_[i + 1]));
            allocator_.destroy(arr_ + i + 1);
        }
        --size_;

        return Iterator<T>(arr_ + indx);
    }

    template<typename T, typename Allocator>
    Iterator<T> slice<T, Allocator>::erase(const T *first, const T *last) {                  // erase elements in range
        auto start = first - arr_;
        auto end = last - arr_;
        auto count = end - start;

        if (end > size_ || start >= size_ || start >= end) {
            throw std::out_of_range("invalid range in erase");
        }

        for (size_t i = start; i < end; ++i) {
            allocator_.destroy(arr_ + i);
        }

        for (size_t i = end; i < size_; ++i) {
            allocator_.construct(arr_ + i - count, std::move(arr_[i]));
            allocator_.destroy(arr_ + i);
        }

        size_ -= count;

        return Iterator<T>(arr_ + start);
    }

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                        COMPARE                           \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

    template<typename T, typename Allocator>
    bool slice<T, Allocator>::operator==(const slice<T> &other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (arr_[i] != other.arr_[i]) {
                return false;
            }
        }
        return true;
    }

    template<typename T, typename Allocator>
    bool slice<T, Allocator>::operator!=(const slice<T> &other) const {
        return !(*this == other);
    }

    template<typename T, typename Allocator>
    bool slice<T, Allocator>::operator<(const slice<T> &other) const {
        size_t min_size = std::min(size_, other.size_);
        for (size_t i = 0; i < min_size; ++i) {
            if (arr_[i] < other.arr_[i]) return true;
            if (arr_[i] > other.arr_[i]) return false;
        }
        return size_ < other.size_;
    }

    template<typename T, typename Allocator>
    bool slice<T, Allocator>::operator>(const slice<T> &other) const {
        return other < *this;
    }

    template<typename T, typename Allocator>
    bool slice<T, Allocator>::operator<=(const slice<T> &other) const {
        return !(*this > other);
    }

    template<typename T, typename Allocator>
    bool slice<T, Allocator>::operator>=(const slice<T> &other) const {
        return !(*this < other);
    }
}

#endif //SLICE_SLICE_H