#include "sortings.h"


void Sortings::heapSort(std::vector<long long>& array,
                        const std::function<void(int, int)>& onSwap) {
    size_t size = array.size();


    for (long long i = size / 2 - 1; i >= 0; --i) {
        heapDown(array, size, i, onSwap);
    }


    for (long long i = size - 1; i > 0; --i) {
        if (onSwap) {
            onSwap(0, i);
        }
        std::swap(array[0], array[i]);
        heapDown(array, i, 0, onSwap);
    }
}

void Sortings::quickSort(std::vector<long long>& arr, long long low,
                         long long high,
                         const std::function<void(int, int)>& onSwap) {


    if (low < high) {
        long long pi = partition(arr, low, high, onSwap);
        quickSort(arr, low, pi - 1, onSwap);
        quickSort(arr, pi + 1, high, onSwap);
    }
}

void Sortings::mergeSort(std::vector<long long>& arr, long long left,
                         long long right,
                         const std::function<void(int, int)>& onSwap) {


    if (left < right) {
        long long mid = (left + right) / 2;

        mergeSort(arr, left, mid, onSwap);
        mergeSort(arr, mid + 1, right, onSwap);

        merge(arr, left, mid, right, onSwap);
    } else {
        return;
    }
}

void Sortings::interpolationSort(std::vector<long long>& array, long long low,
                                 long long high,
                                 const std::function<void(int, int)>& onSwap) {


    if (high <= low) {
        return;
    }

    long long min = array[low];
    long long max = array[low];


    for (long long i = low; i <= high; ++i) {
        if (array[i] < min) {
            min = array[i];
        } else if (array[i] > max) {
            max = array[i];
        }
    }


    if (min == max) {
        return;	 // all elements same
    }

    long long bucket_count = high - low + 1;
    std::vector<std::vector<long long>> buckets(bucket_count);


    for (long long i = low; i <= high; ++i) {
        // devide into buckets
        long long curr = array[i];
        long long bucket = static_cast<long long>(
            static_cast<double>(curr - min) / (max - min) * (bucket_count - 1));
        buckets[bucket].push_back(curr);
    }

    long long curr_position = low;


    for (long long i = 0; i < bucket_count; ++i) {
        if (!buckets[i].empty()) {
            long long buck_start = curr_position;
            for (auto& el : buckets[i]) {
                // visual
                if (onSwap && curr_position != (low + &el - &buckets[i][0])) {
                    onSwap(curr_position, low + &el - &buckets[i][0]);
                }
                array[curr_position++] = el;
            }
            // sort for bucket
            interpolationSort(array, buck_start, curr_position - 1, onSwap);
        }
    }
}

long long Sortings::binPow(long long num, long long pow, long long mod) {
    long long result = 1;


    while (pow) {
        if (pow & 1) {	// check first bit ==(pow % 2 == 1)
            result = (result * num) % mod;
        }
        num = (num * num) % mod;
        pow >>= 1;	// devide by 2
    }

    return result;
}
/*


if (pow == 0){
    return 1;
}

num %= mod;


if (pow % 2 == 1){
    long long temp =  binPow(num, pow - 1) * num;
    return (temp * num) % mod;
}
else {
    long long b = binPow(num, pow / 2, mod);
    return (b * b) % mod;
}
*/

long long Sortings::binSearch(const std::vector<long long>& arr,
                              long long digit) {
    long long left = 0;
    long long right = arr.size() - 1;


    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (arr[mid] == digit) {
            return mid;
        } else if (arr[mid] < digit) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}


void Sortings::heapDown(std::vector<long long>& array, long long distance,
                        long long root,
                        const std::function<void(int, int)>& onSwap) {
    long long large = root;
    long long left = 2 * root + 1;
    long long right = 2 * root + 2;


    if (left < distance && array[left] > array[large]) {
        large = left;
    }


    if (right < distance && array[right] > array[large]) {
        large = right;
    }


    if (large != root) {
        if (onSwap) {
            onSwap(root, large);
        }
        std::swap(array[root], array[large]);
        heapDown(array, distance, large, onSwap);
    }
}

long long Sortings::partition(std::vector<long long>& arr, long long low,
                              long long high,
                              const std::function<void(int, int)>& onSwap) {
    long long pivot = arr[high];
    long long i = (low - 1);


    for (long long j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            if (onSwap) {
                onSwap(i, j);
            }
            std::swap(arr[i], arr[j]);
        }
    }


    if (onSwap) {
        onSwap(i + 1, high);
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void Sortings::merge(std::vector<long long>& array, long long left,
                     long long mid, long long right,
                     const std::function<void(int, int)>& onSwap) {
    std::vector<long long> left_a(mid - left + 1);
    std::vector<long long> right_a(right - mid);

    for (size_t i = 0; i < left_a.size(); ++i) {
        left_a[i] = array[left + i];
    }

    for (size_t j = 0; j < right_a.size(); ++j) {
        right_a[j] = array[mid + 1 + j];
    }

    size_t i = 0;
    size_t j = 0;
    long long m = left;

    while (i < left_a.size() && j < right_a.size()) {


        if (left_a[i] <= right_a[j]) {
            // visual
            if (onSwap && (size_t)m != (size_t)left + i) {
                onSwap(m, left + i);
            }
            array[m] = left_a[i];
            ++i;
        } else {
            // visual
            if (onSwap && (size_t)m != (size_t)mid + 1 + j) {
                onSwap(m, mid + 1 + j);
            }
            array[m] = right_a[j];
            ++j;
        }

        ++m;
    }

    while (i < left_a.size()) {
        // other el visual


        if (onSwap && (size_t)m != (size_t)left + i) {
            onSwap(m, left + i);
        }
        array[m] = left_a[i];
        ++i;
        ++m;
    }

    while (j < right_a.size()) {
        // visual othr el of right subarray


        if (onSwap && (size_t)m != (size_t)mid + 1 + j) {
            onSwap(m, mid + 1 + j);
        }
        array[m] = right_a[j];
        ++j;
        ++m;
    }
}
