#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    stack<ll> nums;
    string token;

    while (cin >> token) { 
        if (token == "+") {
            ll second = nums.top(); nums.pop();
            ll first = nums.top(); nums.pop();
            nums.push(first + second);
        } else if (token == "-") {
            ll second = nums.top(); nums.pop();
            ll first = nums.top(); nums.pop();
            nums.push(first - second);
        } else if (token == "*") {
            ll second = nums.top(); nums.pop();
            ll first = nums.top(); nums.pop();
            nums.push(first * second);
        } else { 
            nums.push(stoll(token));
        }
    }

    cout << nums.top();

    return 0;
}
