#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;


int main() {
    int size;
    cin >> size;
    vector<ll> A(size, 0);// basic arr with 0
    vector<ll> result;
    result.push_back(1);
    ll ones = 0;
    ll lenght = 0;
    
//(ones - lenght + 1));

  for (ll i = 0; i < size; ++i){
  ll pos;
  cin >> pos;
  pos--;
  if(A[pos] == 0){
    A[pos] = 1;
    ones++;
  }
  
  while(lenght < size && A[size - 1 - lenght] == 1){
    ++lenght;
  }
  result.push_back(ones - lenght + 1);
  }

  for (ll& res : result){
    cout << res << '\n';
  }
  return 0;
}

