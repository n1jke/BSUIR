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

#include <bits/stdc++.h>
using namespace std;

#define ll  long long
#define vll vector<ll>
#define pll pair<ll, ll>
const ll INF = LLONG_MAX;

using PII = pair<ll, int>; // (distance, vertex)

struct Road {
    int u, v, time;
    ll weight_limit;
};

vll dijkstra(int n, const vector<vpll>& adj, int start) {
    vll dist(n, INF);
    dist[start] = 0;

    priority_queue<PII, vector<PII>, greater<>> pq; // minHeap
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Road> roads(M);
    for (int i = 0; i < M; ++i) {
        cin >> roads[i].u >> roads[i].v >> roads[i].time >> roads[i].weight_limit;
        roads[i].u--;
        roads[i].v--;
    }

    ll low = 0;
    ll high = 10000000;

    while (low < high) {
        ll mid = (low + high + 1) / 2;
        ll W = 3000000 + 100LL * mid;

        vector<vpll> adj(N);
        for (const auto& road : roads) {
            if (road.weight_limit >= W) {
                adj[road.u].emplace_back(road.v, road.time);
                adj[road.v].emplace_back(road.u, road.time);
            }
        }

        vll distances = dijkstra(N, adj, 0);
        if (distances[N - 1] <= 1440) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    cout << low;

    return 0;
}