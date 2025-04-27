#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll countTest;
    cin >> countTest;

    ll op;      
    ll number;
    stack<pair<ll, ll>> solve;
    vector<ll> result;
    
    cin >> op >> number;
    ll currentMin = number;
    solve.push({number, currentMin});

    for (ll i = 1; i < countTest; ++i) {
        cin >> op;
        if (op == 1) { 
            cin >> number;
            if (solve.empty()) {
                currentMin = number;
            } else {
                currentMin = (number < solve.top().second ? number : solve.top().second);
            }
            solve.push({number, currentMin});
        } else if (op == 2) {
            solve.pop();
        } else if (op == 3) { 
            result.push_back(solve.top().second);
        }
    }

    for (const auto &num : result) {
        cout << num << '\n';
    }

    return 0;
}

/*
8
1 2
1 3
1 -3
3
2
3
2
3*/