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

void solve(ll lenght, ll power, vll& cost){

    vll dp(lenght + 1, mInf);
    vll prev(lenght + 1, -1);

    dp[1] = 0; // start
    deque<ll> dq;
    dq.pb(1);

    for (ll i = 2; i <= lenght; ++i){

        while (!dq.empty() && dq.front() < i - power){
            dq.pop_front();
        }

        if (!dq.empty()) {
            ll j = dq.front();
            ll tCoin = (i == lenght ? 0 :cost[i]);
            dp[i] = dp[j] + tCoin;
            prev[i] = j;
        }

        while (!dq.empty() && dp[dq.back()] <= dp[i]){ // delete useless
            dq.pop_back();
        }

        dq.pb(i );
    }
    /*
     for (ll i = 2; i <= lenght; ++i){
        for (ll j = max((ll)1, i - power); j < i; ++j) {
            ll tCoin = (i == lenght ? 0 : cost[i]);
            ll tempDp = dp[j] + tCoin;
            if (tempDp > dp[i]){
                prev[i] = j;
                dp[i] = tempDp;
            }
        }
    }
     */

    cout << dp[lenght] << '\n';
    vll path;
    ll curr = lenght;
    while (curr != -1){
        path.pb(curr);
        curr = prev[curr];
    }

    reverse(path.begin(), path.end());

    cout << path.size() - 1 << '\n';

    for (auto& p : path){
        cout << p << ' ';
    }
    cout << '\n';

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll length, power;
    cin >> length >> power;

    vll cost(length + 1, 0);
    for (ll i = 2; i < length; ++i){
        cin >> cost[i];
    }

    solve(length, power, cost);
    return 0;
}
