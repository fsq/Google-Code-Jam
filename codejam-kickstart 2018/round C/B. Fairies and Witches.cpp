#include "/Users/fsq/stdc++.h"
using namespace std;

int n, ans;
int a[17][17];

void dfs(int now, vector<int>& vis, int sum, int mx, int sz) {
    if (now==n+1) {
        if (sum-mx>mx && sz>2) ++ans;
    } else {
        dfs(now+1, vis, sum, mx, sz);
        if (!vis[now])
            for (int j=now+1; j<=n; ++j)
                if (a[now][j] && !vis[j]) {
                    vis[now] = vis[j] = true;
                    dfs(now+1, vis, sum+a[now][j], max(mx, a[now][j]), sz+1);
                    vis[now] = vis[j] = false;
                }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) {
        cin >> n;
        REP(i, 1, n) REP(j, 1, n) cin >> a[i][j];
        ans = 0;
        vector<int> vis(n+1);
        dfs(1, vis, 0, 0, 0);

        cout << "Case #" << t << ": " << ans << '\n';

    }
    return 0;
}