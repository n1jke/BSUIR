#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

struct triplePair {
    long long s; // момент появления задачи
    long long t; // время, отведенное на решение задачи
    int idx;    // номер задачи (изначальный порядок)
};

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
    
  ll n;
  ll c;
  cin >> n >> c;

  vector<triplePair> tasks(n);
  for (ll i = 0; i < n; ++i){
    cin >> tasks[i].s >> tasks[i].t;
    tasks[i].idx = i + 1; // task descr
  }
    
    // Сsort by end time(s + t) upper
  sort(tasks.begin(), tasks.end(), [](triplePair &a, triplePair &b){
    return (a.s + a.t) < (b.s + b.t);
  });
    
  ll currTime = 0;
  vector<ll> chosen; // result

  for (ll i = 0; i < n; i++){
    if (tasks[i].s >= currTime) {
      chosen.push_back(tasks[i].idx);
      currTime = tasks[i].s + tasks[i].t;
      }
  }
    
    cout << (ll)chosen.size() * c << "\n" << chosen.size() << "\n";
    for (int idx : chosen) {
      cout << idx << ' ';
    }
    //cout << "\n";
    
    return 0;
}
