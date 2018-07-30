#include "/Users/fsq/stdc++.h"

int r,c,w;
vector<string> a;
vector<string> words;
vector<vector<int>> s;

void init() {
    cin >> r >> c >> w;
    a.clear();
    a.resize(r+1);
    REP(i, 1, r) {
        cin >> a[i];
        a[i].insert(a[i].begin(), ' ');
    }
    words.clear();
    words.resize(w+1);
    REP(i, 1, w) {
        cin >> words[i];
        // cout << words[i] << endl;
    }

    s = VVI(r+1, VI(c+1, 0));
    REP(i, 1, r) REP(j, 1, c)
        if (find(words.begin(), words.end(), string(1, a[i][j]))!=words.end()) 
            ++s[i][j];

    REP(i, 1, r) REP(j, 1, c) {
        s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
        // printf("s[%d][%d]=%d\n", i, j, s[i][j]);
    }
}

int gcd(int a, int b) {
    return b==0 ? a : gcd(b, a%b);
}

void simpl(int& a, int &b) {
    if (a==0) 
        b = 1;
    else {
        int g = gcd(a, b);
        a /= g, b /= g;
    }
}

int cmp(int& a, int& b, int x, int y) {
    // printf("%d %d %d %d\n", a, b, x, y);
    simpl(a, b);
    // printf("%d %d %d %d\n", a, b, x, y);
    if (a*y==b*x) return 0;
    if (a*y>b*x) return 1;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    int numCases;
    cin >> numCases;
    for (int cases=1; cases<=numCases; ++cases) {
        cout << "Case #" << cases << ": ";        
        init();
        int p=0, q=1, rep=0;
        REP(x, 1, r) REP(y, 1, c) {
            REP(c, 1, x) REP(d, 1, y) {
                int cnt = 4*(s[x][y] - s[x][d-1] - s[c-1][y] + s[c-1][d-1]);
                int wd = x-d+1, ht = y-c+1;
                int a = cnt, b = wd+ht;
                int cp = cmp(a, b, p, q);
                // printf("(%d,%d) (%d,%d) %d %d %d \n", c, d, x, y, a, b, cnt);
                if (cp==1) {
                    rep = 1;
                    p = a, q = b;
                } else if (cp==0)
                    ++rep;
            }
        }
        cout << p << '/' << q << ' ' << rep << '\n';
    }
    return 0;
}
