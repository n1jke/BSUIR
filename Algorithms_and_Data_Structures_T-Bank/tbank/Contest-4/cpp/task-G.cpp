#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

const ll DAY = 86400;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll count = 0;
  cin >> count;
  ll removed = 0;
  vector<pair<ll, ll>> event;// start or end / typeof event

  ll hh, mm , ss, first, second;// first - open, second - close
  for (ll i = 0; i < count; ++i) {
    cin >> hh >> mm >> ss;
    first = hh * 3600 + mm * 60 + ss;
    cin >> hh >> mm >> ss;
    second = hh * 3600 + mm * 60 + ss;

    if (first == second) {
      ++removed;
      //event.push_back({0, 1});
      //event.push_back({DAY, -1});
    } else if (first < second) {
      event.push_back({first, 1});
      event.push_back({second, -1});
    } else {
      event.push_back({first, 1});
      event.push_back({DAY, -1});
      event.push_back({0, 1});
      event.push_back({second, -1});
    }
  }

  if (event.empty()) {
    cout << DAY << '\n'; 
    return 0;
}

  sort(event.begin(), event.end(), [](pair<ll, ll> a, pair<ll, ll> b) {
    if(a.first == b.first)  return a.second > b.second;
    return a.first < b.first;
  });

  ll countCass = 0;
  ll prevTime = 0;
  ll answer = 0;
  count -= removed;

  for (auto& sub : event) {
    ll time = sub.first;
    if (time > prevTime){
      if (countCass == count){
        answer += time - prevTime;
      } 
      prevTime = time;
    }
    countCass += sub.second; // time == prevTime
  }

  cout << answer << '\n';

  return 0;
}