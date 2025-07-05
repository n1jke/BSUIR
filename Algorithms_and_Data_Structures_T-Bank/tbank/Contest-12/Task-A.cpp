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

ll gcd(ll f, ll s) {
	// if (s == 0) return f;
	// return gcd(s, f % s);
	while (s > 0) {
	    f %= s;
		swap(f, s);
	}
	return f;
}

ll lcm(ll f, ll s) {
	return f * s / gcd(f, s);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll first, second;
	cin >> first >> second;
	// find lcm

	cout << lcm(first, second);

	return 0;
}