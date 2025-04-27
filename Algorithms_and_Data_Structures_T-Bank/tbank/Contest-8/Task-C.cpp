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

vll logs;
vll tree;

void build_DO(const ll root, const ll tl, const ll tr) {
  if (tr - tl == 1) {
    tree[root] = (logs[tl] == 1) ? 1 : 0;
    return;
   }

  ll tm = (tl + tr) / 2;
  build_DO(root * 2 + 1, tl, tm);
  build_DO(root * 2 + 2, tm, tr);
  tree[root] = tree[root * 2 + 1] + tree[root * 2 + 2];
}

ll kth_number(const ll target, const ll currRoot, const ll tl, const ll tr) {
  if (tr  - tl == 1) {
    return tl;
  }
  ll md = (tl + tr) / 2;
  if (tree[currRoot * 2 + 1]  > target) {
    return kth_number(target, currRoot * 2 + 1, tl, md);
  }
  return kth_number(target - tree[currRoot * 2 + 1], currRoot * 2 + 2, md, tr);
}

void update_DO(ll indx, ll currRoot, ll tl, ll tr) {
  if (tr - tl == 1) {
    // in range of indx element
    tree[currRoot] = tree[currRoot] == 1 ? 0 : 1;
    return;
  }

  ll tm = (tl + tr) / 2;
  if (tm > indx) update_DO(indx, currRoot * 2 + 1, tl, tm);
  else update_DO(indx, currRoot * 2 + 2, tm, tr);
  tree[currRoot] = tree[currRoot * 2 + 1] + tree[currRoot * 2 + 2];
}



int main() {
  ll countLog, countRequest;
  cin >> countLog >> countRequest;
  logs.resize(countLog);
  tree.resize(countLog * 4);

  for (ll i = 0; i <countLog; ++i) cin >> logs[i];
  build_DO(0, 0, countLog);
  vll ans;
  ll type, first;
  while (countRequest--) {
    cin >> type >> first;
    if (type == 1) {
      update_DO(first, 0, 0, countLog);
    } else {
      ans.pb(kth_number(first, 0, 0, countLog));
    }
  }
  //cout << tree.size() << '\n';
  for (auto& a : ans) cout << a <<  '\n';

  return 0;
}
