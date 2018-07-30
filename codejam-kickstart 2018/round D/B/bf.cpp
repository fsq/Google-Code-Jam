#include "/Users/fsq/stdc++.h"

int n, k;
vector<LL> p, h, x, y;

void init(vector<LL>& a, int n) {
    LL x1, x2, A, B, C, M;
    cin >> x1 >> x2 >> A >> B >> C >>M;
    a.clear();
    a.resize(n+1);
    a[1] = x1, a[2] = x2;
    REP(i, 3, n) {
        LL xi = (A*x2 + B*x1 + C) % M + 1;
        a[i] = xi;
        x1 = x2;
        x2 = xi;
    }
}


int main() {
    int numCases;
    cin >> numCases;
    for (int cases=1; cases<=numCases; ++cases) {
        cout << "Case #" << cases << ": ";
        cin >> n >> k;
        init(p, n);
        init(h, n);
        init(x, k);
        init(y, k);


        vector<int> ok(k+1);
        int ans = 0;
        REP(i, 1, k) {
            REP(j, 1, n) {
                // if (p[j]==x[i] && y[i]<=h[j])
                //     ok[i] = 1;
                // else if (p[j]<x[i] && h[j]+p[j]>=x[i]+y[i] ||
                //          p[j]>x[i] && h[j]-p[j]>=y[i]-x[i])
                //     ok[i] = 1;
                // if (ok[i]) {
                //     // printf("%d %d\n", i, j);
                //     break;
                // }
                if (y[i]+abs(p[j]-x[i])<=h[j]) {
                    // ok[i] = 1;
                    ++ans;
                    break;
                }
            }

        }

        // cout << accumulate(ok.begin(), ok.end(), 0) << '\n';
        cout << ans << endl;
    }
    return 0;
}
