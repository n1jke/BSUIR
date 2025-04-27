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


#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<ll>

void dfs(vector<vll>& graph, vector<bool>& used, vector<vll>& comp, ll vert, ll cNum) {
  used[vert] = true;
  comp[cNum].pb(vert);

  for (auto& v : graph[vert]) {
    if (!used[v]) {
      dfs(graph, used, comp, v, cNum);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  vector<bool> used(n + 1);
  vector<vll> graph(n + 1);
  vector<vll> comp(n);

  // Чтение графа
  for (ll i = 0; i < m; i++) {
    ll first, second;
    cin >> first >> second;
    graph[first].pb(second);
    graph[second].pb(first);  // неориентированный граф
  }

  ll compCount = 0;
  for (ll i = 1; i <= n; i++) {
    if (!used[i]) {
      dfs(graph, used, comp, i, compCount);
      sort(comp[compCount].begin(), comp[compCount].end());
      compCount++;
    }
  }

  cout << compCount << '\n';
  for (ll i = 0; i < compCount; i++) {
    cout << comp[i].size() << '\n';
    for (auto v : comp[i]) {
      cout << v << ' ';
    }
    cout << '\n';
  }

  return 0;
}