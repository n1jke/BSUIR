#ifndef STRING_STRING_H
#define STRING_STRING_H

#include <cstddef>
#include <memory>

namespace sml
{
  class stringg {

    std::unique_ptr<char[]> ptr;
    size_t capacity_ = 0;
    size_t size_ = 0;

  public:
    stringg();

    stringg(const char* str);

    stringg(size_t count, char c);

    stringg(const stringg& other);

    stringg(stringg&& other) ;

    stringg &operator=(const stringg &other);

    stringg &operator=(stringg &&other) noexcept;

    ~stringg() = default;

    char &operator[](size_t indx) const;

    void resize(size_t _size);

    void reserve(size_t _size);

    bool empty() const;

    size_t size() const;

    size_t capacity() const;

    char& front();

    char& back();

    void clear();

    void erase(size_t pos, size_t len);

    void push_back(char c);

    void pop_back();

    void insert(size_t pos, const char* str);

    void append(const char* str);

    void append(const stringg &str);

    friend stringg operator+(const stringg &left, const stringg &right);

    friend stringg operator+(const stringg &left, char right);

    static void* memcpy_sml(void* s1, const void* s2, size_t n);

    static void* memmove_sml(void* s1, const void* s2, size_t n);

    static char* strcpy_sml(char* s1, const char* s2);

    static char* strncpy_sml(char* s1, const char* s2, size_t n);

    static char* strcat_sml(char* s1, const char* s2);

    static char* strncat_sml(char* s1, const char* s2, size_t n);

    static int memcmp_sml(const void* s1, const void* s2, size_t n);

    static int strcmp_sml(const char* s1, const char* s2);

    static int strcoll_sml(const char* s1, const char* s2);

    static int strncmp_sml(const char* s1, const char* s2, size_t n);

    static char* strxfrm_sml(char* s1, const char* s2, size_t n);

    static char* strtok_sml(char* s1, const char* s2);

    static char* strchr_sml(const char* s, int c);

    static void* memset_sml(void* s, int c, size_t n);

    static char* strerror_sml(int errnum);

    static size_t strlen_sml(const char* s);
  };
}

#endif //STRING_STRING_H
