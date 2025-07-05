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

ll INF = 1e18;

ll findMinCost(const vll& points) {
	vector dp(points.size(), vll(points.size(), INF)); // min cost : points[i] -> points[j] devide

	for (ll i = 0; i < points.size() - 1; ++i) dp[i][i + 1] = 0;

	for (ll len = 2; len < points.size(); ++len) {
		for (ll left = 0; left  + len < points.size(); ++left) {
			ll right = left + len;
			for (ll i = left + 1; i < right; ++i) {
				dp[left][right] = min(dp[left][right], dp[left][i] + dp[i][right] + points[right] - points[left]);
			}
		}
	}

  return dp[0][dp.size() - 1];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

  ll len, count;
  cin >> len >> count;
  vll points(count + 2);
  points[0] = 0;
  points[count + 1] = len;
  for (ll i = 1; i <= count; i++) cin >> points[i];
	sort(points.begin(), points.end());

  cout << findMinCost( points);

	return 0;
}