#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

// need upsolve
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll count, index;
  string token;
  deque<ll> left, right;

  cin >> count;
  count += 1;
for ( ; --count; ){
  cin >> token;

  if (token == "+") {
    cin >> index;
    right.push_back(index);
  } else if (token == "*") { // ohh to centre
    cin >> index;
    left.push_back(index);
  } else if (token == "-") { // shamanchik svyazuvai
    cout << left.front() << '\n';
    left.pop_front();
  }

  // balance two deque
  if (left.size() < right.size()) {
    left.push_back(right.front());
    right.pop_front();
  } else if (left.size() > right.size() + 1) {
    right.push_front(left.back());
    left.pop_back();
  }
}

  return 0;
}
