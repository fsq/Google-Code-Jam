#include "/Users/fsq/stdc++.h"
using namespace std;

int n;
vector<int> e[1003];
bool inside[1003];
int dis[1003];

void clear() { 
    REP(i, 1, 1000) e[i].clear(); 
    MEMSET(inside, false);
}

bool dfs(int x, vector<int>& vis, vector<int>& path, int pre) {
    vis[x] = 1;
    path.PB(x);
    FOREACH(y, e[x])
        if (!vis[y]) {
            if (dfs(y, vis, path, x)) return true;;
        } else if (vis[y] && y!=pre) {
            while (path.back()!=y) {
                inside[path.back()] = true;
                path.pop_back();
            }
            inside[y] = true;
            return true;
        }
    path.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) {
        clear();
        cin >> n;
        for (int x,y,i=0; i<n; ++i) {
            cin >> x >> y;
            e[x].push_back(y);
            e[y].push_back(x);
        }

        vector<int> vis(n+1);
        vector<int> path;
        dfs(1, vis, path, 0);

        cout << "Case #" << t << ": ";
        REP(i, 1, n) 
            if (inside[i]) {
                cout << "0 ";
            } else {
                int dis;
                bool found = false;
                fill(ALL(vis), 0);
                queue<PII> q;
                q.push({i, 0});
                vis[i] = 1;
                while (true) {
                    auto p = q.front(); q.pop();
                    for (auto y : e[p.first])
                        if (!vis[y]) {
                            if (inside[y]) {
                                found = true;
                                dis = p.second + 1;
                                break;
                            }
                            q.push({y, p.second+1});
                            vis[y] = true;
                        }
                    if (found) break;
                }

                cout << dis << ' ';
            }
        
        cout << '\n';

    }
    return 0;
}