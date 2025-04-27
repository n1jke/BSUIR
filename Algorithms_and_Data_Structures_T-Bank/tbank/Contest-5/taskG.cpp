#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("tune=native")
#pragma GCC target("avx2")

#define ll long long
#define ld long double
//#define str string
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

std::mt19937 my_rand(2838383);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin >> n;
    unordered_map<ll, ll> hash;

    vll a(n), fHash(n + 1, 0);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        if (hash.find(a[i]) == hash.end())
        {
            hash[a[i]] = my_rand();
        }
    }

    ll m;
    cin >> m;
    vll b(m), sHash(m + 1);
    for (ll i = 0; i < m; i++) {
        cin >> b[i];
        if (hash.find(b[i]) == hash.end())
        {
            hash[b[i]] = my_rand();
        }
    }

    for (ll i = 0; i < n; ++i)
    {
        fHash[i + 1] = fHash[i] + hash[a[i]];
    }
    for (ll i = 0; i < m; ++i)
    {
        sHash[i + 1] = sHash[i] + hash[b[i]];
    }


    for (ll len = min(n, m); len > 0; --len)
    {
        unordered_set<ll> seen;

        for (ll i = 0; i + len <= m; ++i)
        {
            seen.insert(sHash[i + len] - sHash[i]);
        }

        for (ll j = 0; j + len  <= n; ++j)
        {
            if (seen.count(fHash[ j+ len] - fHash[j]))
            {
                cout << len << '\n';
                return 0;
            }
        }
    }

    cout << 0 << '\n';

    return 0;
}