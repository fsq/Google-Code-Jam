#include "/Users/fsq/stdc++.h"

using namespace std;

string cipher(const string& t) {
    string s(t.size(), ' ');
    s[1] = t[0];
    for (int i=1; i+2<s.size(); i+=2) 
        s[i+2] = (t[i+1]+26-s[i]) % 26;

    s[s.size()-2] = t.back();
    for (int i=s.size()-2; i-2>=0; i-=2)
        s[i-2] = (t[i-1]+26-s[i]) % 26;

    for (auto& c : s) c += 'A';
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    string s;
    for (int t=1; t<=T; ++t) {
        cin >> s;
        for (auto& c : s) c-='A';
        cout << "Case #" 
        << t << ": ";
        if (s.size() & 1) {
            cout << "AMBIGUOUS\n";
        } else {
            cout << cipher(s) << '\n';
        }

    }

    return 0;
}