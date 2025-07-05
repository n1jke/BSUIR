#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int64 mod_pow(int64 a, int64 b, int64 m) {
    int64 res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) {
            res = (int64)((__int128)res * a % m);
        }
        a = (int64)((__int128)a * a % m);
        b >>= 1;
    }
    return res;
}

int64 mod_inv(int64 a, int64 m) {
    return mod_pow(a, m - 2, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 N, M, K, MOD;
    cin >> N >> M >> K >> MOD;

    int64 p = mod_pow(M, N, MOD);
    int64 invK = mod_inv(K % MOD, MOD);
    int64 answer = (int64)((__int128)p * invK % MOD);

    cout << answer << "\n";
    return 0;
}
