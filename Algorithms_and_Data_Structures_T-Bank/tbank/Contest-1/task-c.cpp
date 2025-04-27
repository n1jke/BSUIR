#include <iostream>

using namespace std;

int query(int x) {
    cout << x << '\n';
    cout.flush();    
    
    string response;
    cin >> response;  
    return (response == ">=");
}

int main() {
    int n;
    cin >> n; 
    
    int L = 1, R = n;
    while (L < R) {
        int mid = (L + R + 1) / 2;
        if (query(mid)) {
            L = mid;  // x >= mid
        } else {
            R = mid - 1; // x < mid
        }
    }

    cout << "! " << L << '\n';
    cout.flush(); 
    return 0;
}
