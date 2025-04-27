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

const ll MOD = 1E18;
const ll mod = 998244353;

bool has_letter(const str& task, char letter) {
    return task.find(letter) != str::npos;
}

int main() {
    int n;
    cin >> n;

    vstr tasks(n);
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i];
    }

    vstr original = tasks;
    sort(tasks.begin(), tasks.end());

    do {
        bool is_valid = true;
        for (int i = 0; i < n; ++i) {
            char required = 'A' + i;
            if (!has_letter(tasks[i], required)) {
                is_valid = false;
                break;
            }
        }

        if (is_valid) {
            cout << "Yes\n";
            for (int i = 0; i < n; ++i) {
                cout << char('A' + i) << "." << tasks[i] << "\n";
            }
            return 0;
        }
    } while (next_permutation(tasks.begin(), tasks.end()));

    cout << "NO\n";
    return 0;
}
