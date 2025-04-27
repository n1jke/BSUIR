#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t size = 0;
  cin >> size;

  vector<ll> nums(size);
  vector<ll> prefixSum(size + 1, 0);
  stack<ll> minLeft;

  for (ll i = 0; i < size; ++i) {
    cin >> nums[i];
    prefixSum[i + 1] = nums[i] + prefixSum[i];
  }

  vector<ll> left(size), right(size);
  stack<int> st;
    for (int i = 0; i < size; ++i) {
        while (!st.empty() && nums[st.top()] >= nums[i]) st.pop();

        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();// clear

    for (int i = size - 1; i >= 0; --i) {
      while (!st.empty() && nums[st.top()] >= nums[i]) st.pop();

      right[i] = st.empty() ? size : st.top();
      st.push(i);
    }


  ll result = -1;
  for (ll i = 0; i < size; ++i){
    ll sum = prefixSum[right[i]] - prefixSum[left[i] + 1];
    ll candidate = nums[i] * sum;
    result = max(result, candidate);
  }

  cout << result;

  return 0;
}
