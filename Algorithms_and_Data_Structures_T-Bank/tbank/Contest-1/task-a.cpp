#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
#define ld long double
#define vector std::vector
#define string std::string

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    while (k--) {
        long long x;
        std::cin >> x;
        if (std::binary_search(arr.begin(), arr.end(), x))
            std::cout << "YES" << "\n";
        else
            std::cout << "NO" << "\n";
    }
    
    return 0;
}
