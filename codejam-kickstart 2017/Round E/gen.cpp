#include "/Users/fsq/stdc++.h"

using namespace std;

int main() {
    srand(time(NULL));
    cout << 1 << endl;
    string s;
    FOR(i, 20) s.push_back(rand()%26+'a');

    cout << s << endl;
    return 0;
}