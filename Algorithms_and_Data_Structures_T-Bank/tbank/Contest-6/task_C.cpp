#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("tune=native")
#pragma GCC target("avx2")

#define ll long long
#define ld long double
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb push_back

constexpr ll mod = 1e9 + 7;
constexpr ll mod2 = 1e9 + 9;
constexpr ll pInf = std::numeric_limits<ll>::max();
constexpr ll mInf = std::numeric_limits<ll>::min();
const ll base = 31;
const ll base1 = 67, base2 = 71;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  vector<pair<ll,ll>> graph(m);// all edges
  vll check(n + 1);

  for (ll i = 0; i < m; ++i) {
    cin >> graph[i].first >> graph[i].second;
  }

  for (ll i = 1; i <= n; ++i) {
    cin >> check[i];
  }

  vll positions(n + 1);
  for (ll i = 1; i <= n; ++i) {
    positions[check[i]] = i;
  }

  bool isOkay = true;
  for (ll i = 0; i < m; ++i) {
    ll needLeft = graph[i].first;
    ll needRight = graph[i].second;

    if (positions[needRight] < positions[needLeft]) {
      isOkay = false;
      break;
    }
  }

  cout << '\n';
  if (isOkay) {
    cout << "YES" << '\n';
  } else {
    cout << "NO" << '\n';
    }


  return 0;
}