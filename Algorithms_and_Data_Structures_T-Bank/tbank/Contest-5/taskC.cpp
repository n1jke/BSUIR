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
constexpr ull base = 31;

pair<vull, vull> computeHash(const string& input, ull mod) {
        ull size = input.size();
        vull hash(size + 1, 0), pow(size + 1, 1);

        for (ull i = 1; i <= size; i++)
        {
            // TODO bm need fx for nums and UP letters< fuck make double hash
            ull x;
            if (isdigit(input[i - 1]))
            {
                x = input[i - 1] - '0' + 1;
            }else if (islower(input[i - 1]))
            {
                x = input[i - 1] - 'a' + 11;
            }else if (isupper(input[i - 1]))
            {
                x = input[i - 1] - 'A' + 37;
            }
            pow[i] = (pow[i - 1] * base) % MOD;
            hash[i] = (hash[i - 1] * base + x) % mod;
        }

        return {hash, pow};
}

ull getHash(ull left, ull right, vull& hashh, vull& pow, ull mod) {
    return (hashh[right] - hashh[left - 1] * pow[right - left + 1] % mod + mod) % mod;
}

void solve(str& input, str& move) {
    ull lenI = input.length();
    ull lenM = move.length();
    ull count = 0;

    if (lenI < lenM) {
        cout << 0 << '\n';
        return;
    }

    move += move;
    auto [hashIn, powIn] = computeHash(input, mod);
    auto [hashM, powM] = computeHash(move, mod);
    // second hashing
    auto [hashIn2, powIn2] = computeHash(input, mod2);
    auto [hashM2, powM2] = computeHash(move, mod2);

    set<pair<ull, ull>> interestHashes;// firsrt and second hashes
    for (ull i = 0; i < lenM; ++i) {
        interestHashes.insert({getHash(i + 1, i + lenM, hashM, powM, mod),
                               getHash(i + 1, i + lenM, hashM2, powM2, mod2)});
    }

    for (ull i = 0; i + lenM <= lenI; ++i) {
        pair<ull, ull> temp = {getHash(i + 1, i + lenM, hashIn, powIn, mod),
                             getHash(i + 1, i + lenM, hashIn2, powIn2, mod2)};
        if (interestHashes.count(temp)) {
            ++count;
        }
    }

    cout << count << '\n';
}

/*
=
abcabc
abc
4
abcabc
acb
0
aaaaaaa
aa
6
aAaa8aaAa
aAa
 */

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    str input, move;
    cin >> input >> move;
    solve(input, move);

    return 0;
}
/*

void solve(str& input, str& move)
{
    ll lenI = input.length();;
    ll lenM = move.length();
    ll count = 0;
    if (lenI < lenM)
    {
        cout << 0 << '\n';
        return;
    }
    move += move;
    auto [hashIn , powIn] = computeHash(input);
    auto [hashM, powM]  = computeHash(move);

    unordered_set<ll> interestHashes;
    for (ll i = 0; i < lenM; ++i)
    {
        interestHashes.insert(getHash(i + 1, i + lenM, hashM, powM));
    }


    for (ll i = 0; i + lenM <= lenI; ++i)
    {
        //ll temp = getHash(i , i + lenM, hashIn, powIn);
        ll temp = getHash(i + 1, i + lenM, hashIn, powIn);
        //if (interestHashes.contains(temp))
        if (interestHashes.count(temp))
        {
            ++count;
        }
    }

    cout  << count << '\n';
}
 */