#include <bits/stdc++.h>
using namespace std;

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

vll logs;
vll tree;

void build_DO(ll root, ll tl, ll tr) {
  if (tl == tr) {
    tree[root] = logs[tl];
   } else {
     ll tm = (tl + tr) / 2;
     build_DO(root * 2 + 1, tl, tm);
     build_DO(root * 2 + 2, tm + 1, tr);
     tree[root] = tree[root * 2 + 1] + tree[root * 2 + 2];
   }
}

ll sum_DO(ll left, ll right, ll currRoot, ll tl, ll tr) {
  if (tr < left || right < tl) return 0;
  if (left <= tl && tr <= right) {
    return tree[currRoot];
  }

  ll tm = (tl + tr) / 2;
  return sum_DO(left, right, currRoot * 2 + 1, tl, tm) + sum_DO(left, right, currRoot * 2 + 2, tm + 1, tr);
}

void update_DO(ll indx, ll val, ll currRoot, ll tl, ll tr) {
  if (tl == tr && tr == indx) {
    logs[indx] = val;
    tree[currRoot] = val;
    return;
  }

  if (indx > tr || indx < tl) {
    return;
  }

  ll tm = (tl + tr) / 2;
  update_DO(indx, val, currRoot * 2 + 1, tl, tm);
  update_DO(indx, val, currRoot * 2 + 2, tm + 1, tr);
  tree[currRoot] = tree[currRoot * 2 + 1] + tree[currRoot * 2 + 2];
}



int main() {
  ll countLog, countRequest;
  cin >> countLog >> countRequest;
  logs.resize(countLog);
  tree.resize(countLog * 4);

  for (ll i = 0; i <countLog; ++i) cin >> logs[i];
  build_DO(0, 0, countLog - 1);
  vll ans;
  ll type, first, second;
  while (countRequest--) {
    cin >> type >> first >> second;
    if (type == 1) {
      update_DO(first, second, 0, 0, countLog - 1);
    } else {
      ans.pb(sum_DO(first, second - 1, 0, 0, countLog - 1));
    }
  }
  for (auto& a : ans) cout << a << '\n';

  return 0;
}
/*
* 5 5
5 4 2 3 5
2 0 3
1 1 1
2 0 3
1 3 1
2 0 5
 * */