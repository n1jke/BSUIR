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

ll damerauLevenshtein(str& s, str& t) {
    ll m = s.size(), n = t.size();
    vector<vll> d(m + 1, vll(n + 1, 0));

    d[0][0] = 0;
    for (ll i = 1; i <= m; ++i){
        d[i][0] = d[i - 1][0] + 1;
    }
    for (ll j = 1; j <= n; ++j){
        d[0][j] = d[0][j - 1] + 1;
    }

    for (ll i = 1; i <= m; ++i) {
        for (ll j = 1; j <= n; ++j) {
            if (s[i - 1] == t[j - 1]){
                d[i][j] = d[i - 1][j - 1];
            }
            else{
                d[i][j] = d[i - 1][j - 1] + 1;
            }
            d[i][j] = min({d[i][j], d[i - 1][j] + 1, d[i][j - 1] + 1});

            if (i > 1 && j > 1 && s[i - 1] == t[j - 2] && s[i - 2] == t[j - 1]){
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + 1);
            }
        }
    }

    return d[m][n];
}

int main() {
    str s, t;
    cin >> s >> t;
    cout << damerauLevenshtein(s, t);

    return 0;
}
