#ifndef BITSETT_H
#define BITSETT_H

#include <cstring>
#include <string>

template <size_t N>
class Bitsett {
   private:
    static constexpr size_t kBitsPerOne = 64;
    static constexpr size_t kWOrdCount = (N + kBitsPerOne - 1) / kBitsPerOne;

    size_t words_[kWOrdCount];

    size_t WordIndx(size_t indx)
        const;	// find word(size = 64byt) in bitset for interesting number

    size_t BitIndx(
        size_t indx) const;	 // find bit in bitset for interesting number


    void check_boundaries(size_t indx) const;

    void delete_useless();

   public:
    Bitsett();

    Bitsett(size_t init);

    void set(size_t pos, bool val = true);	// val true - 1, false - 0

    void set();

    void reset(size_t pos);

    void reset();

    void flip(size_t pos);

    void flip();

    bool test(size_t pos) const;

    bool none() const;	// all bits == 0

    bool all() const;  // all bits == 1

    bool any() const;

    size_t count() const;  // coutn bits == 1

    size_t size() const;

    std::string to_string() const;

    unsigned long to_ulong() const;

    size_t to_ullong() const;

    Bitsett operator~();

    Bitsett operator&(const Bitsett& other) const;

    Bitsett operator|(const Bitsett& other);

    bool operator[](size_t indx) const;
};

#include "bitsett.cpp"  // Include implementation for template class

#endif	// BITSETT_H
