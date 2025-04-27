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

pair<vll,vll> computeHash(const string& input)
{
    ll size = input.size();
    vll hash(size + 1, 0), pow(size + 1, 1);

    for (ll i = 1; i <= size; i++)
    {
        ll x = (int) (input[i - 1] - 'a' + 1);
        pow[i] = (pow[i - 1] * base) % MOD;
        hash[i] = (hash[i - 1] * base + x) % mod;
    }

    return {hash, pow};
}

ll getHash(ll left, ll right, vll& hashh, vll&pow)
{
    return (hashh[right] - hashh[left - 1] * pow[right - left + 1] % mod + mod) % mod;
}

void solve(str& input)
{
    input += input;
    ll len = input.length() / 2;
    ll bestIndx = 0;

    for (ll indx = 1, comp = 0; indx < len; ++indx)
    {
        while (comp < len && input[bestIndx + comp] == input[indx + comp]) ++comp;
        if (comp == len) break;
        if (input[indx + comp] < input[bestIndx + comp]) bestIndx = indx;
        comp = 0;
    }

    str res  = input.substr(bestIndx, len);
    cout << res << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    str input;
    cin >> input;
    solve(input);

    return 0;
}

