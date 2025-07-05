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

class SegmentTree {
private:
  size_t size;
  vll tree, lazy;

  void push(ll node, ll left, ll right) {
    if (lazy[node] == -1) return;
    tree[node] = max(tree[node], lazy[node]);
    if (left != right) {
      lazy[node * 2] = max(lazy[node * 2], lazy[node]);
      lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
    }
    lazy[node] = -1;
  }

  void update(ll node, ll left, ll right, ll ql, ll qr, ll val) {
    push(node, left, right);
    if (ql > qr) return;
    if (ql == left && qr == right) {
      lazy[node] = max(lazy[node], val);
      push(node, left, right);
    } else {
      ll mid = (left + right) / 2;
      update(node * 2, left, mid, ql, min(qr, mid), val);
      update(node * 2 + 1, mid + 1, right, max(ql, mid + 1), qr, val);
      tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
  }

  ll findMax(ll node, ll left, ll right, ll pos) {
    push(node, left, right);
    if (left == right) return tree[node];
    ll mid = (left + right) / 2;
    if (pos <= mid) return findMax(node * 2, left, mid, pos);
    else return findMax(node * 2 + 1, mid + 1, right, pos);
  }

public:
  SegmentTree(size_t n) {
    size = n;
    tree.assign(n * 4, 0);
    lazy.assign(n * 4, -1);
  }

  void update(ll left, ll right, ll val) {
    update(1, 0, size - 1, left, right, val);
  }

  ll getMax(ll pos) {
    return findMax(1, 0, size - 1, pos);
  }

};

struct Plant {
    ll x, y;
    ll index;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll lenght, height, count;
  cin >> lenght >> height >> count;
  vector<Plant> points(count);
  vll yCoord;

  for (ll i = 0; i < count; ++i) {
    ld x, y;
    cin >> x >> y;
    points[i] = {static_cast<ll>(x * 2), static_cast<ll>(y * 2), i};
    yCoord.pb(static_cast<ll>(y * 2));
  }

  sort(points.begin(), points.end(),  [&](const Plant& f, const Plant& s){
    return f.x < s.x;
  });

  sort(yCoord.begin(), yCoord.end());
  yCoord.erase(unique(yCoord.begin(), yCoord.end()), yCoord.end());

  map<ll, ll> yIndx;
  for (ll i = 0; i < yCoord.size(); ++i) {
    yIndx[yCoord[i]] = i;
  }

  SegmentTree tree(yCoord.size());
  vll result(count);

  for (const auto& p : points) {
    ll x = p.x;
    ll y = p.y;
    ll indexY = yIndx[y];
    ll xCover = tree.getMax(indexY);
    ll half = x - xCover;
    result[p.index] = half;

    //upd
    ll yLow = y - half;
    ll yHigh = y + half;
    ll l = lower_bound(yCoord.begin(), yCoord.end(), yLow) - yCoord.begin();
    ll r = upper_bound(yCoord.begin(), yCoord.end(), yHigh) - yCoord.begin() - 1;
    if (l <= r) {
      tree.update(l, r, x + half);
    }
  }

  for (const auto& ans : result) cout << ans << " ";

  return 0;
}
