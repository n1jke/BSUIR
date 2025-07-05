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
const ll INF = LLONG_MAX;

using PII = pair<ll, int>; // (distance, vertex)

vll dijkstra(int n, const vector<vector<pair<int, int>>>& adj, int start) {
	vll dist(n, INF);
	dist[start] = 0;

	priority_queue<PII, vector<PII>, greater<>> pq; // minHeap
	pq.emplace(0, start);

	while (!pq.empty()) {
		auto [d, u] = pq.top();
    pq.pop();

		if (d > dist[u]) continue; // skip useless

		for (auto [v, w] : adj[u]) {
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.emplace(dist[v], v);
			}
		}
	}

	return dist;
}

vll dijkstra_loggs(int n, const vector<vector<pair<int, int>>>& adj, int start) {
	vll dist(n, INF);
	dist[start] = 0;

	priority_queue<PII, vector<PII>, greater<>> pq; // minHeap
	pq.emplace(0, start);

	cout << "[LOG] Starting Dijkstra from vertex " << start + 1 << '\n';

	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();

		cout << "[LOG] Visiting vertex " << u + 1 << " with current distance " << d << '\n';

		if (d > dist[u]) {
			cout << "[LOG] Skipping vertex " << u + 1 << " as outdated path (known: " << dist[u] << ")\n";
			continue;
		}

		for (auto [v, w] : adj[u]) {
			cout << "[LOG] → Checking edge " << u + 1 << " → " << v + 1 << " with weight " << w << '\n';
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				cout << "[LOG]   → Updating distance of " << v + 1 << " to " << dist[v] << '\n';
				pq.emplace(dist[v], v);
			}
		}
	}

	cout << "[LOG] Dijkstra complete.\n";
	return dist;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll vert, edges;
	cin >> vert >> edges;

	vector<vector<pair<int, int>>> adj(vert); // (to, weight)
	for (int i = 0; i < edges; ++i) {
		ll s, e, c;
		cin >> s >> e >> c;
		adj[s-1].emplace_back(e-1, c);
		adj[e-1].emplace_back(s-1, c);
	}

//	vll distances = dijkstra(vert, adj, 0);
//
//	for (const auto& d : distances) cout << d << ' ';

	vll distances = dijkstra_loggs(vert, adj, 0);

	return 0;
}

