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

vll solve(vll& nums){
    ll size = nums.size();

    vll dp(size, 1);
    vll prev(size, -1);

    ll mLen = 1;
    ll lIndx = 0;

    for(ll i = 0; i < size; ++i){
        for (ll j = 0; j < i; ++j){
            if (nums[j] < nums[i] && dp[j] + 1 > dp[i]){
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > mLen){
            mLen = dp[i];
            lIndx = i;
        }
    }

    vll list;
    while(lIndx != -1){
        list.pb(nums[lIndx]);
        lIndx = prev[lIndx];
    }

    reverse(list.begin(), list.end());

    return list;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll size;
    cin >> size;
    vll nums(size);

    for(ll i = 0; i < size; ++i){
        cin >> nums[i];
    }

    vll subArr = solve(nums);
    cout << subArr.size() << '\n';
    for(auto& el : subArr){
        cout << el << ' ';
    }


    return 0;
}