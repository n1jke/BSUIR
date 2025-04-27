#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("tune=native")
#pragma GCC target("avx2")

#define ll long long
#define ld long double
#define vc vector
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb push_back

struct Count {
    ll dot = 0, star = 0;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vstr grid(n);
    for (ll i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    //try to solve from final pix to empty holst33333333333

    vc<Count> rowCoutn(n);
    vc<Count> colCoutn(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                rowCoutn[i].dot++;
                colCoutn[j].dot++;
            } else {
                rowCoutn[i].star++;
                colCoutn[j].star++;
            }
        }
    }

    //rows and columns we dont know how to paint
    vc<bool> row_active(n, true); // going from funal and dont know nothing
    vc<bool> col_active(m, true);
    ll active_rows = n, active_cols = m;

    //     r or c    num   color
    vc<pair<str, pair<ll, char>>> paint;
    bool found;
    while (active_rows > 0 || active_cols > 0) {
        found = false;

        // rows
        for (ll i = 0; i < n && !found; ++i) {
            if (row_active[i]) {
                // dont have act(dont use already) colons  || all is same
                if (active_cols == 0 ||
                    (rowCoutn[i].dot == active_cols && rowCoutn[i].star == 0) ||
                    (rowCoutn[i].star == active_cols && rowCoutn[i].dot == 0)) {
                    char c = active_cols == 0 ? grid[i][0] : (rowCoutn[i].dot ? '.' : '*');
                    paint.pb({"r", {i + 1, c}});
                    row_active[i] = false;
                    active_rows--;
                    found = true;
                    // update for colons
                    for (int j = 0; j < m; ++j) {
                        if (col_active[j]) {
                            if (grid[i][j] == '.') colCoutn[j].dot--;
                            else colCoutn[j].star--;
                        }
                    }
                }
            }
        }

        // goto coluns copipaste mBBB fix need
        if (!found) {
            for (int j = 0; j < m && !found; ++j) {
                if (col_active[j]) {
                    // dont have act(dont use already) rows  || all is same
                    if (active_rows == 0 ||
                        (colCoutn[j].dot == active_rows && colCoutn[j].star == 0) ||
                        (colCoutn[j].star == active_rows && colCoutn[j].dot == 0)) {
                        char d = active_rows == 0 ? grid[0][j] : (colCoutn[j].dot ? '.' : '*');
                        paint.pb({"c", {j + 1, d}});
                        col_active[j] = false;
                        active_cols--;
                        found = true;
                        // update
                        for (int i = 0; i < n; ++i) {
                            if (row_active[i]) {
                                if (grid[i][j] == '.') rowCoutn[i].dot--;
                                else rowCoutn[i].star--;
                            }
                        }
                    }
                }
            }
        }
        if (!found && (active_rows > 0 || active_cols > 0)) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << paint.size() << '\n';
    for (ll i = paint.size() - 1; i >= 0; --i) {
        cout << paint[i].first << ' ' << paint[i].second.first << ' ' << paint[i].second.second << '\n';
    }
    return 0;
}

/*
int main() {
    ll n, m;
    cin >> n >> m;
    vstr grid(n);
    for (ll i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    //try to solve from final pix to empty holst33333333333

    vc<unordered_map<char, ll>> rowCoutn(n);
    vc<unordered_map<char, ll>> colCoutn(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            rowCoutn[i][grid[i][j]]++;
            colCoutn[j][grid[i][j]]++;
        }
    }

    //rows and columns we dont know how to paint
    vector<bool> row_active(n, true);// going from funal and dont know nothing
    vector<bool> col_active(m, true);
    ll active_rows = n;
    ll active_cols = m;

    //     r or c    num   color
    vc<pair<str, pair<ll, char>>> paint;
    bool found;
    while (active_rows > 0 || active_cols > 0) {
        found = false;

        // rows
        for (ll i = 0; i < n && !found; ++i) {
            if (row_active[i]) {
                // dont have act(dont use already) colons  || all is same
                if (active_cols == 0 || (rowCoutn[i].size() == 1 && rowCoutn[i].begin()->second == active_cols)) {
                    char c = active_cols == 0 ? grid[i][0] : rowCoutn[i].begin()->first;
                    paint.push_back({"r", {i + 1, c}});
                    row_active[i] = false;
                    active_rows--;
                    found = true;
                    // update for colons
                    for (int j = 0; j < m; ++j) {
                        if (col_active[j]) {
                            colCoutn[j][grid[i][j]]--;
                            if (colCoutn[j][grid[i][j]] == 0) {
                                colCoutn[j].erase(grid[i][j]); // удаляем блять
                            }
                        }
                    }
                }
            }
        }
        // goto coluns copipaste mBBB fix need
        if (!found) {
            for (int j = 0; j < m && !found; ++j) {
                if (col_active[j]) {
                    // dont have act(dont use already) rows  || all is same
                    if (active_rows == 0 || (colCoutn[j].size() == 1 && colCoutn[j].begin()->second == active_rows)) {
                        char d = active_rows == 0 ? grid[0][j] : colCoutn[j].begin()->first;
                        paint.push_back({"c", {j + 1, d}});
                        col_active[j] = false;
                        active_cols--;
                        found = true;
                        // update
                        for (int i = 0; i < n; ++i) {
                            if (row_active[i]) {
                                rowCoutn[i][grid[i][j]]--;
                                if (rowCoutn[i][grid[i][j]] == 0) {
                                    rowCoutn[i].erase(grid[i][j]);
                                }
                            }
                        }
                    }
                }
            }
        }
        if (!found && paint.size() > n + m) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << paint.size() << '\n';
    for ( ll i = paint.size() - 1; i >= 0; --i )
    {
        cout << paint[i].first << ' ' << paint[i].second.first << ' ' << paint[i].second.second << '\n';
    }
    return 0;
}
*/