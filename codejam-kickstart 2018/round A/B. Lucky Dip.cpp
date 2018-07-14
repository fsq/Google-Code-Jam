#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>

using namespace std;

double a[20007], pre[20007];

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;

    for (int t=1; t<=T; ++t) {
        cout << "Case #" << t << ": ";
        int n, k;
        cin >> n >> k;

        double sum = 0;
        for (int i=1; i<=n; ++i) {
            cin >> a[i];
            sum += a[i];
        }
        sort(a+1, a+n+1);
        partial_sum(a+1, a+n+1, pre+1);

        double f = sum / n;
        for (int i=1; i<=k; ++i) {
            int it = lower_bound(a+1, a+1+n, f) - a;
            f = (f*(it-1) + (pre[n]-pre[it-1])) / n;
        }
        cout << std::fixed << setprecision(6) << f << '\n';

    }
    return 0;
}