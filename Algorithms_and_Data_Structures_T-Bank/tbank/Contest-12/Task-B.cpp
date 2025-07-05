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
#define pb push_back

map<ll,ll> factorize(ll num) {
  map<ll,ll> factors;

  for (ll i = 2; i * i <= num; ++i) {
    while (num % i == 0) {
      factors[i]++;
      num /= i;
    }
  }

  if (num != 1) {
    factors[num]++;
  }

  return factors;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll num;
  cin >> num;
  map<ll,ll> factors = factorize(num);

  bool flag = false;
  for (auto [n, pow] : factors) {
    if (flag) cout << '*';
    if (pow == 1) {
      cout << n;
      flag = true;
    }
    else {
      cout << n << '^' << pow ;
      flag = true;
    }
  }

  return 0;
}