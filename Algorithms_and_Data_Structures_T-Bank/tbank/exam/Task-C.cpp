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

ll height, width;

void dfs(const vector<vector<char>>& graph, vector<vector<bool>>& visit,
				 ll y, ll x, bool& sharp, bool& X) {
	if (visit[y][x] || graph[y][x] == '.') return;

	visit[y][x] = true;
	if (graph[y][x] == '#') sharp = true;
	if (graph[y][x] == 'X') X = true;
	ll dx[] = {0, 0, 1, -1};
	ll dy[] = {1, -1, 0, 0};

	for (int d = 0; d < 4; ++d) {
		ll nY = y + dy[d];
		ll nX = x + dx[d];
		if (nY >= 0 && nY < height && nX >= 0 && nX < width) {
			dfs(graph, visit, nY, nX, sharp, X);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> height >> width;
	vector field(height, vector<char>(width));
	vector visit(height, vector(width, false));
	for (ll y = 0; y < height; ++y) {
		for (ll x = 0; x < width; ++x) {
			cin >> field[y][x];
		}
	}

	ll full = 0, partial = 0, destroy = 0;
	for (ll y = 0; y < height; ++y) {
		for (ll x = 0; x < width; ++x) {
			if (!visit[y][x] && field[y][x] != '.') {
				bool sharp = false, X = false;
				dfs(field, visit, y, x, sharp, X);
				if (sharp && X) partial++;
				else if (sharp && !X) full++;
				else destroy++;
			}
		}
	}

	cout << full << " " << partial << " " << destroy;

	return 0;
}