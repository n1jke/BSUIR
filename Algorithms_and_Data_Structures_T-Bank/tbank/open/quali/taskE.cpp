#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target ("tune=native")
#pragma GCC target ("avx2")

#define ll long long
#define ld long double
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll,ll>
#define vstr vector<string>
#define vpll vector<pair<ll,ll>>
#define pb push_back
const ll mod = 998244353, MOD = 1E18;


str task = "ABCDEFGH";

void solve(vstr& words)
{
    ll n = words.size();
    str current = task.substr(0, n);

    map<char, vector<str>> mp;
    map<str, ll> freq;

    for ( auto &word : words) {
        set<char> uniqueLetters;
        for (auto ch : word) {
            if (current.find(ch) != string::npos) {
                uniqueLetters.insert(ch);
            }
        }

        freq[word] = uniqueLetters.size(); // freq - count uniq letter
        for (char ch : uniqueLetters) {
            mp[ch].push_back(word);
        }
    }

    vector<char> sorted_task(current.begin(), current.end());
    sort(sorted_task.begin(), sorted_task.end(), [&](char a, char b) {
        return mp[a].size() < mp[b].size();
    });
    vector<str> result(n, "");
    set<str> used;
    // мл первый сем какой я тупой
    for (char ch : sorted_task) {
        bool found = false;
        sort(mp[ch].begin(), mp[ch].end(), [&](const str &a, const str &b) {
            return freq[a] < freq[b];
        });
        for (const auto &word : mp[ch]) {
            if (!used.count(word)) {
                size_t pos = current.find(ch);
                result[pos] = word;
                used.insert(word);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        cout << current[i] << "." << result[i] << "\n";
    }
}

int main(){
    ll count;
    cin >> count;
    vstr words(count);
    for (ll i = 0; i < count; ++i)
    {
        cin >> words[i];
    }

    solve(words);
}
