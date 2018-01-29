#include <iostream>
#include <unordered_set>

using namespace std;

// https://code.google.com/codejam/contest/6254486/dashboard
// only '0' gives INSOMNIA

int main() {
    int t;
    long long n;
    cin >> t;
    for (int count=1; count<=t; ++count) {
        cin >> n;
        if (n==0) 
            cout << "Case #"<<count<<": INSOMNIA"<<endl;
        else {
            unordered_set<int> seen;
            int times = 1;
            long long ori = n;
            do  {
                for (int i=n; i>0; i/=10)
                    seen.insert(i%10);
                if (seen.size()==10) break;
                ++times;
                n = times * ori;
            } while(true);
            cout << "Case #"<<count<<": "<<n<<endl;
        }
    }
    return 0;
}