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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll size, x1, y1, x2, y2;
  cin >> size >> x1 >> y1 >> x2 >> y2;
  --x1, --y1, --x2, --y2;

  vpll moves = {
    {1,2},{1,-2},{-1,2},{-1,-2},
    {2,1}, {2,-1}, {-2,1}, {-2,-1}
  };

  vector<vll> dist(size,vll(size, -1));
  vector<vector<pll>> par(size, vector<pll>(size, {-1,-1}));
  queue<pll> q;

  //base point
  dist[x1][y1] = 0;
  q.push({x1, y1});

  // find way
  while (!q.empty())
  {
    ll x = q.front().first;
    ll y = q.front().second;
    q.pop();

    if (x == x2 && y == y2)
    {
      break;
    }

    for (auto& move : moves)
    {
      ll dx = x + move.first;
      ll dy = y + move.second;

      if (dx >= 0 && dy >= 0 && dx < size && dy < size && dist[dx][dy] == -1)
      {
        dist[dx][dy] = dist[x][y] + 1;
        par[dx][dy] = {x,y};
        q.push({dx, dy});
      }
    }
  }

  ll count = dist[x2][y2];
  cout << count << '\n';

  vector<pll> revPath;
  ll x = x2, y = y2;
  while (x != -1 && y != -1)
  {
    revPath.pb({x, y});
    ll px = par[x][y].first;
    ll py = par[x][y].second;
    x = px;
    y = py;
  }

  for (ll i = count; i >= 0; i--)
  {
    cout << revPath[i].first + 1 << ' ' << revPath[i].second  + 1<< '\n';
  }

  return 0;
}