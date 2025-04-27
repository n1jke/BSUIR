#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll evaluate(const string& expr) {
    string t;
    t.reserve(expr.size());
    for (char c : expr)
        if (c != ' ')
            t.push_back(c);

    ll result = 0;
    int n = t.size();
    vector<ll> stk;
    stk.reserve(128);
    stk.push_back(1);

    int i = 0;
    while (i < n) {
        char c = t[i];
        if (c == '+' || c == '-') {
            int net = 1;
            while (i < n && (t[i] == '+' || t[i] == '-')) {
                if (t[i] == '-')
                    net = -net;
                ++i;
            }
            if (i < n && isdigit(t[i])) {
                ll num = 0;
                while (i < n && isdigit(t[i])) {
                    num = num * 10 + (t[i] - '0');
                    ++i;
                }
                result += stk.back() * net * num;
            }
            else if (i < n && t[i] == '(') {
                stk.push_back(stk.back() * net);
                ++i;
            }
        }
        else if (c == '(') {
            stk.push_back(stk.back());
            ++i;
        }
        else if (c == ')') {
            stk.pop_back();
            ++i;
        }
        else if (isdigit(c)) {
            ll num = 0;
            while (i < n && isdigit(t[i])) {
                num = num * 10 + (t[i] - '0');
                ++i;
            }
            result += stk.back() * num;
        }
        else {
            ++i;
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);
    cout << evaluate(s) << "\n";
    return 0;
}
