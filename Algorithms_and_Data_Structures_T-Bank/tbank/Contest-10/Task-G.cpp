#include <bits/stdc++.h>
using namespace std;

#define ll  long long
#define ld long double
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb push_back

const ll INF = 1e18;

vector<vpll> adj;

vll dijkstra(ll s, ll n) {
    vll dist(n + 1, INF);
    dist[s] = 0;
    priority_queue<pair<ll, ll>, vpll, greater<pll>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        ll d = pq.top().first;
        ll u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    adj.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll a, b, c;
    cin >> a >> b >> c;
    auto dist_a = dijkstra(a, n);
    auto dist_b = dijkstra(b, n);
    auto dist_c = dijkstra(c, n);

    if (dist_a[b] == INF || dist_a[c] == INF || dist_b[c] == INF) {
        cout << -1;
        return 0;
    }

    ll ab = dist_a[b];
    ll ac = dist_a[c];
    ll bc = dist_b[c];
    ll sum1 = ab + bc;
    ll sum2 = ac + bc;
    ll sum3 = ab + ac;

    ll result = min({sum1, sum2, sum3});
    cout << result;

    return 0;
}