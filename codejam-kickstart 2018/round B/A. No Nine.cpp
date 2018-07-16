#include <vector>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using ll = long long;

bool ok(ll x) {
    return x%9!=0 && to_string(x).find('9')==string::npos;
}

ll count(ll x) {
    ll ans = 0;
    for (int i=0; i<=x%10; ++i)
        if (ok(x-i)) ++ans;

    x -= x % 10;
    ll e=0;
    for (ll s=1; x; s*=9) {
        e += x % 10 * s;
        x /= 10;
    }

    return ans + 8*e/9;
}

int main() {
    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) {
        ll x, y;
        cin >> x >> y;
        // cout << count(y) << ' '<<count(x-1) << endl;
        cout << "Case #" << t << ": " << count(y) - count(x-1) << endl;
    }
    return 0;
}