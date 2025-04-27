#ifndef SORTINGS_H_
#define SORTINGS_H_

#include <vector>
#include <functional>

class Sortings {
   public:
    static void heapSort(std::vector<long long>& array,
                         const std::function<void(int, int)>& onSwap = nullptr);

    static void quickSort(std::vector<long long>& arr, long long low,
                          long long high,
                          const std::function<void(int, int)>& onSwap = nullptr);

    static void mergeSort(std::vector<long long>& arr, long long left,
                          long long right,
                          const std::function<void(int, int)>& onSwap = nullptr);

    static void interpolationSort(std::vector<long long>& array, long long low,
                                  long long high,
                                  const std::function<void(int, int)>& onSwap = nullptr);

    static long long binPow(long long num, long long pow, long long mod);

    static long long binSearch(const std::vector<long long>& arr,
                               long long digit);

    static void heapDown(std::vector<long long>& array, long long distance,
                         long long root,
                         const std::function<void(int, int)>& onSwap = nullptr);

    static long long partition(std::vector<long long>& arr, long long low,
                               long long high,
                               const std::function<void(int, int)>& onSwap = nullptr);

    static void merge(std::vector<long long>& array, long long left,
                      long long mid, long long right,
                      const std::function<void(int, int)>& onSwap = nullptr);
};

#endif	// SORTINGS_H_
