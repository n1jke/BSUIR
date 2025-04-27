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
//алгоритме Рабина-Карпа\\
constexpr ll MOD = 1E18;
constexpr ll mod = 1e9 + 7;
constexpr int maxn = 1e5+1;
const ll base = 31;

vll findApproxMatches(const string& p, const string& t) {
    int n = t.size(), m = p.size();
    vll positions;

    for (ll i = 0; i + m <= n; i++) {
        ll diffCount = 0;
        for (int j = 0; j < m; j++) {
            if (t[i + j] != p[j]) {
                ++diffCount;
                if (diffCount > 1) break;
            }
        }
        if (diffCount <= 1) {
            positions.push_back(i + 1);
        }
    }

    return positions;
}

int main() {
    string p, t;
    cin >> p >> t;

    vll result = findApproxMatches(p, t);

    cout << result.size() << "\n";
    for (int pos : result) {
        cout << pos << " ";
    }
    cout << "\n";

    return 0;
}

