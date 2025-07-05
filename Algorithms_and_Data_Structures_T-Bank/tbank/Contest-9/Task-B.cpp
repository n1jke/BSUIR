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

struct Lazy {
  bool set;
  ll setVal;
  ll addVal;
};

struct Node {
    ll sum;
    Lazy lazy;
};

class SegmentTree {
private:
  vector<Node> tree;
  ll n;

  void applyAdd(ll node, ll left, ll right, ll val) {
    if (tree[node].lazy.set) {
      tree[node].lazy.setVal += val; // уже меняли значение но не обновили
    }
    else {
      tree[node].lazy.addVal += val;
    }

    tree[node].sum += val * (right - left + 1);
  }

  void applyChange(ll node, ll left, ll right, ll val) {
    tree[node].lazy.set = true;
    tree[node].lazy.setVal = val;
    tree[node].lazy.addVal = 0;
    tree[node].sum = val * (right - left + 1);
  }

  void push(ll node, ll left, ll right) {
    if (left == right) return;

    ll mid = (right + left) / 2;
    ll leftC = node * 2;
    ll rightC = node * 2 + 1;

    if (tree[node].lazy.set) {
      applyChange(leftC, left, mid, tree[node].lazy.setVal);
      applyChange(rightC, mid + 1, right, tree[node].lazy.setVal);
      tree[node].lazy.set = false;
    }

    if (tree[node].lazy.addVal != 0) {
      applyAdd(leftC, left, mid, tree[node].lazy.addVal);
      applyAdd(rightC, mid + 1, right, tree[node].lazy.addVal);
      tree[node].lazy.addVal = 0;
    }
  }

  void updateAdd(ll node, ll left, ll right, ll ql, ll qr, ll val) {
    if (qr < left || right < ql) return;

    if (ql <= left && right <= qr) {
      applyAdd(node, left, right, val);
      return;
    }

    push(node, left, right);
    ll mid = (left + right) / 2;
    updateAdd(node * 2, left, mid, ql, qr, val);
    updateAdd(node * 2 + 1, mid + 1, right, ql, qr, val);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
  }

  void updateChange(ll node, ll left, ll right, ll ql, ll qr, ll val) {
    if (qr < left || right < ql) return;

    if (ql <= left && right <= qr) {
      applyChange(node, left, right, val);
      return;
    }

    push(node, left, right);
    ll mid = (left + right) / 2;
    updateChange(node * 2, left, mid, ql, qr, val);
    updateChange(node * 2 + 1, mid + 1, right, ql, qr, val);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
  }

  ll sum(ll node, ll left, ll right, ll ql, ll qr) {
    if (qr < left || right < ql) return 0;

    if (ql <= left && right <= qr) return tree[node].sum;

    push(node, left, right);
    ll mid = (left + right) / 2;
    return sum(node * 2, left, mid, ql, qr) + sum(node * 2 + 1, mid + 1, right, ql, qr);
  }

public:
  SegmentTree(ll size) {
    n = size;
    tree.resize(4 * n + 1);
  }

  void rangeAdd(ll left, ll right, ll val) {
    updateAdd(1,0,n - 1, left, right - 1, val);
  }

  void rangeChange(ll left, ll right, ll val) {
    updateChange(1,0,n - 1, left, right - 1, val);
  }

  ll rangeSum(ll left, ll right) {
    return sum(1, 0, n - 1, left, right - 1);
  }

};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll size, count;
  cin >> size >> count;

  SegmentTree st(size);
  ll type, f, s, val;

  vll ans;

  for (ll i = 0; i < count; i++) {
    cin >> type >> f >> s;
    if (type == 1) {
      cin >> val;
      st.rangeChange(f, s, val);
    } else if (type == 2) {
      cin >> val;
      st.rangeAdd(f, s, val);
    } else {
      ans.pb(st.rangeSum(f, s));
    }
  }


  for (ll i = 0; i < ans.size() - 1 ; ++i) cout << ans[i] << '\n';
  cout << ans[ans.size() - 1];

  return 0;
}
