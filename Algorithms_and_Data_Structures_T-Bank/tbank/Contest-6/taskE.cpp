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

  ll K;
  cin >> K;
  const ll INF = 1e9;
  vll dist(K, INF);

  priority_queue<pll, vector<pll>, greater<pll>> pq;

  for (ll d = 1; d <= 9; d++) {
    ll rem = d % K;
    if (dist[rem] > d) {
      dist[rem] = d;
      pq.push({d, rem});
    }
  }

  // Аdijkastra
  while (!pq.empty()) {
    auto [sum, r] = pq.top();
    pq.pop();

    if (r == 0) {
      cout << sum << "\n";
      return 0;
    }

    if (sum > dist[r])
      continue;

    //add num in right side
    for (ll d = 0; d <= 9; d++) {
      ll nr = (r * 10 + d) % K;
      ll nsum = sum + d;
      if (nsum < dist[nr]) {
        dist[nr] = nsum;
        pq.push({nsum, nr});
      }
    }
  }
  
  return 0;
}
