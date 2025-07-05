#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace sml {

// -----------------------------------------------------------------------------
// Array-based binary max-heap
// -----------------------------------------------------------------------------

template <typename T, typename Compare = std::less<T>>
class ArrayHeap {
   public:
    void insert(T value) {
        heap_.push_back(std::move(value));
        heapifyUp(heap_.size() - 1);
    }

    T extractMax() {
        if (heap_.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        T max = heap_.front();
        heap_.front() = std::move(heap_.back());
        heap_.pop_back();
        if (!heap_.empty()) {
            heapifyDown(0);
        }
        return max;
    }

    const T& getMax() const {
        if (heap_.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap_.front();
    }

    bool isEmpty() const noexcept { return heap_.empty(); }
    size_t size() const noexcept { return heap_.size(); }

    void clear() noexcept { heap_.clear(); }

    std::vector<T> toVector() const { return heap_; }

   private:
    std::vector<T> heap_;
    Compare cmp_;

    void heapifyUp(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (!cmp_(heap_[parent], heap_[idx])) {
                break;
            }
            std::swap(heap_[parent], heap_[idx]);
            idx = parent;
        }
    }

    void heapifyDown(size_t idx) {
        size_t n = heap_.size();
        while (true) {
            size_t left = 2 * idx + 1;
            size_t right = 2 * idx + 2;
            size_t largest = idx;

            if (left < n && cmp_(heap_[largest], heap_[left])) {
                largest = left;
            }
            if (right < n && cmp_(heap_[largest], heap_[right]))
                largest = right;

            if (largest == idx)
                break;
            std::swap(heap_[idx], heap_[largest]);
            idx = largest;
        }
    }
};
}  // namespace sml
