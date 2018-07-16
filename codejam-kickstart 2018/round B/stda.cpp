#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using ll = long long;
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    int ans = 0;
    for (int i=x; i<=y; ++i) 
        if (!(i%9==0 || to_string(i).find('9')!=string::npos))
            ++ans;
    cout << ans << endl;
    return 0;
}