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

constexpr ll mod = 1e9 + 7;
constexpr ll mod2 = 1e9 + 9;
constexpr ll pInf = std::numeric_limits<ll>::max();
constexpr ll mInf = std::numeric_limits<ll>::min();
const ll base = 31;
const ll base1 = 67, base2 = 71;

ll dijkstra(vector<vll>& graph, ll start, ll end )
{
  ll n = graph.size();
  vector<ll> dist(n, pInf);
  vector<bool> used(n, false);

  dist[start] = 0;

  for (ll i = 0; i < n; ++i)
  {
    // find unused vert with minimum distance
    ll v = -1;
    for (ll j = 0; j < n; ++j)
    {
      if (!used[j] && (v == -1 || dist[j] < dist[v]))
      {
        v = j;
      }
    }

    if (dist[i] == pInf) // exit when the vertex mInf
    {
      break;
    }

    used[v] = true;

    // update deistance
    for (ll j = 0; j < n; ++j)
    {
      if (graph[v][j] != mInf && dist[v] + graph[v][j] < dist[j])
      {
        dist[j] = dist[v] + graph[v][j];
      }
    }
  }

  return (dist[end] == pInf) ? -1 : dist[end];
}

ll bfs(unordered_map<ll, vll>& graph, ll start, ll end) {
  queue<pll> que;
  unordered_map<ll, ll> dist;

  que.push({start, 0});
  dist[start] = 0;

  while (!que.empty()) {
    auto [v, d] = que.front();
    que.pop();

    if (v == end) return d;

    for (ll u : graph[v]) { // all near vertexes
      if (!dist.count(u)) {
        dist[u] = d + 1;
        que.push({u, d + 1});
      }
    }
  }
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll count;
  cin >> count;
  str first, shit, second;
  ll vert = 0;

  unordered_map<ll, vll> graph;
  unordered_map<str,ll> vertNum;

  for (ll i = 0; i < count; ++i)
  {
    cin >> first >> shit >> second;

    // init vertexes
    if (!vertNum.count(first)) vertNum[first] = ++vert;
    if (!vertNum.count(second)) vertNum[second] = ++vert;

    graph[vertNum[first]].pb(vertNum[second]); // add line
  }
  str f,s;
  cin >> f >> s;

  if (!vertNum.count(f) || !vertNum.count(s))
  {
    cout <<  -1 << '\n';
  } else
  {
    cout << bfs(graph, vertNum[f], vertNum[s]) << '\n';
  }


  /*
  unordered_map<str, ll> vertNum;
  vector<vll> graph(101);

   for (ll i = 0; i < count; ++i){
     cin >> first >> shit >> second;
     //cout << first << " " << second;
     if (vertNum.find(first) == vertNum.end())
     {
       vertNum[first] = vert;
       ++vert;
     }
     if (vertNum.find(second) == vertNum.end())
     {
       vertNum[second] = vert;
       ++vert;
     }
     graph[vertNum[first]].pb(vertNum[second]);
   }

   str f, s;
   cin >> f >> s;
  ll start = vertNum[f];
  ll end = vertNum[s];

  cout << dijkstra(graph, start, end) << '\n';
   //dijkstra ?!?!
*/

  return 0;
}