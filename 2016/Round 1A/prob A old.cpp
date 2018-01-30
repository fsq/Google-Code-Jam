#include <iostream>
#include <string>
#include <vector>

using namespace std;

string get_max(string s) {
    if (s.empty()) return "";
    if (s.size()==1)
        return s;
    vector<int> count(26, 0);

    for (auto c : s) ++count[c-'A'];
    char max_letter = 0;
    for (max_letter='Z'; max_letter>='A'; --max_letter)
        if (count[max_letter-'A']>0)
            break;

    string ret(count[max_letter-'A'], max_letter);
    int i=0, pre=0;
    bool first = true;
    for (i=0; i<s.size(); ++i)
        if (s[i]==max_letter) 
            if (first) {
                ret += get_max(s.substr(0, i));
                pre = i;
                first = false;
            } else {
                ret += s.substr(pre+1, i-pre-1);
                pre = i;
            }
    ret += s.substr(pre+1);
    return ret;
}

int main() {
    int num_cases;

    cin >> num_cases;

    for(int count_case=1; count_case<=num_cases; ++count_case) {
        string s;
        cin >> s;
        cout << "Case #" << count_case << ": " << get_max(s) <<endl;
    }
    return 0;
}