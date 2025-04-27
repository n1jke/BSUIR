#ifndef SLICE_ITERATOR_H
#define SLICE_ITERATOR_H

namespace sml {

    template<typename T>
    class Iterator {
        T *ptr;

    public:
        Iterator() = delete;

        explicit Iterator(T *p) : ptr(p) {}

        T &operator*();

        Iterator &operator++();

        Iterator &operator--();

        bool operator==(const Iterator &othr);

        bool operator!=(const Iterator &othr);

        T *operator->();
    };

}

#endif //SLICE_ITERATOR_H
