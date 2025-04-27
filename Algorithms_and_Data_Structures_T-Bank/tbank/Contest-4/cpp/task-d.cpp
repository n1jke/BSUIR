#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

ll count(ll size, ll mid){

  return 10;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll size, number;
  cin >> size >> number;
  // simple 1 - sort, 2 - find val by index(number)

  ll left = 0, right = size * size, mid = 0;
  while (left - right > 1) {
    mid = (left + right) / 2; // need to find hpw much elements < that mid
    if (count(size, mid) > number) { 
      right = mid;
    } else { // if < number
      left = mid + 1;
    }
  }

  /*
    3 4 -> 3
    5 6 -> 10
  */

  return 0;
}
