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
constexpr ll mod2 = 1e9 + 9;
const ll base = 31;
const ll base1 = 67LL, base2 = 71LL;

void computePrefixHash( string &s, ll base, ll mod, vector<ll>& pref, vector<ll>& power) {
    int n = s.size();
    pref.assign(n + 1, 0);
    power.assign(n + 1, 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = (pref[i] * base + (ll)s[i]) % mod;
        power[i + 1] = (power[i] * base) % mod;
    }
}

// hash of s[l...r]
ll getHash( vector<ll>& pref,  vector<ll>& power, int l, int r, ll mod) {
    ll res = (pref[r + 1] - (pref[l] * power[r - l + 1]) % mod + mod) % mod;
    return res;
}

int maxOddPalindrome( string &s, int center,
                      vector<ll>& pref1,  vector<ll>& power1,
                      vector<ll>& pref2,  vector<ll>& power2,
                      vector<ll>& pref1_rev,  vector<ll>& power1_rev,
                      vector<ll>& pref2_rev,  vector<ll>& power2_rev) {
    int n = s.size();
    int lo = 0, hi = min(center, n - 1 - center);
    int best = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int L = center - mid, R = center + mid;
        //  s[L...R]
        ll h1 = getHash(pref1, power1, L, R, mod);
        ll h2 = getHash(pref2, power2, L, R, mod2);

        int L_rev = n - 1 - R, R_rev = n - 1 - L;
        ll rh1 = getHash(pref1_rev, power1_rev, L_rev, R_rev, mod);
        ll rh2 = getHash(pref2_rev, power2_rev, L_rev, R_rev, mod2);

        if (h1 == rh1 && h2 == rh2) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return best;
}

int maxEvenPalindrome( string &s, int i,
                       vector<ll>& pref1,  vector<ll>& power1,
                       vector<ll>& pref2,  vector<ll>& power2,
                       vector<ll>& pref1_rev,  vector<ll>& power1_rev,
                       vector<ll>& pref2_rev,  vector<ll>& power2_rev) {
    int n = s.size();
    //  s[i - r + 1 ... i + r]
    int lo = 1, hi = min(i + 1, n - 1 - i);
    int best = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int L = i - mid + 1, R = i + mid;
        ll h1 = getHash(pref1, power1, L, R, mod);
        ll h2 = getHash(pref2, power2, L, R, mod2);
        // reverse
        int L_rev = n - 1 - R, R_rev = n - 1 - L;
        ll rh1 = getHash(pref1_rev, power1_rev, L_rev, R_rev, mod);
        ll rh2 = getHash(pref2_rev, power2_rev, L_rev, R_rev, mod2);

        if (h1 == rh1 && h2 == rh2) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return best;
}

void solve(str& input){
    int n = input.size();

    string s_rev = input;;
    reverse(s_rev.begin(), s_rev.end());

    //haghagaaa
    vector<ll> pref1, power1, pref2, power2;
    vector<ll> pref1_rev, power1_rev, pref2_rev, power2_rev;
    computePrefixHash(input, base1, mod, pref1, power1);
    computePrefixHash(input, base2, mod2, pref2, power2);
    computePrefixHash(s_rev, base1, mod, pref1_rev, power1_rev);
    computePrefixHash(s_rev, base2, mod2, pref2_rev, power2_rev);

    ll total = 0;
    for (int i = 0; i < n; ++i) {
        int r = maxOddPalindrome(input, i, pref1, power1, pref2, power2, pref1_rev, power1_rev, pref2_rev, power2_rev);
        total += (r + 1);
    }

    // Чётные палиндромы: центр между s[i] и s[i+1]
    for (int i = 0; i < n - 1; ++i) {
        int r = maxEvenPalindrome(input, i, pref1, power1, pref2, power2, pref1_rev, power1_rev, pref2_rev, power2_rev);
        total += r;
    }

    cout << total << '\n';
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

/*
*void findSubPolygnom(str& input)
{
    ll count = 0;
    auto [hash, pow] = computeHash(input);
    str revInput = input;
    reverse(revInput.begin(), revInput.end());
    auto [rHash, rPow] = computeHash(revInput);

    for (ll i = 0; i < input.length(); ++i)
    {
        ll left = i, right = i;
        while (left >= 0 && right <= input.length())
        {
            ll lHsh = getHash(left + 1, right + 1, rHash, rPow);
            ll rHsh = getHash(input.length() - right, input.length() - left, hash, pow);
            if (lHsh == rHsh /*&& left > 0 && right < input.length() - 1)
            {
                --left;
                ++right;
                ++count;
            } else
            {
                break;
            }
        }


left = i, right = i + left;
while (left >= 0 && right < input.length())
{
    ll lHsh = getHash(left + 1, right + 1, hash, pow);
    ll rHsh = getHash(input.length() - right, input.length() - left, rHash, rPow);
    if (lHsh == rHsh)
    {
        ++count;
        --left;
        ++right;
    } else
    {
        break;
    }
}
    }

cout << count << '\n';
}
*/
