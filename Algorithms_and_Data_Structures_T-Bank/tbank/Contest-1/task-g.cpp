#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
  ll n;
  vector<ll> mas;
  cin >> n;
  mas.resize(n);

  for (int i=0;i<n;i++){ 
    mas[i] = i + 1;
  }
  for (int i = 2; i < n; i++){
    swap(mas[i], mas[i / 2]);
  }
  for (int i = 0 ; i < n ; i++)
    cout << mas[i] << " ";
  

  
  return 0 ;
}