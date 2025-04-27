#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

/*
1. В очередь пришел новый человек с уникальным номером id, он встает в очередь последним.
2. Человеку, стоящему спереди в очереди, удалось купить билет. Он уходит.
3. Человеку, стоящему последнему в очереди, надоело ждать. Он уходит.
4. Человек с уникальным номером q хочет знать, сколько людей стоит в очереди спереди него.
5. Очередь хочет знать, человек с каким уникальным номером стоит сейчас первым и задерживает всех.
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll count;
  ll token, index;
  deque<ll> queue;// people id 
  map<ll, ll> forward; // <index, queueNum> 

  cin >> count;
  --count;
  cin >> token >> index;
  queue.push_back(index);
  forward[index] = 0;
  
  for ( ;count; --count){
    cin >> token;
    if (token == 1){
      cin >> index;
      if (queue.empty()){
        forward[index] = 0;
      } else {
      forward[index] = forward[queue.back()] + 1;
      }
      queue.push_back(index);
    } else if (token == 2){
      if (!queue.empty()) queue.pop_front(); 
    } else if (token == 3) {
      if (!queue.empty()) queue.pop_back();
    } else if (token == 4){
      cin >> index;
      if (forward.find(index) != forward.end()) {
        cout << (forward[index] - forward[queue.front()]) << '\n';
      } else {
        cout << -1 << '\n';
      }
      //cout << (forward[index] - forward[queue.front()] ) << '\n'; 
    }else if (token == 5){
      if (!queue.empty()) {
        cout << queue.front() << '\n';
      } else {
        cout << -1 << '\n';
      }
    }
  }

  return 0;
}
