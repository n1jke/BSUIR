#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> balls(n);
    for (int i = 0; i < n; i++){
        cin >> balls[i];
    }
    
    ll counter = 0;
    bool removed = true;

    while(removed) {
        removed = false;
        vector<ll> newBalls;
        for (int i = 0; i < balls.size(); ) {
            int j = i;
            // ищем границы группы с одинаковыми
            while(j < balls.size() && balls[j] == balls[i])
                j++;
            int count = j - i;
            if(count >= 3) {
                counter += count;
                removed = true;
            } else {
                // иначе копируем группу в новый вектор
                for (int k = i; k < j; k++){
                    newBalls.push_back(balls[k]);
                }
            }
            i = j;
        }
        balls = newBalls;
    }
    
    cout << counter;
    return 0;
}

/*
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  stack<ll> nums;
  ll  size = 0;
  cin >> size;
  ll num;
  ll counter = 0;

  for ( ; size ; --size) { 
    cin >> num;

    if (nums.size() >= 2 ){
    ll top = nums.top(); nums.pop();
    ll beforeTop = nums.top(); 
    nums.push(top);

    if (num == top && top == beforeTop){
      nums.pop();
      nums.pop();
      counter += 3;
      if (!nums.empty()) {
        while (nums.top() == num){
          ++counter;
          nums.pop();
        }
      }
      while (size){
        cin >> num;
        --size;
        if (num == top) {
          ++counter;
        } else break;
      }
    } 
    else {
      nums.push(num);
    }

    } else nums.push(num);
  }

  cout << counter;

  return 0;
}
*/
