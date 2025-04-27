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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vll> grid(n, vll(m));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    vector<vll> right_zeros(n, vll(m, 0));
    vector<vll> bottom_zeros(n, vll(m, 0));

    for (ll i = 0; i < n; ++i) {
        for (ll j = m - 1; j >= 0; --j) {
            if (grid[i][j] == 1) {
                right_zeros[i][j] = (j < m - 1 ? right_zeros[i][j + 1] : 0) + 1;
            }
        }
    }

    for (ll j = 0; j < m; ++j) {
        for (ll i = n - 1; i >= 0; --i) {
            if (grid[i][j] == 1) {
                bottom_zeros[i][j] = (i < n - 1 ? bottom_zeros[i + 1][j] : 0) + 1;
            }
        }
    }

    ll max_size = 0;
    ll max_i = 0, max_j = 0;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            if (grid[i][j] == 1) {
                ll possible_k = min(right_zeros[i][j], bottom_zeros[i][j]);
                for (ll k = max_size + 1; k <= possible_k; ++k) {
                    bool can_form = true;
                    for (ll row = i; row < i + k; ++row) {
                        if (right_zeros[row][j] < k) {
                            can_form = false;
                            break;
                        }
                    }
                    if (can_form) {
                        max_size = k;
                        max_i = i;
                        max_j = j;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    cout << max_size << "\n";
    cout << max_i + 1 << " " << max_j + 1 << "\n";

    return 0;
}