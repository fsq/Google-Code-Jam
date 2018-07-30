#include "/Users/fsq/stdc++.h"

int n, maxo;
LL d;

vector<LL> a, s;
vector<int> od;


void init() {
    a.clear(), s.clear(), od.clear();
    cin >> n >> maxo >> d;
    a.resize(n+1);
    LL x1, x2, A, B, C, M, L;
    cin >> x1 >> x2 >> A >> B >> C >> M >> L;

    a[1]  = x1 + L, a[2] = x2 + L;
    REP(i, 3, n) {
        LL xi = (A*x2 + B*x1 + C) % M;
        a[i] = xi + L;
        x1 = x2;
        x2 = xi;
    }

    od.resize(n+1), s.resize(n+1);
    REP(i, 1, n) {
        od[i] = od[i-1] + abs(a[i]%2);
        // cout << od[i] << ' ';
    }
    REP(i, 1, n) s[i] = s[i-1] + a[i];

}   

int main() {
    int numCases;
    cin >> numCases;
    for (int cases=1; cases<=numCases; ++cases) {
        cout << "Case #" << cases << ": ";

        init();

        LL ans = INT_MIN;
        multiset<LL> st = {0};

        for (int l=0,r=1; r<=n; ++r) {
            while (l<r && od[l]<od[r]-maxo) {
                // printf("erase%d\n", s[l]);
                auto it = st.find(s[l++]);
                if (it!=st.end()) st.erase(it);
            }
            auto it = st.lower_bound(s[r]-d);
            if (it!=st.end()) 
                ans = max(ans, s[r]-*it);
            // printf("%d %d\n", r, ans);
            // printf("insert%d\n", s[r]);
            st.insert(s[r]);
        }


        if (ans==INT_MIN) 
            cout << "IMPOSSIBLE\n";
        else
            cout << ans << '\n';

    }
    return 0;
}
