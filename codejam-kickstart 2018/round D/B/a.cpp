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
    // for (auto x : a) cout << x << ' '; cout << endl;
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

        vector<pair<LL,LL>> pl(n+1);
        REP(i, 1, n) pl[i] = {p[i], h[i]};
        sort(pl.begin()+1, pl.end());
        REP(i, 1, n)
            p[i] = pl[i].first, h[i] = pl[i].second;

        vector<pair<LL,LL>> bl(k+1);
        REP(i, 1, k) bl[i] = {x[i], y[i]};
        sort(bl.begin()+1, bl.end());
        REP(i, 1, k)
            x[i] = bl[i].first, y[i] = bl[i].second;


        vector<int> ok(k+1);
        set<LL> st;
        int l = 1;
        REP(i, 1, k) {
            while (l<=n && p[l]<=x[i]) {
                st.insert(p[l]+h[l]);
                ++l;
            }
            if (st.lower_bound(x[i]+y[i])!=st.end())
                ok[i] = 1;
        }

        st.clear();
        int r = n;
        PER(i, k, 1) {
            while (r>0 && p[r]>=x[i]) {
                st.insert(h[r]-p[r]);
                --r;
            }
            if (st.lower_bound(y[i]-x[i])!=st.end())
                ok[i] = 1;
        }

        cout << accumulate(ok.begin(), ok.end(), 0) << '\n';
    }
    return 0;
}
