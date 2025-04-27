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

constexpr ll MOD = 1E18;
constexpr ll mod = 1e9 + 7;
constexpr int maxn = 1e5+1;
const ll base = 31;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    str input;
    cin >> input;

    ll  k = static_cast<int>(input.length());
    vll hash(k + 1, 0);
    vll p(k + 1 , 1); // pow of every
    for (int i = 1; i <= k ; ++i)
    {
        p[i] = (p[i-1] * base) % mod;
        ll x = (int) (input[i - 1] - 'a' + 1);
        hash[i] = (hash[i - 1] * base + x) % mod;
    }

    ll test;
    cin >> test;
    for ( ; test; test--)
    {
        ll ff, fs, sf, ss;
        cin >> ff >> fs >> sf >> ss;
        ff--; fs--; sf--; ss--;

        ll len = fs - ff + 1;

        ll hashF = (hash[fs + 1] - (hash[ff] * p[len]) % mod + mod) % mod;
        ll hashS = (hash[ss + 1] - (hash[sf] * p[len]) % mod + mod) % mod;

        /*
        ll hashF = (hash[fs + 1] - hash[ff] + mod)  % mod;
        hashF = (hashF * p[k - fs - 1]) % mod;
        ll hashS = (hash[ss + 1] - hash[sf] + mod)  % mod;
        hashS = (hashS * p[k - ss - 1]) % mod;
        */
        (hashF == hashS) ? cout << "Yes\n" : cout << "No\n";
    }
}
