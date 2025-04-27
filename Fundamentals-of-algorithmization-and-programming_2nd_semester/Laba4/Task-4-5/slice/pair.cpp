#include "pair.h"
#include "slice.h"
#include <string>

// basic pair instantiations
template class sml::pair<int, int>;
template class sml::pair<int, double>;
template class sml::pair<double, int>;
template class sml::pair<double, double>;
template class sml::pair<std::string, int>;
template class sml::pair<int, std::string>;
template class sml::pair<std::string, std::string>;
template class sml::pair<sml::slice<int>, sml::slice<int>>;
template class sml::pair<sml::slice<double>, sml::slice<double>>;
template class sml::pair<sml::slice<std::string>, sml::slice<std::string>>;

template class sml::pair<sml::pair<int, int>, sml::pair<int, int>>;
template class sml::pair<sml::pair<double, double>, sml::pair<double, double>>;
template class sml::pair<sml::pair<int, double>, sml::pair<int, double>>;
template class sml::pair<sml::slice<int>, sml::slice<sml::pair<int, double>>>;