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

struct Node {
  ll sum;
  ll count;

  bool set;
  ll lazy; // 0 - white, 1 - black

  ll lColor;
  ll rColor;

  Node() : sum(0), count(0), set(false), lazy(0), lColor(0), rColor(0) {};
};

vll lens, prefix;

class SegmentTree {
private:
  vector<Node> tree;
  ll n;

  ll segmentSum(ll left, ll right) {
    return prefix[right + 1] - prefix[left];
  }


  void applyChange(ll node, ll left, ll right, ll val) {
    tree[node].set = true;
    tree[node].lazy = val;
    tree[node].lColor = tree[node].rColor = val;
    tree[node].sum = val == 1 ? segmentSum(left, right) : 0;
    tree[node].count = val == 1 ? 1 : 0;
  }

  Node merge(const Node& left, const Node& right) {
    Node merged;
    merged.sum = left.sum + right.sum;
    merged.count = left.count + right.count;

    if (left.rColor == 1 && 1 == right.lColor) --merged.count;

    merged.lColor = left.lColor;
    merged.rColor = right.rColor;

    return merged;
  }

  void push(ll node, ll left, ll right) {
    if (left == right || tree[node].set == false) return;

    ll mid = (right + left) / 2;
    applyChange(node * 2, left, mid, tree[node].lazy);
    applyChange(node * 2 + 1, mid + 1, right, tree[node].lazy);
    tree[node].set = false;
  }

  void updateChange(ll node, ll left, ll right, ll ql, ll qr, ll val) {
    if (qr < left || right < ql) return; // not overlaped

    if (ql <= left && right <= qr) { // inside
      applyChange(node, left, right, val);
      return;
    }

    push(node, left, right);
    ll mid = (left + right) / 2;
    updateChange(node * 2, left, mid, ql, qr, val);
    updateChange(node * 2 + 1, mid + 1, right, ql, qr, val);

    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
  }

public:
  SegmentTree(ll size) {
    n = size;
    tree.assign(4 * n + 1, Node());
  }

  void rangeChange(ll left, ll right, ll val) {
    updateChange(1,0,n - 1, left, right, val);
  }

  Node getAnswer() {
    return tree[1];
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n;
  cin >> n;
  vector<pair<char, pll>> ops(n);
  set<ll> coords;

  for (ll i = 0; i < n; ++i) {
    ll x, len;
    cin >> ops[i].first >> x >> len;
    ll r = x + len;
    ops[i].second = {x, r};
    coords.insert(x);
    coords.insert(r);
  }

  // compress
  vll sorted(coords.begin(), coords.end());
  for (int i = 0; i + 1 < (int)sorted.size(); ++i) {
    lens.push_back(sorted[i+1] - sorted[i]);
  }

  prefix.assign(lens.size()+1, 0);
  for (int i = 0; i < (int)lens.size(); ++i) {
    prefix[i+1] = prefix[i] + lens[i];
  }

  // coord value -> to indx in sorted[]
  unordered_map<ll,ll> indx;
  for (int i = 0; i < (int)sorted.size(); ++i) {
    indx[sorted[i]] = i;
  }

  vector<tuple<char, ll, ll>> final(n);
  for (int i = 0; i < n; ++i) {
    char c = ops[i].first;
    ll left = indx[ ops[i].second.first ];
    ll right = indx[ ops[i].second.second ];
    // in DO  [l..r-1]
    final[i] = make_tuple(c, left, right - 1);
  }


  SegmentTree st(lens.size());
   for ( ll i = 0; i < n; ++i) {
     char clr; ll left, right;
     tie(clr, left, right) = final[i];

     ll color = clr == 'B' ? 1 : 0;
     st.rangeChange(left, right, color);

     Node ans = st.getAnswer();
     cout << ans.count << ' ' << ans.sum << '\n';
   }

  return 0;
}
