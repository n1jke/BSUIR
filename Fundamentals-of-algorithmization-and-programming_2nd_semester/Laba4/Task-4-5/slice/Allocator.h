#ifndef SLICE_ALLOCATOR_H
#define SLICE_ALLOCATOR_H

#pragma once

#include <cstddef>

namespace sml {

    template<typename T>
    class Allocator {
    public:
        T *allocate(size_t size) {
            return reinterpret_cast<T *>(new char[sizeof(T) * size]);
        }

        void deallocate(T *ptr, size_t size = 0) {
            delete[] reinterpret_cast<char *>(ptr);
        }

        void construct(T *ptr, const T &value) {
            new(ptr) T(value); // placement new init of difficult type with value, in address - ptr
        }

        void destroy(T *ptr) {
            ptr->~T();
        }
    };

}


#endif //SLICE_ALLOCATOR_H
