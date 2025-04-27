#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("tune=native")
#pragma GCC target("avx2")

#define ll long long
#define ull unsigned long long
#define ld long double
#define str string
#define vll vector<ll>
#define vull vector<ull>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb push_back

constexpr ull MOD = 1E18;
constexpr ull mod = 1e9 + 7;
constexpr ull mod2 = 1e9 + 9;
constexpr ull base1 = 67;
constexpr ull base2 = 71;
//constexpr ull base = 31;


vull compute_prefix_hash(str& s, ull p) {
    ull n = s.size();
    vull hash(n + 1, 0);
    for (ll i = 0; i < n; ++i) {
        hash[i + 1] = hash[i] * p + static_cast<ull>(s[i]);
    }
    return hash;
}

void solve(str& input, str& find)
{
    str b2 = find + find;

    ull p1 = 67;
    ull p2 = 71;

    // prefix hash
    auto hash_b2_p1 = compute_prefix_hash(b2, p1);
    auto hash_b2_p2 = compute_prefix_hash(b2, p2);
    auto hash_a_p1 = compute_prefix_hash(input, p1);
    auto hash_a_p2 = compute_prefix_hash(input, p2);

    //  p1^find  p2^find
    ull pow_b1 = 1;
    for (ull i = 0; i < find.length(); ++i) pow_b1 *= p1;
    ull pow_b2 = 1;
    for (ull i = 0; i < find.length(); ++i) pow_b2 *= p2;

    set<pair<ull, ull>> hashes;
    for (ull k = 0; k < find.size(); ++k) {
        ull h1 = hash_b2_p1[k + find.size()] - hash_b2_p1[k] * pow_b1;
        ull h2 = hash_b2_p2[k + find.size()] - hash_b2_p2[k] * pow_b2;
        hashes.insert({h1, h2});
    }

    int count = 0;
    for (ull j = 0; j <= input.size() - find.size(); ++j) {
        ull h1 = hash_a_p1[j + find.size()] - hash_a_p1[j] * pow_b1;
        ull h2 = hash_a_p2[j + find.size()] - hash_a_p2[j] * pow_b2;
        if (hashes.count({h1, h2})) ++count;
    }


    cout << count << '\n';

}

int main() {
    str input, find;
    cin >> input >> find;

    solve(input, find);

    return 0;
}