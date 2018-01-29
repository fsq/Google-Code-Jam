#include <iostream>
#include <string>
#include <vector>

using namespace std;

void flip(vector<int>& a, int l, int r) {
    --r;
    
    while (l<r) {
        a[l] ^= 1;
        a[r] ^= 1;
        swap(a[l++], a[r--]);
    }
    if (l==r) a[l] ^= 1;
}

int main() {
    int t;
    string init;
    cin >> t;
    for (int count=1; count<=t; ++count) {
        cin >> init;
        vector<int> a;
        for (auto c : init)
            a.push_back(c=='+' ? 1 : 0);
        while (!a.empty() && a.back()==1)
            a.pop_back();
        int ans = 0;
        while (!a.empty()) {
            int i=0;
            while (i<a.size() && a[i]==1) ++i;
            if (i>0) {
                flip(a, 0, i);
                ++ans;
            }
            flip(a, 0, a.size());
            ++ans;
            while (!a.empty() && a.back()==1)
                a.pop_back();
        }

        cout << "Case #"<<count<<": "<<ans<<endl;
    }
    return 0;
}