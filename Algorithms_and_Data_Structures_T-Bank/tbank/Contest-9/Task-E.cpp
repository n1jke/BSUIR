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
#define pb emplace_back

struct Node {
    ll cov = 0;
    ll len = 0;
};

class SegmentTree {
    vector<Node> tree;
    ll size;
    const vll& yCoords;

    void apply(ll node, ll left, ll right, ll delta) {
        tree[node].cov += delta;
        if (tree[node].cov > 0) {
            tree[node].len = yCoords[right + 1] - yCoords[left];
        } else if (left == right) {
            tree[node].len = 0;
        } else {
            tree[node].len = tree[node * 2].len + tree[node * 2 + 1].len;
        }
    }

    void update(ll node, ll left, ll right, ll ql, ll qr, ll delta) {
        if (qr < left || right < ql) return;
        if (ql <= left && right <= qr) {
            apply(node, left, right, delta);
            return;
        }
        ll mid = (left + right) / 2;
        update(node * 2, left, mid, ql, qr, delta);
        update(node * 2 + 1, mid + 1, right, ql, qr, delta);
        if (tree[node].cov > 0) {
            tree[node].len = yCoords[right + 1] - yCoords[left];
        } else {
            tree[node].len = tree[node * 2].len + tree[node * 2 + 1].len;
        }
    }



public:
    SegmentTree(ll n, const vll& y) : size(n), yCoords(y) {
        tree.resize(4 * n);
    }

    void modify(ll l, ll r, ll delta) {
        update(1, 0, size - 1, l, r - 1, delta);
    }

    ll coveredLength() const {
        return tree[1].len;
    }
};

struct Window {
    ll x, y1, y2, type;
    Window(ll x_, ll y1_, ll y2_, ll type_) : x(x_), y1(y1_), y2(y2_), type(type_) {}
    bool operator<(const Window& o) const {
        return x < o.x;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    vector<Window> events;
    vll yCoords;

    for (ll i = 0; i < n; ++i) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        if (y1 == y2) {
            // horizontal
            events.pb(x1,     y1, y1 + 1, +1);
            events.pb(x2 + 1, y1, y1 + 1, -1);
            yCoords.pb(y1); yCoords.pb(y1 + 1);
        } else {
            // vertical
            events.pb(x1, y1, y2 + 1, +1);
            events.pb(x1 + 1, y1, y2 + 1, -1);
            yCoords.pb(y1); yCoords.pb(y2 + 1);
        }
    }

    sort(yCoords.begin(), yCoords.end());
    yCoords.erase(unique(yCoords.begin(), yCoords.end()), yCoords.end());

    auto getYIndex = [&](ll y) {
        return static_cast<ll>(lower_bound(yCoords.begin(), yCoords.end(), y) - yCoords.begin());
    };

    for (auto& e : events) {
        e.y1 = getYIndex(e.y1);
        e.y2 = getYIndex(e.y2);
    }

    sort(events.begin(), events.end());
    SegmentTree segTree(static_cast<ll>(yCoords . size()) - 1, yCoords);

    ll area = 0;
    ll prevX = events[0].x;

    for (auto& e : events) {
        ll dx = e.x - prevX;
        if (dx > 0) {
            area += segTree.coveredLength() * dx;
            prevX = e.x;
        }
        segTree.modify(e.y1, e.y2, e.type);
    }

    cout << area << '\n';
    return 0;
}
