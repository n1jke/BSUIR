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

class SegmentTree {
private:
  vll tree;
  ll n;

  void update(ll indx, ll val, ll node, ll start, ll end) {
    if (start == end) {
      tree[node] += val;
    } else {
      ll mid = (start + end) / 2;
      if (indx <= mid) update(indx, val, 2 * node, start, mid);
      else update(indx, val, 2 * node + 1, mid + 1, end);

      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  ll query(ll left, ll right, ll node, ll start, ll end) {
    if (right < start || end < left) return 0; // out of range

    if (left <= start && end <= right) return tree[node]; // fully inside

    ll mid = (start + end) / 2;
    ll p1 = query(left, right, 2 * node, start, mid);
    ll p2 = query(left, right, 2 * node + 1, mid + 1, end);
    return p1 + p2;
  }

public:
  SegmentTree(ll size) {
    n = size;
    tree.assign(4 * n + 1, 0);
  }

  void update(ll idx, ll val) {
    update(idx, val, 1, 1, n);
  }

  ll query(ll left, ll right) {
    if (left > right) return 0;
    return query(left, right, 1, 1, n);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n;
  cin >> n;
  vll a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  set<ll> unique_vals(a.begin(), a.end());
  vll sorted_unique(unique_vals.begin(), unique_vals.end());
  map<ll,ll> rank_map;
  for (ll i = 0; i < sorted_unique.size(); ++i) rank_map[sorted_unique[i]] = i + 1;

  ll m = sorted_unique.size();
  vll rank(n); // compressed coordinates
  for (ll i = 0; i < n; ++i) rank[i] = rank_map[a[i]];

// a[i] > a[j] > a[k]

  SegmentTree st1(m);
  vll right_smaller(n, 0); // throw a[j]
  for (ll j = n - 1; j >= 0; --j) {
    right_smaller[j] = st1.query(1, rank[j] - 1);
    st1.update(rank[j], 1);
  }

  SegmentTree st2(m);
  ll ans = 0;
  for (ll j = 0; j < n; ++j) {
    ll left_greater = st2.query(rank[j] + 1, m);
    ans += left_greater * right_smaller[j];
    st2.update(rank[j], 1);
  }

  cout << ans << '\n';
  return 0;
}