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
vll tree[MAXN];
ll up[MAXN][LOG];
ll tin[MAXN], tout[MAXN], depth[MAXN];
ll timer;

void dfs(ll v, ll p) {
	tin[v] = ++timer;
	up[v][0] = p;
	for (ll j = 1; j < LOG; ++j) {
		up[v][j] = up[ up[v][j-1] ][ j-1 ];
	}
	for (ll u : tree[v]) if (u != p) {
		depth[u] = depth[v] + 1;
		dfs(u, v);
	}
	tout[v] = ++timer;
}

inline bool is_ancestor(ll a, ll b) {
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

ll lca(ll a, ll b) {
	if (is_ancestor(a, b)) return a;
	if (is_ancestor(b, a)) return b;
	for (ll j = LOG-1; j >= 0; --j) {
		if (!is_ancestor(up[a][j], b))
			a = up[a][j];
	}
	return up[a][0];
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

	vector<bool> has_parent(n, false);
	for (ll i = 1; i < n; ++i) {
		ll p;
		cin >> p;
		tree[p].push_back(i);
		tree[i].push_back(p);
		has_parent[i] = true;
	}

	ll root = 0;
	while (root < n && has_parent[root]) ++root;
	dfs(root, root);

	ll q;
	cin >> q;
	while (q--) {
		ll u, v;
		cin >> u >> v;
		if (u < 0 || u >= n || v < 0 || v >= n) {
		} else {
			cout << lca(u, v) << '\n';
		}
	}

	return 0;
}
