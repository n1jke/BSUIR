#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

const ll LOG = 11; // near 1000

vector<ll> computeDepth(vector<vector<ll>>& children, ll n) {
    vector<ll> depth(n, 0);
    vector<ll> q; 
    q.push_back(0); // начинаем с корня (вершина 0)
    for (size_t i = 0; i < q.size(); i++) {
        ll cur = q[i];
        for (ll child : children[cur]) {
            depth[child] = depth[cur] + 1;
            q.push_back(child);
        }
    }
    return depth;
}

vector<vector<ll>> buildUpTable(vector<ll>& parent, ll n) {
    vector<vector<ll>> up(LOG, vector<ll>(n, -1));
    // прямой предок
    for (ll i = 0; i < n; i++) {
        up[0][i] = parent[i];
    }
    // остальных уровней
    for (ll k = 1; k < LOG; k++) {
        for (ll v = 0; v < n; v++) {
            ll prev = up[k - 1][v];
            if (prev != -1)
                up[k][v] = up[k - 1][prev];
            else
                up[k][v] = -1;
        }
    }
    return up;// distance,, vertex
}

ll lca(ll u, ll v,  vector<ll>& depth,  vector<vector<ll>>& up,  vector<ll>& parent) {
    if (depth[u] < depth[v])  swap(u, v);
    // up u, чтобы его глубина сравнялась с v
    ll diff = depth[u] - depth[v];
    for (ll k = 0; k < LOG; k++) {
        if (diff & (1 << k))
            u = up[k][u];
    }
    
    if (u == v)
        return u;
    
    // up обе вершины, пока 2^k предки не станут равны
    for (ll k = LOG - 1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }
    return parent[u];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  cin >> n;
    
  vector<ll> parent(n, -1);
  vector<vector<ll>> children(n);
  parent[0] = -1; // no parent for root
  for (ll i = 1; i < n; i++) {
    cin >> parent[i];
    children[parent[i]].push_back(i);
  }
    
  vector<ll> depth = computeDepth(children, n);
  vector<vector<ll>> up = buildUpTable(parent, n);

  ll m;
  cin >> m;
  while (m--) {
    ll u, v;
    cin >> u >> v;
    cout << lca(u, v, depth, up, parent) << '\n';
  }
    
    return 0;
}
