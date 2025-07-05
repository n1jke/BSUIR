#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb push_back

set<ll> resheto(ll n) {
	set<ll> primes;
	vector<bool> isprime(n + 1, true);
	isprime[0] = isprime[1] = false;
	for (ll i = 2; i <= n; ++i) {
		if (isprime[i]) {
			primes.insert(i);
			for (ll j = i * i; j <= n; j += i) {
				isprime[j] = false;
			}
		}
	}
	return primes;
}


constexpr ll MOD = pow(10,9) + 9;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll len;
	cin >> len;

	set<ll> primes = resheto(1000);
	vector go(10, vector<vll>(10)); //xyz go[x][y] -- all z that xyz prime

	for (ll num = 100; num < 1000; ++num) {
		if (primes.find(num) != primes.end()) {
			ll a = (num / 100) % 10;
			ll b = (num / 10) % 10;
			go[a][b].pb(num % 10);
		}
	}

	//dp init
	vector dp(len + 1, vector(10, vll(10,0))); //  dp[len][x][y] pass with len  and lst2 is xy
	for (ll num = 100; num < 1000; ++num) {
		if (primes.find(num) != primes.end()) {
			ll b = (num / 10) % 10;
			ll c = num % 10;
			dp[3][b][c] = (dp[3][b][c] + 1) % MOD;
		}
	}

	for (ll l = 4; l <= len; ++l) {
		for (ll x = 0; x < 10; ++x) {
			for (ll y = 0; y < 10; ++y) {
				for (auto z : go[x][y]) {
					dp[l][y][z] = (dp[l][y][z] + dp[l - 1][x][y]) % MOD; // know: if add for pss len - 1 with lst2 is xy can add z if xyz prime
				}
			}
		}
	}

	ll res = 0;
	for (ll x = 0; x < 10; ++x) {
		for (ll y = 0; y < 10; ++y) {
			res = (res + dp[len][x][y]) % MOD;
		}
	}
	cout <<  res;
	return 0;
}