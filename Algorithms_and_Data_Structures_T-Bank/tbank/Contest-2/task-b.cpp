#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

// need upsolve
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll size, window;
  cin >> size >> window;
  vector<ll> arr(size);
  for (ll i = 0; i < size; ++i){
    cin >> arr[i];
  }

  std::deque<ll> findMin;// indexes
  for (ll i = 0; i < size; ++i){
    while (!findMin.empty() && findMin.front() <= i - window){
      findMin.pop_front();
    }

    while (!findMin.empty() && arr[i] < arr[findMin.back()]){
      findMin.pop_back();
    }

    //if (findMin.empty()) no way because may stay some 
    findMin.push_back(i);

    if (i >= window - 1) cout << arr[findMin.front()] << ' ';
  }
  

  return 0;
}

//  1 3 2 | 4 | 7 | 1 |  size = 6 window = 3
//  0 1 2 3 4 5
//  2 4
// 1 2
