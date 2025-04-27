#include "bitsett.h"

#include <stdexcept>

template <size_t N>
size_t Bitsett<N>::WordIndx(size_t indx) const {
    return indx / kBitsPerOne;
}

template <size_t N>
size_t Bitsett<N>::BitIndx(size_t indx) const {
    return indx % kBitsPerOne;
}

template <size_t N>
void Bitsett<N>::check_boundaries(
    size_t indx) const {  // check correct position


    if (indx >= N) {
        throw std::out_of_range("bit position out of range");
    }
}

template <size_t N>
void Bitsett<N>::delete_useless() {


    if (N % kBitsPerOne == 0) {
        return;
    } else {
        size_t last_bits = N % kBitsPerOne;
        words_[kWOrdCount - 1] &= ((1ULL << last_bits) - 1);
    }
}

template <size_t N>
Bitsett<N>::Bitsett() {
    std::memset(words_, 0, sizeof(words_));
}

template <size_t N>
Bitsett<N>::Bitsett(size_t init) {
    std::memset(words_, 0, sizeof(words_));
    words_[0] = init;
}

template <size_t N>
void Bitsett<N>::set(size_t pos, bool val) {  // val true - 1, false - 0
    check_boundaries(pos);
    // goto current bit with prev methods


    if (val) {
        words_[WordIndx(pos)] |= 1ULL << BitIndx(pos);
        // create mask moving 1ULL for BitIndx(pos) and bits or for mask
    } else {
        words_[WordIndx(pos)] &= ~(1ULL << BitIndx(pos));
        // create mask moving 1ULL for BitIndx(pos) and bits or for mask
    }
}

template <size_t N>
void Bitsett<N>::set() {
    const size_t max = 255;	 //all bytes is 1
    std::memset(words_, max, sizeof(words_));
    delete_useless();
}

template <size_t N>
void Bitsett<N>::reset(size_t pos) {
    set(pos, false);
}

template <size_t N>
void Bitsett<N>::reset() {
    std::memset(words_, 0, sizeof(words_));
}

template <size_t N>
void Bitsett<N>::flip(size_t pos) {
    check_boundaries(pos);
    words_[WordIndx(pos)] ^= (1ULL << BitIndx(pos));
}

template <size_t N>
void Bitsett<N>::flip() {


    for (size_t i = 0; i < kWOrdCount; ++i) {
        words_[i] = ~words_[i];
    }
    delete_useless();
}

template <size_t N>
bool Bitsett<N>::test(size_t pos) const {  // check bit for one in pos
    check_boundaries(pos);
    // goto current bit with prev methods
    return (words_[WordIndx(pos)] >> BitIndx(pos)) & 1ULL;
}

template <size_t N>
bool Bitsett<N>::any() const {


    for (size_t i = 0; i < kWOrdCount; ++i) {
        if (words_[i]) {
            return true;
        }
    }
    return false;
}

template <size_t N>
bool Bitsett<N>::none() const {
    return !any();	// all bytes == 0
}

template <size_t N>
bool Bitsett<N>::all() const {


    for (size_t i = 0; i < kWOrdCount - 1; ++i) {
        if (words_[i] != ~0ULL) {
            return false;  // all is zeros
        }
    }

    size_t last_bits = N % kBitsPerOne;


    if (last_bits == 0) {  // check last word fully used
        return words_[kWOrdCount - 1] == ~0ULL;
    }

    // part of last word
    size_t mask = (1ULL << last_bits) - 1;
    return (words_[kWOrdCount - 1] & mask) == mask;	 // !!! test
}

template <size_t N>
size_t Bitsett<N>::count() const {
    size_t total = 0;


    for (size_t i = 0; i < kWOrdCount; ++i) {
        total += std::__popcount(words_[i]);  // O(1) find all ones
    }
    return total;
}

template <size_t N>
size_t Bitsett<N>::size() const {
    return N;
}

template <size_t N>
std::string Bitsett<N>::to_string() const {
    std::string s;
    s.reserve(N);


    for (size_t i = N; i-- > 0;) {
        s.push_back(test(i) ? '1' : '0');
    }
    return s;
}

template <size_t N>
unsigned long Bitsett<N>::to_ulong() const {
    const int eight = 8;
    if (N > sizeof(unsigned long) * eight) {


        if (kWOrdCount > 1 && words_[1]) {
            throw std::overflow_error("too large for ulong");
        }
    }
    return static_cast<unsigned long>(words_[0]);
}

template <size_t N>
size_t Bitsett<N>::to_ullong() const {
    const int eight = 8;
    if (N > sizeof(size_t) * eight) {


        if (kWOrdCount > 1 && words_[1]) {
            throw std::overflow_error("too large for ullong");
        }
    }
    return static_cast<size_t>(words_[0]);
}

template <size_t N>
Bitsett<N> Bitsett<N>::operator~() {
    Bitsett result;


    for (size_t i = 0; i < kWOrdCount; ++i) {
        result.words_[i] = ~words_[i];
    }
    result.delete_useless();
    return result;
}

template <size_t N>
Bitsett<N> Bitsett<N>::operator&(const Bitsett& other) const {
    Bitsett result;


    for (size_t i = 0; i < kWOrdCount; ++i) {
        result.words_[i] = words_[i] & other.words_[i];
    }
    return result;
}

template <size_t N>
Bitsett<N> Bitsett<N>::operator|(const Bitsett& other) {
    Bitsett result;

    size_t end = std::min(kWOrdCount, other.kWOrdCount);


    for (size_t i = 0; i < end; ++i) {
        result.words_[i] = words_[i] | other.words_[i];
    }

    return result;
}

template <size_t N>
bool Bitsett<N>::operator[](size_t indx) const {
    size_t word = WordIndx(indx);
    size_t bit = BitIndx(indx);

    return (words_[word] >> bit) & 1ULL;
}
