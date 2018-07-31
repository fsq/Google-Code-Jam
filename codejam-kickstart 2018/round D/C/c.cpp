#include "/Users/fsq/stdc++.h"

int n, m, w;

vector<string> a, dict;
// (i,j) length<=k
int lf[103][103][103], up[103][103][103];

void init() {
    a.clear();
    dict.clear();
    MEMSET(lf, 0);
    MEMSET(up, 0);

    cin >> n >> m >> w;
    a.resize(n+1);
    REP(i, 1, n) {
        cin >> a[i];
        a[i].insert(a[i].begin(), ' ');
    }
    string s;
    FOR(i, w) {
        cin >> s;
        dict.PB(s);
        reverse(ALL(s)), dict.PB(s);
    }

    REP(i, 1, n) REP(j, 1, m) {
        for (auto& word : dict) {
            if (word.size()<=i) {
                bool ok = true;
                FOR(k, word.size())
                    if (word[k]!=a[i-k][j]) {
                        ok = false;
                        break;
                    }
                if (ok) up[i][j][word.size()] += word.size();
            }
            if (word.size()<=j) {
                bool ok = true;
                FOR(k, word.size())
                    if (word[k]!=a[i][j-k]) {
                        ok = false;
                        break;
                    }
                if (ok) lf[i][j][word.size()] += word.size();
            }
        }
        
        REP(k, 1, max(n, m)) {
            lf[i][j][k] += lf[i][j][k-1];
            up[i][j][k] += up[i][j][k-1];
        }
    }
}

int gcd(int a, int b) {
    return b==0 ? a : gcd(b, a%b);
}

void simpl(PII& p) {
    int g = gcd(p.first, p.second);
    p.first /= g, p.second /= g;
}

int cmp(PII& now, PII& ans) {
    simpl(now);
    if ((LL)now.first*ans.second>(LL)now.second*ans.first)
        return 1;
    else if ((LL)now.first*ans.second==(LL)now.second*ans.first)
        return 0;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    REP(t, 1, T) {
        cout << "Case #" << t << ": ";
        init(); 
        PII ans = {0, 1};
        int rep = 0;
        REP(r1, 1, n) {
            VI col(m+1);
            VVI row(m+1, VI(m+1));

            REP(r2, r1, n) {
                REP(i, 1, m) col[i] += up[r2][i][r2-r1+1];
                REP(l, 1, m) {
                    int tot = 0;
                    REP(r, l, m){
                        tot += col[r];
                        row[l][r] += lf[r2][r][r-l+1];
                        tot += row[l][r];
                        int dv = r2-r1+1 + r-l+1;
                        PII now = {tot, dv};
                        int cp = cmp(now, ans);
                        if (cp==1) 
                            ans = now, rep = 1;
                        else if (cp==0)
                            ++rep;
                    }
                }
            }
        }
        cout << ans.first << '/' << ans.second << ' ' << rep << '\n';
    }
    return 0;
}
