#ifndef SYNCHRONIZEDSLICEPAIR_H
#define SYNCHRONIZEDSLICEPAIR_H

#include "slice.h"
#include "pair.h"
#include <stdexcept>
#include <string>

class SynchronizedSlicePair {
public:
    sml::slice<int> first;
    sml::slice<sml::pair<int, double>> second;

    void push_back(int value, const sml::pair<int, double>& pair_value) {
        first.push_back(value);
        second.push_back(pair_value);
    }

    bool erase(size_t index) {
        if (index >= first.size() || index >= second.size()) {
            return false;
        }
        first.erase(first.data() + index);
        second.erase(second.data() + index);
        return true;
    }

    bool insert(size_t index, int value, const sml::pair<int, double>& pair_value) {
        if (index > first.size() || index > second.size()) {
            return false;
        }
        first.insert(first.data() + index, value);
        second.insert(second.data() + index, pair_value);
        return true;
    }

    void clear() {
        first.clear();
        second.clear();
    }

    size_t size() const { 
        return std::min(first.size(), second.size()); 
    }

    bool isSynchronized() const {
        return first.size() == second.size();
    }

    sml::pair<int, sml::pair<int, double>> at(size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return sml::pair<int, sml::pair<int, double>>(first[index], second[index]);
    }

    sml::pair<int, sml::pair<int, double>> operator[](size_t index) const {
        return sml::pair<int, sml::pair<int, double>>(first[index], second[index]);
    }
    
    void synchronize() {
        if (first.size() < second.size()) {
            while (first.size() < second.size()) {
                first.push_back(0); 
            }
        } else if (second.size() < first.size()) {
            while (second.size() < first.size()) {
                second.push_back(sml::pair<int, double>(0, 0.0));
            }
        }
    }
    
    std::string toString() const {
        std::string result = "First size: " + std::to_string(first.size()) + 
                             ", Second size: " + std::to_string(second.size()) + "\n";
        
        for (size_t i = 0; i < size(); ++i) {
            result += "[" + std::to_string(i) + "] = (" + 
                      std::to_string(first[i]) + ", (" + 
                      std::to_string(second[i].first) + ", " + 
                      std::to_string(second[i].second) + "))\n";
        }
        
        return result;
    }
};

#endif // SYNCHRONIZEDSLICEPAIR_H 