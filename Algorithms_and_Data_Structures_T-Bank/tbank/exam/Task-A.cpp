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

struct comp {
	ll time, count, relax;
};

ll maxSubmiss(ll time, const comp& one) {
	ll cycle = one.time * one.count + one.relax;
	ll full = time / cycle;
	ll remaining_time = time % cycle;
	ll add = min(one.count, remaining_time / one.time);
	return full * one.count + add;
}

bool canPerform(ll time, const vector<comp>& info, ll request) {
	ll total = 0;
	for (const auto& c : info) {
		total += maxSubmiss(time, c);
		if (total >= request) return 1;
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll request, count;
	cin >> request >> count;
	vector<comp> 	info(count);

	for (ll i = 0; i < count; i++) {
		cin >> info[i].time >> info[i].count >> info[i].relax;
	}

	ll left = 1, right  = 6e18;
	ll ansTime = 1e18;

	while (left <= right) {
		ll mid = left + (right - left) / 2;
		if (canPerform(mid, info, request)) {
			ansTime = mid;
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	vll result(count,0);
	ll remain = request;

	for (ll i = 0; i < count && remain > 0; ++i) {
		ll possible = maxSubmiss(ansTime, info[i]);
		result[i] = min(possible, remain);
		remain -= result[i];
	}

	cout << ansTime << '\n';
	for (const auto& one : result) {
		cout << one << " ";
	}

	return 0;
}