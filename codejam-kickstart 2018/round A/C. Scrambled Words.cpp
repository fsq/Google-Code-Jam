#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <cmath>

using namespace std;

vector<string> dict;
long long n;

char str[1000007];
unordered_map<int, map<vector<int>, int>> lens;
vector<vector<int>> pre;

void init() {
    pre.clear();
    lens.clear();
    int l;
    cin >> l;
    dict = vector<string>(l);
    for (int i=0; i<l; ++i) cin >> dict[i];
    
    string _s1, _s2;
    long long a, b, c, d, x, y;
    cin >> _s1 >> _s2 >> n >> a >> b >> c >> d;
    char s1 = _s1[0], s2 = _s2[0];


    str[0] = x = s1, str[1] = y = s2;
    for (int i=2; i<n; ++i) {
        int nx = (b*x + a*y + c) % d;
        char s3 = nx % 26+ 'a';
        str[i] = s3;
        s1 = s2, s2 = s3;
        x = y, y = nx;
    }
    for (int i=0; i<n; ++i) {
        vector<int> nxt = pre.empty() ? vector<int>(26) : pre.back();
        ++nxt[str[i]-'a'];
        pre.push_back(move(nxt));
    }
}

vector<int> count(const string& s) {
    vector<int> a(28);
    a[0] = s.front() - 'a'; a[1] = s.back() - 'a';
    for (auto c : s) ++a[c-'a'+2];
    return a;
}

void build() {
    for (auto& s : dict) ++lens[s.size()][count(s)];
}


int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;

    for (int _t=1; _t<=T; ++_t) {

        init();
        build();
        
        int ans = 0;
        for (auto &len_grp : lens) {
            int len = len_grp.first;
            auto map = len_grp.second;
            for (int r,l=0; l+len<=n; ++l) {
                r = l + len - 1;
                vector<int> code(28);
                for (int i=0; i<26; ++i)
                    code[i+2] = pre[r][i] - (l==0 ? 0 : pre[l-1][i]);
                code[0] = str[l]-'a', code[1] = str[r]-'a';
                if (map.find(code)!=map.end()) {
                    ans += map[code];
                    map.erase(code);
                }
            }
        }
        
        cout << "Case #" << _t << ": " << ans << '\n';
    }
    return 0;
}