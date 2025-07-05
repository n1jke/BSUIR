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
	vll parents, size, minElem, maxElem;

public:
	DSU(size_t sz) {
		++sz;
		parents.resize(sz);
		size.resize(sz, 1);
		minElem.resize(sz);
		maxElem.resize(sz);
		for (size_t i = 0; i < sz; i++) {
			parents[i] = i;
			minElem[i] = i;
			maxElem[i] = i;
		}
	}

	void union_set(ll first, ll second) {
		ll f = find(first);
		ll s = find(second);
		if (f == s) return;

		if (size[f] < size[s]) std::swap(f, s); // keep size1 >= size2

		parents[s] = f;
		size[f] += size[s];
		minElem[f] = min(minElem[f],minElem[s]);
		maxElem[f] = max(maxElem[f],maxElem[s]);
	}

	ll find(ll val) {
		if (val != parents[val]) parents[val] = find(parents[val]);
		return parents[val];
	}

	void get_info(ll val) {
		ll root = find(val);
		cout << minElem[root] << " " << maxElem[root]  << " " << size[root] << '\n';
	}

};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll size, count;
	cin >> size >> count;
	str type;
	ll first, second;

	DSU dsu(size);
	for (ll i = 0; i < count; i++) {
		cin >> type;
		if (type == "union") {
			cin >> first >> second;
			dsu.union_set(first , second);
		} else { // get
			cin >> first;
			dsu.get_info(first );
		}
	}

	return 0;
}
