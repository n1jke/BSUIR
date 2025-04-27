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

ll solve(ll size){
    vector<vll> dp(size, vll(3)); // dp[i][end by: a,b,c] = count good comb with i size

    dp[0][0] = 1;
    dp[0][1] = 1;
    dp[0][2] = 1;

    for (ll i = 1; i < size; ++i){
        dp[i][0] = dp[i - 1][1] + dp[i - 1][2];
        dp[i][1] = dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2];
        dp[i][2] = dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2];
    }

    return   dp[size - 1][0] + dp[size - 1][1] + dp[size - 1][2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   ll size;
   cin >> size;
   cout << solve(size);

    return 0;
}
