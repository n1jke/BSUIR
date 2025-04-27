#include "stringg.h"
#include <cstring>
#include <stdexcept>

void* sml::stringg::memcpy_sml(void* dest, const void* src, size_t count) {
    //copy count elements from src to dest
    auto* str1 = static_cast<char*>(dest);
    auto* str2 = static_cast<const char*>(src);

    if ((str1 != nullptr) && (str2 != nullptr)) {
        while (count--)	 //till cnt
        {
            *(str1++) = *(str2++);
        }
    }
    return dest;
}

void* sml::stringg::memmove_sml(void* dest, const void* src, size_t count) {
    // safe memcpy
    if ((dest == nullptr && count > 0) || (src == nullptr && count > 0)) {
        return nullptr;
    }


    if (dest == src || count == 0) {
        return dest;
    }

    auto* d = static_cast<unsigned char*>(dest);
    auto* s = static_cast<const unsigned char*>(src);


    if (s < d && d < s + count) {
        // dest  inside src start copying from end
        d += count;
        s += count;
        while (count--) {
            *--d = *--s;
        }
    } else {
        while (count--) {
            *d++ = *s++;
        }
    }

    return dest;
}


char* sml::stringg::strcpy_sml(char* dest, const char* src) {


    if (dest != nullptr && src != nullptr) {
        size_t i = 0;
        while (src[i] != '\0') {
            i++;
        }

        memcpy_sml(dest, src, i);
        dest[i] = '\0';
        return dest;
    } else {
        throw std::invalid_argument("bad pointer");
    }
}

char* sml::stringg::strncpy_sml(char* dest, const char* src, size_t coutn) {


    if (dest == nullptr || src == nullptr) {
        throw std::invalid_argument("bad pointer");
    }
    int i = 0;


    for (; i < coutn && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }


    if (i < coutn) {
        dest[i] = '\0';
    }
    return dest;
}

char* sml::stringg::strcat_sml(char* s1, const char* s2) {


    if (s1 == nullptr || s2 == nullptr) {
        throw std::invalid_argument("bad pointer");
    }
    int i = 0;


    while (s1[i] != '\0') {
        i++;
    }
    int j = 0;
    while (s2[j] != '\0') {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    return s1;
}

char* sml::stringg::strncat_sml(char* s1, const char* s2, size_t count) {


    if (s1 == nullptr || s2 == nullptr) {
        throw std::invalid_argument("bad pointer");
    }
    int i = 0;


    while (s1[i] != '\0') {
        i++;
    }
    int j = 0;
    while (s2[j] != '\0' && j < count) {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    return s1;
}

int sml::stringg::memcmp_sml(const void* s1, const void* s2, size_t count) {
    int i = 0;
    auto* str2 = static_cast<const char*>(s2);
    auto* str1 = static_cast<const char*>(s1);
    while (i < count && str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i])
            return -1;
        if (str1[i] > str2[i])
            return 1;
        i++;
    }


    if (i == count) {
        return 0;
    }


    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    }


    if (str1[i] == '\0') {
        return -1;
    }
    return 1;
}

int sml::stringg::strcmp_sml(const char* s1, const char* s2) {
    int i = 0;
    auto* str2 = static_cast<const char*>(s2);
    auto* str1 = static_cast<const char*>(s1);
    while (str1[i] != '\0' && str2[i] != '\0') {


        if (str1[i] < str2[i]) {
            return -1;
        }


        if (str1[i] > str2[i]) {
            return 1;
        }
        i++;
    }


    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    }


    if (str1[i] == '\0') {
        return -1;
    }
    return 1;
}

int sml::stringg::strcoll_sml(const char* s1, const char* s2) {
    return strcmp_sml(s1, s2);
}

int sml::stringg::strncmp_sml(const char* s1, const char* s2, size_t n) {
    int i = 0;
    auto* str2 = static_cast<const char*>(s2);
    auto* str1 = static_cast<const char*>(s1);


    while (str1[i] != '\0' && str2[i] != '\0' && n--) {
        if (str1[i] < str2[i])
            return -1;
        if (str1[i] > str2[i])
            return 1;
        i++;
    }


    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    }


    if (str1[i] == '\0') {
        return -1;
    }
    return 1;
}

char* sml::stringg::strxfrm_sml(char* s1, const char* s2, size_t n) {

    return strncpy_sml(s1, s2, n);
}

char* sml::stringg::strtok_sml(char* s1, const char* s2) {
    static char* last = nullptr;
    char* start;
    const char* delim = s2;
    if (s1 == nullptr || s1[0] == '\0')
        return nullptr;
    while (*last != '\0' && strchr_sml(delim, *last) != nullptr)
        last++;


    if (*last == '\0') {
        last = nullptr;
        return nullptr;
    }

    start = last;

    while (*last != '\0' && strchr_sml(delim, *last) == nullptr)
        last++;


    if (*last == '\0') {
        last = nullptr;
    } else {
        *last = '\0';
        last++;
    }

    return start;
}

void* sml::stringg::memset_sml(void* dest, int value, size_t count) {
    auto* ptr = static_cast<unsigned char*>(dest);


    if (ptr == nullptr) {
        return nullptr;
    }


    for (size_t i = 0; i < count; i++) {
        ptr[i] = static_cast<unsigned char>(value);
    }

    return dest;
}

char* sml::stringg::strerror_sml(int errnum) {
    return std::strerror(errnum);
}

size_t sml::stringg::strlen_sml(const char* str) {


    if (str == nullptr) {
        return 0;
    }

    size_t len = 0;


    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}

char* sml::stringg::strchr_sml(const char* str, int ch) {


    if (str == nullptr) {
        return nullptr;
    }


    while (*str != '\0' && *str != ch) {
        str++;
    }


    if (*str == ch) {
        return const_cast<char*>(str);
    }
    return nullptr;
}

sml::stringg::stringg()
    : ptr(std::make_unique<char[]>(1)), size_(1), capacity_(1) {
    ptr[0] = '\0';
}

sml::stringg::stringg(const char* str) {


    if (str == nullptr) {
        ptr = std::make_unique<char[]>(1);
        size_ = 1;
        capacity_ = 1;
        ptr[0] = '\0';
        return;
    }

    size_t length = strlen_sml(str);
    size_ = length + 1;
    capacity_ = size_;
    ptr = std::make_unique<char[]>(capacity_);

    memcpy_sml(ptr.get(), str, length);
    ptr[length] = '\0';
}

sml::stringg::stringg(size_t count, char c)
    : ptr(std::make_unique<char[]>(count + 1)),
      size_(count + 1),
      capacity_(count + 1) {


    for (size_t i = 0; i < count; ++i) {
        ptr[i] = c;
    }
    ptr[count] = '\0';
}

sml::stringg::stringg(const stringg& other)
    : ptr(std::make_unique<char[]>(other.size_)),
      size_(other.size_),
      capacity_(other.size_) {
    memcpy_sml(ptr.get(), other.ptr.get(), size_);
}

sml::stringg::stringg(stringg&& other)
    : ptr(std::move(other.ptr)),
      size_(other.size_),
      capacity_(other.capacity_) {
    other.size_ = 0;
    other.capacity_ = 0;
}

void sml::stringg::resize(size_t new_size) {
    new_size++;	 // Account for null terminator


    if (new_size <= size_) {
        // Shrinking string
        size_ = new_size;
        ptr[size_ - 1] = '\0';
    } else {
        // grow string
        reserve(new_size);
        for (size_t i = size_; i < new_size; ++i) {
            ptr[i] = '\0';
        }

        size_ = new_size;
    }
}

void sml::stringg::reserve(size_t new_capacity) {
    new_capacity++;	 // \0


    if (new_capacity <= capacity_) {
        return;	 // enought
    }

    std::unique_ptr<char[]> new_ptr = std::make_unique<char[]>(new_capacity);

    // copy data


    if (size_ > 0) {
        memcpy_sml(new_ptr.get(), ptr.get(), size_);
    }

    ptr = std::move(new_ptr);
    capacity_ = new_capacity;
}

bool sml::stringg::empty() const {
    return size_ <= 1;
}

size_t sml::stringg::size() const {
    return (size_ > 0) ? size_ - 1 : 0;
}

size_t sml::stringg::capacity() const {
    return capacity_;
}

void sml::stringg::clear() {
    resize(0);
}

void sml::stringg::erase(size_t pos, size_t len) {


    if (pos >= size_ - 1) {
        throw std::out_of_range("Position out of range");
    }

    // if len  goes beyond string end


    if (pos + len > size_ - 1) {
        len = size_ - 1 - pos;
    }
    //move
    memmove_sml(ptr.get() + pos, ptr.get() + pos + len, size_ - pos - len);

    size_ -= len;
}

void sml::stringg::push_back(char c) {
    // check to alloc


    if (size_ + 1 >= capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 2 : capacity_ * 2;
        reserve(new_capacity);
    }
    ptr[size_ - 1] = c;
    ptr[size_] = '\0';
    ++size_;
}

void sml::stringg::pop_back() {
    if (empty()) {
        return;
    }

    --size_;
    ptr[size_ - 1] = '\0';
}

char& sml::stringg::front() {
    if (empty()) {
        throw std::out_of_range("string is empty");
    }
    return ptr[0];
}

char& sml::stringg::back() {
    if (empty()) {
        throw std::out_of_range("string is empty");
    }
    return ptr[size_ - 2];
}

void sml::stringg::insert(size_t pos, const char* str) {


    if (pos > size_ - 1) {
        throw std::out_of_range("Position out of range");
    }


    if (str == nullptr) {
        return;
    }

    size_t len = strlen_sml(str);


    if (len == 0) {
        return;
    }

    size_t new_size = size_ + len;


    if (new_size > capacity_) {
        reserve(new_size + capacity_);
    }

    // move && copy
    memmove_sml(ptr.get() + pos + len, ptr.get() + pos, size_ - pos);
    memcpy_sml(ptr.get() + pos, str, len);
    size_ += len;
}

void sml::stringg::append(const char* str) {


    if (str == nullptr) {
        return;
    }

    insert(size_ - 1, str);
}

void sml::stringg::append(const stringg& str) {
    if (str.empty()) {
        return;
    }

    append(str.ptr.get());
}

sml::stringg operator+(const sml::stringg& left, const sml::stringg& right) {
    sml::stringg result(left);
    result.append(right);
    return result;
}

sml::stringg operator+(const sml::stringg& left, char right) {
    sml::stringg result(left);
    result.push_back(right);
    return result;
}

sml::stringg& sml::stringg::operator=(const stringg& other) {


    if (this != &other) {
        ptr = std::make_unique<char[]>(other.size_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        memcpy_sml(ptr.get(), other.ptr.get(), size_);
    }
    return *this;
}

sml::stringg& sml::stringg::operator=(stringg&& other) noexcept {


    if (this != &other) {
        ptr = std::move(other.ptr);
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

char& sml::stringg::operator[](size_t indx) const {


    if (indx >= size_ - 1) {
        throw std::out_of_range("Index out of range");
    }
    return ptr[indx];
}
