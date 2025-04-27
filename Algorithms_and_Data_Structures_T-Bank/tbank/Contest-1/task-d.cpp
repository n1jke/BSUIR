#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
#define ld long double
using namespace std;


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ld C;
  cin >> C;
  ld min  = 0.0;
  ld high = sqrt(C);
    
  for (int iter = 0; iter < 50; ++iter) {
    ld mid = (min + high) / 2.0;
    ld f = mid * mid + sqrt(mid + 1);
    if (f < C)
        min = mid;
    else
        high = mid;
  }

  cout << fixed << setprecision(20) << (min + high) / 2 << "\n";

  return 0;
}
