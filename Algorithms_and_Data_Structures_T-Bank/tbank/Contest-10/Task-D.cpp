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

struct monster {
	ll damage;
	ll health;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll count;
	cin >> count;
	vector<monster> monsters(count);
	vll answers(count);

	for (auto& m : monsters) cin >> m.damage;
	for (auto& m : monsters) cin >> m.health;

	vll left(count), right(count), alive(count, 1);
	for (ll i = 0; i < count; ++i) {
		left[i] = i - 1;
		right[i] = i + 1;
	}

	ll round = 0;
	while (true) {
		vll damage_received(count, 0);
		vll to_die;

		for (ll i = 0; i < count; ++i) {
			if (!alive[i]) continue;
			if (left[i] >= 0 && alive[left[i]]) damage_received[left[i]] += monsters[i].damage;
			if (right[i] < count && alive[right[i]]) damage_received[right[i]] += monsters[i].damage;
		}

		for (ll i = 0; i < count; ++i) {
			if (alive[i] && damage_received[i] > monsters[i].health)
				to_die.pb(i);
		}

		if (to_die.empty()) break;

		for (ll i : to_die) {
			alive[i] = 0;
			if (left[i] >= 0) right[left[i]] = right[i];
			if (right[i] < count) left[right[i]] = left[i];
		}

		answers[round++] = to_die.size();
	}

	for (const auto& a : answers) cout << a << ' ';

	return 0;
}
