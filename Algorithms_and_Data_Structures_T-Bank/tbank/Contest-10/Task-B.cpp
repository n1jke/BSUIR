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

class DSU {
	vll parents, size;

public:
	DSU(size_t sz) {
		++sz;
		parents.resize(sz);
		size.resize(sz, 1);
		for (size_t i = 0; i < sz; i++) {
			parents[i] = i;
		}
	}

	bool merge(ll first, ll second) {
		ll f = find(first);
		ll s = find(second);

		if (f == s) return false;
		else {
			if (size[f] < size[s]) parents[f] = s;
			else if (size[s] < size[f]) parents[s] = f;
			else {
				parents[f] = s;
				++size[s];
			}

			return true;
		}
	}

	ll find(ll val) {
		if (val != parents[val]) parents[val] = find(parents[val]);
		return parents[val];
	}

};

struct edge {
	ll a, b, len;

	bool operator<(const edge &other) const {
		return len < other.len;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll countV, countE;
	cin >> countV >> countE;

	vector<edge> edges(countE);
	for (auto& e : edges) {
		cin >> e.a >> e.b >> e.len;
	}
	sort(edges.begin(), edges.end());

	ll min_weight = 0;
	DSU dsu(countV);

	for (auto e : edges) {
		if (dsu.merge(e.a, e.b)) {
			min_weight += e.len;
		}
	}
	cout << min_weight << '\n';

	return 0;
}