#include "/Users/fsq/stdc++.h"
using namespace std;

int n;
char a[103][103];

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;

    for (int t=1; t<=T; ++t) {
        cin >> n;
        cout << "Case #" << t << ": ";
        vector<vector<int>> rows(n+1), cols(n+1);

        REP(i, 1, n) {
            string s;
            cin >> s;
            REP(j, 1, n) {
                a[i][j] = s[j-1];
                if (a[i][j]=='X') 
                    rows[i].PB(j), cols[j].PB(i);
            }
        }

        bool ok = true;
        int cnt = 0;
        REP(i, 1, n)
            if (rows[i].size()==2) {
                cnt += 2;
                int c1=rows[i][0], c2=rows[i][1];
                if (!(cols[c1].size()==2 && cols[c2].size()==2 && 
                      ((cols[c1][0]==cols[c2][1] && cols[c1][1]==cols[c2][0]) ||
                       cols[c1]==cols[c2]))) {
                    ok = false;
                    break;
                }
            } else if (rows[i].size()==1) {
                ++cnt;
                if (!(cols[rows[i][0]].size()==1)) {
                    ok = false;
                    break;
                }
            } else {
                ok = false;
                break;
            }


        if (ok && cnt==(2*n-1))
            cout << "POSSIBLE\n";
        else 
            cout << "IMPOSSIBLE\n";
    }

    return 0;
}