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

bool dfs(vector<bool>& used, vector<vll>& graph, vector<bool>& inStack, ll vert)
{
  used[vert] = true;
  inStack[vert] = true;

  for (auto& v : graph[vert])
  {
    if (!used[v])
    {
      if (dfs(used, graph, inStack, v))
      {
        return true;
      }
    } else if (inStack[v])
    {
      return true;
    }
  }

  inStack[vert] = false;
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  vector<bool> used(n + 1, false);
  vector<vll> graph(n + 1);
  vector<bool> inStack(n + 1, false);

  for (ll i = 0; i < m; i++) {
    ll first, second;
    cin >> first >> second;
    graph[first].pb(second);
  }

  bool find = false;
  for (ll i = 1; i <= n; ++i)
  {
    if (!used[i])
    {
      if (dfs(used, graph, inStack, i))
      {
        cout << "1\n";
        return 0;
      }
    }
  }
  cout << "0\n";

  return 0;
}