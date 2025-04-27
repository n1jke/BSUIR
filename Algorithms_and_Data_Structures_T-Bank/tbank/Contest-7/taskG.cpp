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

str rebuild(ll left, ll right, str& base, vector<vll>& dp, vector<vll>& includ){
    if (left >= right || left < 0 || right > base.length() - 1) return "";

    if (includ[left][right] == 1000){
        return base[left] + rebuild(left + 1, right - 1, base, dp, includ) + base[right];
    } else {
        ll temp = includ[left][right];
        return rebuild(left, temp, base, dp, includ) + rebuild(temp + 1, right, base, dp, includ);
    }
}

bool match(char l, char r){
    if (l == '{' && r == '}' ||
        l == '[' && r == ']' ||
        l == '(' && r == ')'
    ) {
        return true;
    } else {
        return false;
    }
}

str solve(str& base){
    ll size = base.length();

    vector<vll> dp(size, vll(size)); // in dp[i][j] max psp fo i - j substring
    vector<vll> includ(size, vll(size));

    for (ll len = 2; len <= size; ++len){
        for (ll left = 0; left + len - 1 < size; ++left){
            ll right = left + len - 1;
            dp[left][right] = 0;
            includ[left][right] = -10;

            if (match(base[left], base[right])) {
                dp[left][right] = dp[left + 1][right - 1] + 2;// take [left + 1][right - 1] like skeleton
                includ[left][right] = 1000;
            }
            for (ll t = left; t < right; ++t){
                if (dp[left][t] + dp[t + 1][right] > dp[left][right]){ // delete one sybbol inside
                    dp[left][right] = dp[left][t] + dp[t + 1][right];
                    includ[left][right] = t;
                }
            }
        }
    }

    return rebuild(0, size - 1, base, dp, includ);

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    str input;
    getline(cin, input);
    cout << solve(input);

    return 0;
}
