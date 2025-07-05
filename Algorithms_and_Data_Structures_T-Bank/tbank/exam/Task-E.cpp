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

class SegTree {
	ll size;
	vll countOne;
	vector<bool> lazy;

	void build(const vll& bits, ll node, ll left, ll right) {
		if (left == right) {
			countOne[node] = bits[left];
			return;
		}
		ll mid = (left + right) / 2;
		build(bits, node * 2, left, mid);
		build(bits, node * 2 + 1, mid + 1, right);
		countOne[node] = countOne[node * 2] + countOne[node * 2 + 1];
	}

	void push(ll node, ll left, ll right) {
		if (!lazy[node]) return;

		countOne[node] = (right - left + 1) - countOne[node];
		if (left != right) {
			lazy[node*2] = !lazy[node*2];
			lazy[node*2 + 1] = !lazy[node*2 + 1];
		}
		lazy[node] = false;
	}

	void updateRange(ll node, ll left, ll right, ll l,ll r) {
		push(node, left, right);
		if (r < left || right < l) return;
		if (l <= left && right <= r) {
			lazy[node] = lazy[node] ^ 1;
			push(node, left, right);
			return;
		}
		ll mid = (left + right) / 2;
		updateRange(node * 2, left, mid, l, r);
		updateRange(node * 2 + 1, mid + 1, right, l, r);
		countOne[node] = countOne[node * 2] + countOne[node * 2 + 1];
	}

	ll Range(ll node, ll left, ll right, ll l, ll r) {
		push(node, left, right);
		if (r < left || right < l) return 0;
		if (l <= left && right <= r) {
			return countOne[node];
		}
		ll mid = (left + right) / 2;
		return Range(node * 2, left, mid, l, r) + Range(node * 2 + 1, mid + 1, right, l, r);
	}

public:
	SegTree(ll size, const vll& bits) : size(size), countOne(size * 4 + 10, 0), lazy(size* 4 + 10, false) {
		build(bits, 1, 1, size);
	}
	void xorRange(ll l, ll r) {
		updateRange(1, 1, size, l, r);
	}

	ll countOnes(ll l, ll r) {
		return Range(1,1,size, l, r);
	}
};

class XorSum {
	ll n;
	vector<SegTree> bitTrees;

public:
	XorSum(const vll& nums)
			 : n(nums.size() - 1)
	{
		for (ll bit = 0; bit < 20; ++bit) {
			vll bitArr(n + 1, 0);
			for (ll i = 1; i <= n; ++i) {
				bitArr[i] = (nums[i] >> bit) & 1;
			}
			bitTrees.emplace_back(n, bitArr);
		}
	}

	void Apply(ll l, ll r, ll x) {
		for (ll bit = 0; bit < 20; ++bit) {
			if ( (x >> bit) & 1LL ) {
				bitTrees[bit].xorRange(l, r);
			}
		}
	}

	ll Sum(ll l, ll r) {
		ll res = 0;
		for (ll bit = 0; bit < 20; ++bit) {
			ll ones = bitTrees[bit].countOnes(l,r);
			res += ones * (1LL << bit); // 2^bit
		}
		return res;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll count;
	cin >> count;
	vll nums(count + 1);
	for (ll i = 1; i <= count; ++i) cin >> nums[i];

	XorSum xorSum(nums);
	ll request;
	cin >> request;

	while (request--) {
		ll type, l, r;
		cin >> type >> l >> r;
		if (type == 1) {
			cout << xorSum.Sum(l, r) << '\n';
		} else {
			ll x;
			cin >> x;
			xorSum.Apply(l, r, x);
		}
	}

	return 0;
}

