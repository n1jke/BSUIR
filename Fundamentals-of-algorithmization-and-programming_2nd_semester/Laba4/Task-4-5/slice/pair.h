#ifndef SLICE_PAIR_H
#define SLICE_PAIR_H

#pragma once

#include <utility>

namespace sml {

    template<typename T1, typename T2>
    class pair {
    public:
        T1 first;
        T2 second;

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //               CONSTRUCTOR, COPY CONSTRUCTOR              \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        pair() : first(), second() {}                                           // default constructor

        pair(const pair &other) : first(other.first), second(other.second) {}   // copy constructor

        pair(const T1 &x, const T2 &y) : first(x), second(y) {}                  // copy constructor from type

        template<typename U1, typename U2>
        pair(const pair<U1, U2> &p) : first(p.first),
                                      second(p.second) {}       // templ copy constructor if U1 -> T1 and U2 -> T2 implicitly converted

        pair(pair &&other) noexcept                                             // move constructor
                : first(std::move(other.first)), second(std::move(other.second)) {}

        template<typename U1, typename U2>
        // move constructor from type
        pair(U1 &&x, U2 &&y) : first(std::forward<U1>(x)), second(std::forward<U2>(y)) {}

        template<typename U1, typename U2>
        // templ move constructor
        pair(pair<U1, U2> &&p) : first(std::forward<U1>(p.first)), second(std::forward<U2>(p.second)) {}

        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
    //                          OPERATORS                       \\
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\

        pair &operator=(const pair &other) noexcept {
            if (this != &other) {
                first = other.first;
                second = other.second;
            }
            return *this;
        }

        pair &operator=(pair &&other) noexcept {
            if (this != &other) {
                first = std::move(other.first);
                second = std::move(other.second);
            }
            return *this;
        }

        template<typename U1, typename U2>
        pair &operator=(const pair<U1, U2> &other) {
            first = other.first;
            second = other.second;
            return *this;
        }

        template<typename U1, typename U2>
        pair &operator=(pair<U1, U2> &&other) {
            first = std::forward<U1>(other.first);
            second = std::forward<U2>(other.second);
            return *this;
        }


        void swap(pair &other) noexcept {
            using std::swap;
            swap(first, other.first);
            swap(second, other.second);
        }
    };

//non-member func
    template<typename T1, typename T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<typename T1, typename T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs == rhs);
    }

    template<typename T1, typename T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template<typename T1, typename T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(rhs < lhs);
    }

    template<typename T1, typename T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return rhs < lhs;
    }

    template<typename T1, typename T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs < rhs);
    }

// Helper function to create pairs
    template<typename T1, typename T2>
    pair<T1, T2> make_pair(T1 t1, T2 t2) {
        return pair<T1, T2>(t1, t2);
    }
}


#endif // SLICE_PAIR_H 