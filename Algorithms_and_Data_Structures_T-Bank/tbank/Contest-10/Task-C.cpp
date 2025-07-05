#include <bits/stdc++.h>
using namespace std;

#define ll  long long
#define ld  long double
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb push_back

const ll INF = 1e9;

ll node_id(ll i, ll j, ll M) {
    return i * M + j;
}

struct edge {
    ll a, b, len;
    ll i, j, d; // coord {i, j}, d = 1 (vertical), 2 (horizontal)

    bool operator<(const edge& other) const {
        return len < other.len;
    }
};

class DSU {
    vector<ll> parents, size;

public:
    DSU(size_t sz) {
        parents.resize(sz);
        size.resize(sz, 1);
        for (size_t i = 0; i < sz; i++)
            parents[i] = i;
    }

    ll find(ll v) {
        if (v != parents[v])
            parents[v] = find(parents[v]);
        return parents[v];
    }

    bool merge(ll a, ll b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b])
            swap(a, b);
        parents[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll lenght, height;
    cin >> lenght >> height;

    vector<vll> grid(lenght, vll(height));
    for (ll i = 0; i < lenght; ++i)
        for (ll j = 0; j < height; ++j)
            cin >> grid[i][j];

    vector<edge> edges;

    for (ll i = 0; i < lenght; ++i) {
        for (ll j = 0; j < height; ++j) {
            ll u = node_id(i, j, height);

            // exist vertical
            if ((grid[i][j] & 1) && i + 1 < lenght) {
                ll v = node_id(i + 1, j, height);
                edges.pb({u, v, 0, i, j, 1});
            }

            // exist horizontal
            if ((grid[i][j] & 2) && j + 1 < height) {
                ll v = node_id(i, j + 1, height);
                edges.pb({u, v, 0, i, j, 2});
            }

            //vertical conneсtion
            if (!(grid[i][j] & 1) && i + 1 < lenght) {
                ll v = node_id(i + 1, j, height);
                edges.pb({u, v, 1, i, j, 1});
            }

            //horizontal conn
            if (!(grid[i][j] & 2) && j + 1 < height) {
                ll v = node_id(i, j + 1, height);
                edges.pb({u, v, 2, i, j, 2});
            }
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu(lenght * height);
    ll total_cost = 0;
    vector<tuple<ll, ll, ll>> added;

    for (auto& e : edges) {
        if (dsu.merge(e.a, e.b)) {
            total_cost += e.len;
            if (e.len > 0)
                added.pb({e.i + 1, e.j + 1, e.d});
        }
    }

    cout << added.size() << " " << total_cost << '\n';
    for (auto [i, j, d] : added)
        cout << i << " " << j << " " << d << '\n';

    return 0;
}