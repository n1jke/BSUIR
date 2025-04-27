#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

/*
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m, k;
  cin >> n >> m >> k;

  vector<string> prefix(n);
  vector<string> sufix(m);
  for(ll i = 0 ; i < n; ++i){
    cin >> prefix[i];
  }

  for (ll i = 0; i < m; ++i){
    cin >> sufix[i];
  }

  sort(prefix.begin(), prefix.end());
  sort(sufix.begin(), sufix.end());

  ll temp, pr, sf;
  for ( ;k; --k){
    cin >> temp;
    --temp; // throw 0 num
    // all is n* m
    // pr is the maxest we can do
    pr = temp / m;
    sf = temp % m;
    cout << prefix[pr] << '_' << sufix[sf] << '\n';
  }

  return 0;
}
*/