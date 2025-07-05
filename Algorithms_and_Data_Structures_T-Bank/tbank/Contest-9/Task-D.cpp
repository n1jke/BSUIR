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
    ll maxCover = 0;
    ll lazy = 0; // lazy update tp children
    ll idx = 0;
};

class SegmentTree {
    vector<Node> tree;
    ll size;

    void apply(ll node, ll left, ll right, ll delta) { // apply delta for node & upd lazy
        tree[node].maxCover += delta;
        tree[node].lazy += delta;
    }

    void push(ll node, ll left, ll right) {   // push to children
        if (tree[node].lazy != 0 && left != right) {
            ll mid = (left + right) / 2;
            apply(node * 2, left, mid, tree[node].lazy);
            apply(node * 2 + 1, mid + 1, right, tree[node].lazy);
        }
        tree[node].lazy = 0; // already pushed to children
    }

    void pull(ll node) {   // upd from children
        ll lVal = tree[node * 2].maxCover;
        ll rVal = tree[node * 2 + 1].maxCover;
        if (lVal >= rVal) {
            tree[node].maxCover = lVal;
            tree[node].idx = tree[node * 2].idx;
        } else {
            tree[node].maxCover = rVal;
            tree[node].idx = tree[node * 2 + 1].idx;
        }
    }

    void build(ll node, ll left, ll right) {
        if (left == right) {
            tree[node].idx = left;
            return;
        }
        ll mid = (left + right) / 2;
        build(node * 2, left, mid);
        build(node * 2 + 1, mid + 1, right);
        pull(node);
    }

    void update(ll node, ll left, ll right, ll ql, ll qr, ll delta) {
        if (qr < left || right < ql) return;
        if (ql <= left && right <= qr) {
            apply(node, left, right, delta);
            return;
        }
        push(node, left, right);
        ll mid = (left + right) / 2;
        update(node * 2, left, mid, ql, qr, delta);
        update(node * 2 + 1, mid + 1, right, ql, qr, delta);
        pull(node);
    }

public:
    SegmentTree(ll n) : size(n) {
        tree.resize(4 * n);
        build(1, 0, size - 1);
    }

    void modify(ll l, ll r, ll delta) {
        update(1, 0, size - 1, l, r, delta);
    }

    pll getMax() const {
        return {tree[1].maxCover, tree[1].idx };
    }
};

struct Window {
    ll type, x, y1, y2;
    Window(ll x_, ll y1_, ll y2_, ll type_) : type(type_), x(x_), y1(y1_), y2(y2_) {}
    bool operator<(const Window& o) const {
        if (x != o.x) return x < o.x;
        return type > o.type; // first add 2-nd delete&&!&!
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
        events.pb(x1, y1, y2, 1);
        events.pb(x2 + 1, y1, y2, -1);
        yCoords.pb(y1);
        yCoords.pb(y2);
    }

    sort(yCoords.begin(), yCoords.end());
    yCoords.erase(unique(yCoords.begin(), yCoords.end()), yCoords.end());


    auto getYIndex = [&](long long y) {
        return static_cast<ll>(lower_bound(yCoords.begin(), yCoords.end(), y) - yCoords.begin());
        //  lower_bound find first elem >= y in range .begin() -> .end() O(logN)
        //  comeback with itaretor in struct if not exist it = .end()
        //  can use inside lambda for complex types -- lower_bound(begin, end, value, [](int a, int b){ return a < b; });
    };

    // auto it = lower_bound(yCoords.begin(), yCoords.end(), 1);
    // ll indx = it - yCoords.begin();
    // cout << indx << " " << yCoords[indx] << " " <<  *it << '\n';

    for (auto& e : events) { // change new compressed coord indx
        e.y1 = getYIndex(e.y1);
        e.y2 = getYIndex(e.y2);
    }

    sort(events.begin(), events.end());
    SegmentTree segTree(yCoords.size());

    ll maxCover = 0, bestX = 0, bestY = 0;

    for (size_t i = 0; i < events.size(); ) {
        ll currX = events[i].x;
        while (i < events.size() && events[i].x == currX) { // same starts for lazyyyy
            segTree.modify(events[i].y1, events[i].y2, events[i].type);
            ++i;
        }
        auto [curMax, yIdx] = segTree.getMax();
        if (curMax > maxCover) {
            maxCover = curMax;
            bestX = currX;
            bestY = yCoords[yIdx];
        }
    }

    cout << maxCover << '\n' << bestX << ' ' << bestY << '\n';

    return 0;
}
