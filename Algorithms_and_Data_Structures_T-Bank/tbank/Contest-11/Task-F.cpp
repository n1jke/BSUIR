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

vll best, current, cost;
ll minCount = 21;

void dfs(ll i, ll sum, ll count, ll target) {
	if (sum > target) return;
	if (i == cost.size()) {
		if (sum == target && count < minCount) {
			minCount = count;
			best = current;
		}
		return;
	}
	for (short use = 0; use <= 2; ++use) {
		current[i] = use;
		dfs(i + 1, sum + cost[i] * use, count + use, target);
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll price, count;
	cin >> price >> count;
	ll ms = 0, temp;
	for (ll i = 0; i < count; i++) {
		cin >> temp;
		if (temp <= price) {
			cost.pb(temp);
			ms += temp * 2;
		}
	}
	ll sz = cost.size();
	best.resize(sz), current.resize(sz);

	if (ms < price) {
		cout << -1;
	} else {
		dfs(0, 0, 0, price);
		if (minCount == 21) cout << 0;
		else {
		cout << minCount << '\n';
		for (ll i = 0; i < sz; i++) {
			if (best[i] == 0) continue;
			if (best[i] == 1) {
				cout << cost[i] << ' ';
			} else {
				cout << cost[i] << ' ' << cost[i] << ' ';
			}
		}
		}
	}

	return 0;
}