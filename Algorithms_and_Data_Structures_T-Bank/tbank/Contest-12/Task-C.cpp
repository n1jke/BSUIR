#include <bits/stdc++.h>
using namespace std;

#define ll  long long
#define ld long double
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb emplace_back


vll resheto(ll target) {
  vll res;
  vector<int> is_prime(target + 1, true);

  for (ll i = 2; i <= target; ++i) {
    if (is_prime[i]) {
      res.pb(i);
    }
    for (auto p : res) {
      if (i * p > target) break;
      is_prime[i * p] = false;
      if (i % p == 0) break;
    }
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll target;
  cin >> target;

  if (target == 4) {
    cout << 2 << ' ' << 2;
    return 0;
  }

  auto primes = resheto(target);
  ll l = 0, r = primes.size() - 1;
  bool found = false;
  while (l <= r) {
    ll sum = primes[l] + primes[r];
    if (sum == target) {
      found = true;
      break;
    } else if (sum < target) {
      ++l;
    } else {
      --r;
    }
  }

  if (primes[l] < primes[r]) cout << primes[l] << " " << primes[r];
  else cout << primes[r] << " " << primes[l];

  return 0;
}