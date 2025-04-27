  #include <bits/stdc++.h>
  using namespace std;

  #define ll long long
  #define vll vector<ll>
  #define pb push_back

  ll binSearch(const vll& nums, ll target) {
    ll left = 0;
    ll right = nums.size() - 1;

    ll best = -1;
    ll bestDiff = 100000000000;

    while (left <= right) {
      ll mid = left + (right - left) / 2;
      ll diff = abs(nums[mid] - target);

      if (diff < bestDiff || (diff == bestDiff && mid < best)) {
        bestDiff = diff;
        best = mid;
      }

      if (nums[mid] == target) {
        return mid;
      } else if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return best;
  }

vll findClosest(const vll& numbers, ll target, ll count) {
    if (count == 0) {
      vll ans;
      return  ans;
    }

    ll best = binSearch(numbers, target);
    ll left = best - 1, right = best + 1;

    while (right - left - 1 < count) {
      if (left < 0 && right >= numbers.size()) {
        break;
      }
      if (left < 0) {
        ++right;
      } else if (right >= numbers.size()) {
        --left;
      } else {
        ll l = target - numbers[left];
        ll r = numbers[right] - target;
        if (l <= r) {
          --left;
        } else {
          ++right;
        }
      }
    }



    return vll (numbers.begin() + left + 1, numbers.begin() + right);;
  }

  int main() {
    ll size;
    cin >> size;
    vll numbers(size);

    for (ll i = 0; i <size; i++) cin >> numbers[i];

    ll target, count;
    cin >> target >> count;
    vll ans = findClosest(numbers, target, count);

    for (auto& a : ans) cout << a << " ";

    return 0;
   }