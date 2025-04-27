#include "Iterator.h"

template <typename T>
T& sml::Iterator<T>::operator*() {
    return *ptr;
}

template <typename T>
sml::Iterator<T>& sml::Iterator<T>::operator++() {
    ++ptr;
    return *this;
}

template <typename T>
sml::Iterator<T>&sml:: Iterator<T>::operator--() {
    --ptr;
    return *this;
}

template <typename T>
bool sml::Iterator<T>::operator==(const Iterator<T>& othr) {
    return ptr == othr.ptr;
}

template <typename T>
bool sml::Iterator<T>::operator!=(const Iterator<T>& othr) {
    return ptr != othr.ptr;
}

template <typename T>
T* sml::Iterator<T>::operator->() {
    return ptr;
}