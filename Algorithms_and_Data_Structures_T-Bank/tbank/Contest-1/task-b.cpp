#include <iostream>
#include <vector>
#define ll long long
#define ld long double
using namespace std;

ll findingNum(const vector<ll>& in, ll num) {
  ll left = 0, right = in.size() - 1;
  ll closest = in[0];

  while (left <= right) {
    ll mid = left + (right - left) / 2;
    if (in[mid] == num) {
      return num;
    }
    
    if (abs(in[mid] - num) < abs(closest - num) || (abs(in[mid] - num) == abs(closest - num) && in[mid] < closest)) {
      closest = in[mid];
    }

    if (in[mid] > num) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

    return closest;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<ll> in(n), find(k);

    for (ll i = 0; i < n; ++i) {
        cin >> in[i];
    }

    for (ll i = 0; i < k; ++i) {
        cin >> find[i];
    }

    for (ll i = 0; i < k; ++i) {
        cout << findingNum(in, find[i]) << '\n';
    }

    return 0;
}
