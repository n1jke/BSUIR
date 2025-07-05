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

const ll MOD = 1e9 + 7;

struct Node {
    ll len, cnt;
    Node(ll l = 0, ll c = 0) : len(l), cnt(c) {}
};

class SegmentTree {
private:
    vector<Node> tree;
    ll n;

    Node merge(Node a, Node b) {
        if (a.len > b.len) return a;
        if (b.len > a.len) return b;
        return Node(a.len, (a.cnt + b.cnt) % MOD);
    }

    void update(ll idx, Node val, ll node, ll start, ll end) {
        if (start == end) {
            tree[node] = merge(tree[node], val);
        } else {
            ll mid = (start + end) / 2;
            if (idx <= mid) update(idx, val, 2 * node, start, mid);
            else update(idx, val, 2 * node + 1, mid + 1, end);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    Node query(ll l, ll r, ll node, ll start, ll end) {
        if (r < start || end < l) return Node(0, 0);
        if (l <= start && end <= r) return tree[node];
        ll mid = (start + end) / 2;
        Node left = query(l, r, 2 * node, start, mid);
        Node right = query(l, r, 2 * node + 1, mid + 1, end);
        return merge(left, right);
    }

public:
    SegmentTree(ll size) {
        n = size;
        tree.assign(4 * n + 1, Node(0, 0));
    }

    void update(ll idx, Node val) {
        update(idx, val, 1, 1, n);
    }

    Node query(ll l, ll r) {
        if (l > r) return Node(0, 0);
        return query(l, r, 1, 1, n);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    vll a(n);
    for (ll i = 0; i < n; ++i) cin >> a[i];

    // compress
    set<ll> unique_vals(a.begin(), a.end());
    vll sorted_unique(unique_vals.begin(), unique_vals.end());
    map<ll, ll> rank_map;
    for (ll i = 0; i < sorted_unique.size(); ++i) rank_map[sorted_unique[i]] = i + 1;

    ll m = sorted_unique.size();
    vll rank(n);
    for (ll i = 0; i < n; ++i) rank[i] = rank_map[a[i]];

    SegmentTree st(m);

    for (ll i = 0; i < n; ++i) {
        Node best = st.query(1, rank[i] - 1);
        Node cur;
        cur.len = best.len + 1;
        cur.cnt = (best.len == 0 ? 1 : best.cnt);
        st.update(rank[i], cur);
    }

    Node ans = st.query(1, m);
    cout << ans.cnt << '\n';

    return 0;
}
