#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

int len = 15, m = 10, p = 10;

string t2(int x) {
	string a;
	while (x) {
		a = string(1, (x&1) + '0') + a;
		x >>= 1;
	}
	return a;
}

int main() {
	srand(time(NULL));
	ofstream fout("a.in");
	

	fout << "1\n";
	fout << len << ' '<< m << ' '<< p << endl;

	int x = rand() % (1<<len);
	string s = t2(x);
	vector<vector<int>> cons;
	cout << s << endl;
	for (int i=0; i<m; ++i) {
		int x = rand()%len + 1, y = rand()%len + 1;
		if (x>y) swap(x, y);
		cons.push_back({x, y, (int)count(s.begin()+x-1, s.begin()+y, '1')});
		fout << x << ' ' << y << ' ' << cons.back()[2] << '\n';
	}

	fout.close();


	ofstream stdout("std.out");
	for (int r=0, i=0; i<(1<<len); ++i)  {
		string s = t2(i);
		if (s.size()<len) s = string(len-s.size(), '0') + s;
		if (all_of(cons.begin(), cons.end(), [=](vector<int>& a) {
			return count(s.begin()+a[0]-1, s.begin()+a[1], '1')==a[2];
		}) && ++r==p) {
			cout << i << ' ' << s << endl;
			stdout << s << endl;
			break;
		}
	}
	stdout.close();

	return 0;
}