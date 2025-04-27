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
constexpr ll pInf = 1e9;
constexpr ll mInf = std::numeric_limits<ll>::min();
const ll base = 31;
const ll base1 = 67, base2 = 71;


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll city, roads;
  cin >> city >> roads;
  vector<vll> dist(city, vll(city, pInf));

  for (ll i = 0; i < roads; ++i) {
    ll f, s, t;
    cin >> f >> s >> t;
    --f, --s;
    dist[f][s] = t;
    dist[s][f] = t;
  }

  for (ll i = 0; i < city; i++) dist[i][i] = 0;

  for (ll i = 0; i < city; i++) {
    for (ll j = 0; j < city; j++) {
      for (ll k = 0; k < city; k++) {
        dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
      }
    }
  }


/*
  for (ll i = 0; i < city; i++) {
    for (ll j = 0; j < city; j++) {
      if (dist[i][j] == pInf) cout << "∞ ";
      else cout << dist[i][j] << " ";
    }
    cout << '\n';
  }
  */

  ll bestCity = 0;
  ll minmaxDist = pInf;

  for (ll i = 0; i < city; i++) {
    ll maxDist = 0;
    for (ll j = 0; j < city; j++) {
       maxDist = max(maxDist, dist[i][j]);
    }

    if (maxDist < minmaxDist)
    {
      minmaxDist = maxDist;
      bestCity = i;
    }
  }

  cout << bestCity + 1 << "\n";



  return 0;
}