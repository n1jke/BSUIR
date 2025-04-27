#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll count = 0;
  cin >> count;
  vector<pair<ll, ll>> otr(count);

  for (ll i = 0; i < count; ++i) {
    cin >> otr[i].first >> otr[i].second;
  }

  std::sort(otr.begin(), otr.end());

  ll curr_left = otr[0].first;
  ll curr_right = otr[0].second;
  ll lenght = 0;

  for (ll i = 1; i < otr.size(); ++i){
    if (otr[i].first <= curr_right) {
      curr_right = max(otr[i].second , curr_right);
    } else {
      lenght += curr_right - curr_left;

      curr_left = otr[i].first;
      curr_right = otr[i].second;
    }
  }

  lenght += (curr_right - curr_left);

  cout << lenght << '\n';


  return 0;
}
