#include "slice.h"
#include <string>

/*
 * This file contains explicit template instantiations for sml:: slice library.
 *
 * Templates in C++ compiled when actually used (instantiated) in code,
 * for static library 'slice ', im provide pre-compiled versions of common types
 * so users don't need to include the full template definitions.
 * Each "template class slice<Type>" line tells the compiler to generate all the
 * code for that specific type instantiation and include it in the library.
 * 
 * PS "Without explicit instantiations, slice library would not contain
 * any actual compiled code for these templates".
 */

// explicit template instantiations for slice
template class sml::slice<int>;
template class sml::slice<unsigned int>;
template class sml::slice<long>;
template class sml::slice<unsigned long>;
template class sml::slice<long long>;
template class sml::slice<unsigned long long>;
template class sml::slice<float>;
template class sml::slice<double>;
template class sml::slice<long double>;
template class sml::slice<std::string>;

// explicit instantiations for iterator class
template class sml::Iterator<int>;
template class sml::Iterator<unsigned int>;
template class sml::Iterator<long>;
template class sml::Iterator<unsigned long>;
template class sml::Iterator<long long>;
template class sml::Iterator<unsigned long long>;
template class sml::Iterator<float>;
template class sml::Iterator<double>;
template class sml::Iterator<long double>;
template class sml::Iterator<std::string>;

// explicit instantiations for allocator class
template class sml::Allocator<int>;
template class sml::Allocator<unsigned int>;
template class sml::Allocator<long>;
template class sml::Allocator<unsigned long>;
template class sml::Allocator<long long>;
template class sml::Allocator<unsigned long long>;
template class sml::Allocator<float>;
template class sml::Allocator<double>;
template class sml::Allocator<long double>;
template class sml::Allocator<std::string>;
