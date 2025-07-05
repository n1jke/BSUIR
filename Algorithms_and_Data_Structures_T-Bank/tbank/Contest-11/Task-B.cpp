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

const ll MAXN = 1e5 + 5;
const ll LOG  = 20;
const ll INF = 1e18;

vpll tree[MAXN];
ll up[MAXN][LOG];
ll minCost[MAXN][LOG];
ll tin[MAXN], tout[MAXN], depth[MAXN];
ll timer = 0;

void dfs(ll v, ll p, ll cost) {
	tin[v] = ++timer;
	up[v][0] = p;
  minCost[v][0] = cost;

	for (ll j = 1; j < LOG; ++j) {
		up[v][j] = up[up[v][j-1]][ j-1 ];
    minCost[v][j] = min(minCost[v][j - 1], minCost[up[v][j - 1]][j - 1]);
	}

	for (auto [u, c] : tree[v]) if (u != p) {
		depth[u] = depth[v] + 1;
		dfs(u, v, c);
	}
	tout[v] = ++timer;
}

inline bool is_ancestor(ll a, ll b) {
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

ll lcaMinCost(ll first, ll second) {
	if (depth[first] < depth[second]) swap(first, second);
  ll res = INF;

  for (ll i = LOG - 1; i >= 0; --i) {
		if (depth[first]  - pow(2, i) >= depth[second]) {
    	res = min(res, minCost[first][i]);
      first = up[first][i];
		}
  }

  if (first == second) return res;

  for (ll i = LOG - 1; i >= 0; --i) {
    if (up[first][i] != up[second][i]) {
      res = min({res, minCost[first][i], minCost[second][i]});
      first = up[first][i];
      second = up[second][i];
    }
	}
  return  min({res, minCost[first][0], minCost[second][0]});
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;

	for (ll i = 0; i < n; ++i) {
		tree[i].clear();
		tin[i] = tout[i] = depth[i] = 0;
		for (ll j = 0; j < LOG; ++j)
			up[i][j] = 0;
	}
	timer = 0;

	// root -> 0 always
  ll parent, cost;
  for (ll i = 1; i < n ; ++i) {
    cin >> parent >> cost;
    tree[parent].pb({i, cost});
    tree[i].pb({parent, cost});
  }
	dfs(0, 0, INF);

	ll q;
	cin >> q;
	while (q--) {
		ll u, v;
		cin >> u >> v;
		if (u < 0 || u >= n || v < 0 || v >= n) {
		} else {
			cout << lcaMinCost(u, v) << '\n';
		}
	}

	return 0;
}
