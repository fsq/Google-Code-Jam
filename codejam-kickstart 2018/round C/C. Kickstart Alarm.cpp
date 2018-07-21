#include "/Users/fsq/stdc++.h"

using namespace std;

LL M=1e9+7, k;

VLL a, g, preg;
int n;

LL myp(LL a, LL b) {
    if (a==1) return 1;
    if (b==0) return 1;
    if (b==1) return a;
    LL x = myp(a, b>>1);
    return (b&1) ? x*x%M*a%M : x*x%M;
}

void initg() {
    g.resize(n+1);
    g[1] = k;
    REP(i, 2, n) 
        g[i] = (myp(i, k+1)-i + M) % M * myp(i-1, M-2) % M;
    
    preg.resize(n+1);
    REP(i, 1, n)
        preg[i] = (preg[i-1] + g[i]) % M;
}


void init() {
    LL x,y,c,d,e1,e2,F;
    cin >> n >> k >> x >> y >> c >> d >> e1 >> e2 >> F;
    
    a.resize(n+1);
    REP(i, 1, n) {
        LL ai = (x + y) % F;
        a[i] = ai;
        LL xi = (c*x + d*y + e1) % F;
        LL yi = (d*x + c*y + e2) % F;
        x = xi, y = yi;
    }
    initg();
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) {
        init();
        LL ans = 0;
        REP(i, 1, n) 
            ans = (ans + (a[i] * ((n-i+1) * preg[i] % M)) % M) % M;

        cout << "Case #" << t << ": " << ans << '\n';

    }
    return 0;
}