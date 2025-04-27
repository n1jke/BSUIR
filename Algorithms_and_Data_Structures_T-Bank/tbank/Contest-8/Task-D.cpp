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
    tree[root] = logs[tl];
    return;
   }

  ll tm = (tl + tr) / 2;
  build_DO(root * 2 + 1, tl, tm);
  build_DO(root * 2 + 2, tm, tr);
  tree[root] =  max(tree[root * 2 + 1], tree[root * 2 + 2]);
}

ll find_smallest(const ll target, const ll currRoot, const ll tl, const ll tr) {
  if (tr  - tl == 1) {
    ll ans;
  }
  ll md = (tl + tr) / 2;
  if (tree[currRoot * 2 + 1]  > target) {
    return find_smallest(target, currRoot * 2 + 1, tl, md);
  }
  return find_smallest(target - tree[currRoot * 2 + 1], currRoot * 2 + 2, md, tr);


  /*
  * if (tr < left || right < tl) return {pInf,0};

  if (left <= tl && tr <= right) return tree[currRoot];

  ll tm = (tl + tr) / 2;
  pll leftChild = min_DO(left, right, currRoot * 2 + 1, tl, tm);
  pll rightChild = min_DO(left, right, currRoot * 2 + 2, tm + 1, tr);

  if (rightChild.first == leftChild.first)  return {rightChild.first, rightChild.second + leftChild.second};
  else if (rightChild.first < leftChild.first) return rightChild;
  else return leftChild;
 * */
}


void update_DO(ll indx, ll val, ll currRoot, ll tl, ll tr) {
  if (tr - tl == 1) { // in range of indx element
    tree[currRoot] = val;
    return;
  }

  if (indx > tr || indx < tl) { // outside range
    return;
  }

  ll tm = (tl + tr) / 2;
  update_DO(indx, val, currRoot * 2 + 1, tl, tm);
  update_DO(indx, val, currRoot * 2 + 2, tm + 1, tr);
  tree[currRoot] = max(tree[currRoot * 2 + 1], tree[currRoot * 2 + 2]);
}



int main() {
  ll countLog, countRequest;
  cin >> countLog >> countRequest;
  logs.resize(countLog);
  tree.resize(countLog * 4);

  for (ll i = 0; i <countLog; ++i) cin >> logs[i];
  build_DO(0, 0, countLog);
  vll ans;
  ll type, first, second;
  while (countRequest--) {
    cin >> type >> first >> second;
    if (type == 1) {
      update_DO(first, second, 0, 0, countLog);
    } else {
      //ans.pb(kth_number(first, 0, 0, countLog));
    }
  }
  //cout << tree.size() << '\n';
  for (auto& a : ans) cout << a <<  '\n';

  return 0;
}
