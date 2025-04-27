#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;


int main() {
  ll size;
  cin >> size;
  string base;
  cin >> base;

  map<char, int> symbols;
  for(ll i = 0; i < base.size(); ++i){
    ++symbols[char(base[i])]; 
  }

  bool isMid = false;
  string start, mid, end;
  for (auto& [letter,count] : symbols) {
  if (count % 2 != 0 && !isMid){
    mid = letter;
    isMid = true;
    --count;
  }
  start.append(count / 2, letter);
  //end = letter + end;
  }
  end = start;
  reverse(end.begin(), end.end());
  cout << start + mid + end;  
  
  return 0;
}