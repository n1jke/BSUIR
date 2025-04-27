#include <bits/stdc++.h>
using namespace std;

#define ll unsigned long long
#define ld long double
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb push_back
const ll P = 997;

vll hashes, rhash, poww;

void buildHashes(const vll& a) {
    int n = a.size();
    hashes.assign(n+1, 0);
    rhash.assign(n+1, 0);
    poww.assign(n+1, 0);
    poww[0] = 1;
    for (int i = 1; i <= n; ++i) poww[i] = poww[i-1] * P;

    for (int i = 0; i < n; ++i) hashes[i+1] = hashes[i] * P + a[i];
    for (int i = 0; i < n; ++i) rhash[i+1] = rhash[i] * P + a[n-1-i];
}

ll getHash(const vll& H, int l, int r) {
    return H[r+1] - H[l] * poww[r - l + 1];
}

int findLongest(const vll& a) {
    int n = a.size();
    int ans = 0;

    for (int center = 0; center < n; ++center) {
        // even-length palindrome (center between center-1 and center)
        int l = 0, r = min(center, n - center);
        while (l < r) {
            int m = (l + r + 1) / 2;
            // nowrmal [center-m .. center-1]
            //  reverse rh: [n-center-m .. n-center-1]
            if ( getHash(hashes, center-m, center-1)
              == getHash(rhash, n - center - m, n - center - 1) )
                l = m;
            else
                r = m - 1;
        }
        ans = max(ans, l * 2);

        // odd-length palindrome
        l = 0;
        r = min(center, n - center - 1);
        while (l < r) {
            int m = (l + r + 1) / 2;
            // normal [center-m .. center+m]
            // reverse [n-1-(center+m) .. n-1-(center-m)]
            if ( getHash(hashes, center-m, center+m)
              == getHash(rhash, n-1-(center+m), n-1-(center-m)) )
                l = m;
            else
                r = m - 1;
        }
        ans = max(ans, l * 2 + 1);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vll zones(n);
    for (auto& z : zones) cin >> z;

    buildHashes(zones);
    ll res = findLongest(zones);
    if (res == 1 ) cout << 0 << '\n';
    else cout << res << '\n';
    return 0;
}
