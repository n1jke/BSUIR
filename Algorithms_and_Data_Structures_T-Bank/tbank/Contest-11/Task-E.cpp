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

const ll MAXN = 105;
str dp[MAXN][MAXN];

str encode(const str& s, int l, int r) {
	ll len = r - l + 1;
	str res = s.substr(l, len);
	for (ll t = l; t < r; ++t) {
		str temp = dp[l][t] + dp[t + 1][r];
		if (temp.size() < res.size()) res = temp;
	}

	for (ll k = 1; k <= len / 2; ++k) {
		if (len % k != 0) continue;
		bool match = true;
		for (ll i = l; i <= r; ++i) {
			if (s[i] != s[l + (i - l) % k]) {
				match = false;
				break;
			}
		}
		if (match) {
			ll times = len / k;
			str tmplt = dp[l][l + k - 1];
			str candidate = to_string(times) + "(" + tmplt + ")";
			if (candidate.size() < res.size()) res = candidate;
		}
	}
	return dp[l][r] = res;
}

str findShortest(str& input) {
	ll n = input.length();
	for (ll len = 1; len <= n; ++len) {
		for (ll l = 0; l + len - 1 < n; ++l) {
			ll r = l + len - 1;
			dp[l][r] = encode(input, l, r);
		}
	}
	return dp[0][n - 1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	str input;
	getline(cin, input);
	cout << findShortest(input) << '\n';

	return 0;
}
