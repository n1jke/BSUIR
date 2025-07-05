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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll size;
	cin >> size;
	vll height(size);
	for (auto& i : height) cin >> i;
	height.pb(0);

	ll best = height[0];
	stack<ll> stk;

	for (ll i = 0; i <= size; ++i) {
		while (!stk.empty() && height[i] < height[stk.top()]) {
			ll h = height[stk.top()];
			stk.pop();
			ll left = stk.empty() ? 0 : stk.top() + 1;
			ll width = i - left; // right = i - 1
			best = max(best, width * h);
		}
		stk.push(i);
	}

	cout << best;

	return 0;
}