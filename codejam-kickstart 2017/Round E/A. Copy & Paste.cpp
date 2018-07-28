#include "/Users/fsq/stdc++.h"

using namespace std;

int f[103];

int dp(const string& s, int i) {
    if (i==-1) return 0;
    if (i==0) return 1;
    if (f[i]) return f[i];
    int& ans = f[i];
    ans = dp(s, i-1)+1;
    for (int len=2; len<=i+1; ++len) {
        for (int j=i-len+1, cnt=1, k=j; j>=0; ) {
            if (s.substr(0, k).find(s.substr(j, len))!=string::npos) 
                ans = min(ans, dp(s, k-1)+1+cnt);
            else 
                break;
            
            auto p = s.substr(0, k).rfind(s.substr(j, len));
            if (p!=string::npos) {
                cnt += k - p - len + 1;
                k = p;
            } else break;
        }
    }
    return ans;
}

int main() {
    // ios::sync_with_stdio(false);
    int T;
    cin >> T;

    string s;
    for (int t=1; t<=T; ++t) {
        cin >> s;
        MEMSET(f, 0);
        cout << "Case #" << t << ": " << dp(s, s.size()-1) << '\n';
    }

    return 0;
}