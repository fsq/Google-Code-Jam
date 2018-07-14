#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;

    for (int t=1; t<=T; ++t) {
        cout << "Case #" << t << ": ";

        string s;
        cin >> s;
        while (!s.empty() && !((s.front()-'0') & 1)) s.erase(s.begin());
        if (s.empty()) {
            cout << 0 << '\n';
        } else {
            long long a = stoll(s);
            int head = s.front();
            long long up, lo;
            int l = s.size();
            if (head=='9') {
                up = stoll("2" + string(l, '0'));
            } else {
                up = stoll(string(1, head+1) + string(l-1, '0'));
            }
            if (head=='1') {
                lo = l==1 ? 0 : stoll(string(l-1, '8'));
            } else {
                lo = stol(string(1, head-1) + string(l-1, '8'));
            }
            cout << min<long long>(up-a, a-lo) << '\n';
        }
    }
    return 0;
}