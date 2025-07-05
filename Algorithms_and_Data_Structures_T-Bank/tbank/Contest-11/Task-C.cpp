#include <bits/stdc++.h>
using namespace std;

#define ll  long long
#define ld long double
#define str string
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll, ll>
#define vstr vector<str>
#define vpll vector<pll>
#define pb push_back

const ll MAXN = 100;

str longestPalindrome(const str& input) {
  if (input.length() == 1) return input;

  ll size = input.size();
  vector dp(size, vll(size, 0));
  ll start = 0, mlen = 1; ;
  for (ll i = 0; i < size; ++i) dp[i][i] = true;

  for (int len = 2; len <= size; ++len) {
    for (int i = 0; i <= size - len; ++i) {
      int j = i + len - 1;
      if (input[i] == input[j]) {
        dp[i][j] = (len == 2) ? 2 : dp[i + 1][j - 1] + 2;
      } else {
        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
      }
    }
  }

  str res(dp[0][size - 1], ' ');
  ll i = 0, j = size - 1;
  ll left = 0, right = res.size() - 1;

  while (i <= j) {
    if (input[i] == input[j]) {
      res[left++] = input[i];
      res[right--] = input[j];
      i++;
      j--;
    } else if (dp[i + 1][j] > dp[i][j - 1]) {
      i++;
    } else {// <
      j--;
    }
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  str input;
  getline(cin, input);
  str ans = longestPalindrome(input);
  cout << ans.length() << '\n' << ans;

  return 0;
}