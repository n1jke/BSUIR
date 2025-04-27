#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> wagons(n);
  for (int i = 0; i < n; i++){
    cin >> wagons[i];
  }

  int inputIndex = 0;  
  int nextExpected = 1;// который мы зотетим следующим накатить
  stack<int> typic;
  vector<pair<int, int>> moves; //{oper, count}
    
  while(nextExpected <= n){
    // вершинf тупика  <--> нужный вагон --> выводим его
    if (!typic.empty() && typic.top() == nextExpected) {
      typic.pop();
      moves.push_back({2, 1});
      ++nextExpected;
    }
    // в противном в тупик
    else if (inputIndex < n) {
      typic.push(wagons[inputIndex]);
      moves.push_back({1, 1});
      ++inputIndex;
    }
    // если ничего неляза то мы лохи!?!?!?!
    else {
      cout << 0 << '\n';
      return 0;
    }
  }
    // подряд идущие одного типа в одну
  vector<pair<int, int>> aggregated;
  for (auto op : moves) {
    if (!aggregated.empty() && aggregated.back().first == op.first)
      aggregated.back().second += op.second;
    else
      aggregated.push_back(op);
  }
  cout << aggregated.size() << "\n";
  for (auto op : aggregated) {
    cout << op.first << " " << op.second << "\n";
  }
  return 0;
}
