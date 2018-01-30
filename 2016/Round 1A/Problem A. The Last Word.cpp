#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main() {
    int num_cases;

    cin >> num_cases;

    for(int count_case=1; count_case<=num_cases; ++count_case) {
        string s, ret;
        cin >> s;

        for (auto c : s) 
            ret = max(ret+c, c+ret);

        cout << "Case #" << count_case << ": " << ret <<endl;
    }
    return 0;
}