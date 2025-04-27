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

int main() {
    int n, m;
    cin >> n >> m;
    vector<vll> dp(n + 1, vll(m + 1, 0));
    dp[1][1] = 1;

    for (int sum = 2; sum <= n + m; ++sum) {
        for (int i = 1; i <= n; i++) {
            int j = sum - i;
            if (j >= 1 && j <= m) {
                if (i - 1 >= 1 && j - 2 >= 1) dp[i][j] += dp[i - 1][j - 2];
                if (i - 2 >= 1 && j + 1 <= m) dp[i][j] += dp[i - 2][j + 1];
                if (i - 2 >= 1 && j - 1 >= 1) dp[i][j] += dp[i - 2][j - 1];
                if (i + 1 <= n && j - 2 >= 1) dp[i][j] += dp[i + 1][j - 2];
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}
