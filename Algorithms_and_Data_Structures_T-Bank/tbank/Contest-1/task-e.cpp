#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
#define ld long double
using namespace std;


#include <iostream>
#include <iomanip>

using namespace std;

double f(double x, int a, int b, int c, int d) {
    return a*x*x*x + b*x*x + c*x + d;
}

int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  ld L = -1000, R = 1000;
  while (f(L, a, b, c, d) * f(R, a, b, c, d) > 0) {
    L *= 2;
    R *= 2;
  }

  // Метод бисекции (бинарного поиска)
  while (R - L > 1e-4) {
    double mid = (L + R) / 2;
    if (f(mid, a, b, c, d) * f(L, a, b, c, d) <= 0)
      R = mid;
    else
      L = mid;
  }

    cout << fixed << setprecision(20) << (L + R) / 2 << '\n';
    
    return 0;
}
