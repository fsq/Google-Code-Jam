#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<string> dict;
int l, n, m, ri, seglen;

int vis[27][27];
char str[3001];
vector<int> seg;
vector<vector<int>> pre_seg;

void init() {
    cin >> l;
    dict = vector<string>(l);
    for (int i=0; i<l; ++i) cin >> dict[i];
    
    string _s1, _s2;
    long long n, a, b, c, d, x, y;
    cin >> _s1 >> _s2 >> n >> a >> b >> c >> d;
    char s1 = _s1[0], s2 = _s2[0];


    memset(vis, 0, sizeof(vis));
    vis[s1-'a'][s2-'a'] = 0;
    str[0] = x = s1, str[1] = y = s2;
    m = -1;
    for (int i=2; i<n; ++i) {
        int nx = (b*x + a*y + c) % d;
        char s3 = nx % 26+ 'a';
        // cout << s1 << s2 << s3 << endl;
        if (vis[s2-'a'][s3-'a']) {
            m = i-1;
            ri = vis[s2-'a'][s3-'a'];
            break;
        }
        vis[s2-'a'][s3-'a'] = i-1;
        str[i] = s3;
        s1 = s2;
        s2 = s3;
        x = y;
        y = nx;
    }
    if (m==-1) {
        m = n;
        ri = INT_MAX;
    } 
    else {
        seg = vector<int>(26);
        pre_seg.clear();
        for (int i=ri; i<m; ++i) {
            ++seg[str[i]-'a'];
            vector<int> nxt = pre_seg.empty() ? vector<int>(26) : pre_seg.back();
            ++nxt[str[i]-'a'];
            pre_seg.push_back(move(nxt));
        }
        seglen = m - ri - 1;
    }
    for (int i=0; i<n; ++i)
        cout << str[i];
    cout <<endl;
}

vector<int> count(int l, int r) {
    vector<int> cnt(26);
    while (l<ri && l<=r) ++cnt[str[l++]-'a'];

    if (l > r) return cnt;

    int len = r - l + 1;
    int rep = len / seglen, remain = len % seglen;

    for (int i=0; i<26; ++i) {
        cnt[i] += rep * seg[i];
        if (remain) cnt[i] += pre_seg[remain-1][i];
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;

    for (int _t=1; _t<=T; ++_t) {

        init();
        
        int ans = 0;
        for (auto& s : dict) {
            vector<int> cnt(26);
            for (auto c : s) ++cnt[c-'a'];
            for (int i=0; i<m && i+s.size()<=n; ++i) 
                if (str[i]==s.front() && str[i+s.size()-1]==s.back() &&
                    count(i, i+s.size()-1)==cnt)
                    ++ans;
        }
            

        cout << "Case #" << _t << ": " << ans << '\n';
    }
    return 0;
}