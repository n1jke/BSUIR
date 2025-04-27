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

ll minPrice(vll& prices){
    vll dp(prices.size());

    dp[0] = prices[0];
    dp[1] = prices[1];
    for (ll i = 2; i < prices.size(); ++i){
        dp[i] = min(dp[i - 1], dp[i - 2]) + prices[i];
    }

    return dp[prices.size() - 1];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll count;
    cin >> count;
    vll price (count);

    for (ll i = 0; i < count; ++i){
        cin >> price[i];
    }

    cout << minPrice(price) << '\n';

    return 0;
}
