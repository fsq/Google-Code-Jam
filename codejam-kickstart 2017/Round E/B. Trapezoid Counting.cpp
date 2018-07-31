#include <vector>
#include <algorithm>
#include <iostream>
#define REP(i,a,b) for (int i=a; i<=b; ++i)

using namespace std;

int n;
vector<int> a;
vector<long long> s;
vector<pair<int,long long>> l;

void init() {
	a.clear();
	cin >> n;
	a.resize(n);
	REP(i, 0, n-1) cin >> a[i];
	sort(a.begin(), a.end());
	l.clear();
	l.push_back({0, 0});
	for (auto x : a)
		if (x==l.back().first)
			++l.back().second;
		else 
			l.push_back({x, 1});

	s.clear();
	n = l.size()-1;
	s.resize(n+1);
	REP(i, 1, n)
		s[i] = s[i-1] + (l[i].second*(l[i].second-1)/2);
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	
	REP(t, 1, T) {
		cout << "Case #" << t << ": ";

		init();
		long long ans = 0;

		REP(i, 1, n) REP(j, i+1, n) {
			int u = l[i].first, d = l[j].first;
			int upper = (d - u) >> 1;
			auto it = upper_bound(l.begin()+1, l.end(), pair<int,long long>{upper, INT_MAX}) - l.begin();
			long long av = s.back() - s[it-1];

			
			if (it<=i) {
				av -= l[j].second*(l[j].second-1) / 2;
				av -= l[i].second*(l[i].second-1) / 2;
				ans += l[i].second*l[j].second*av;
				ans += (l[i].second-2)*(l[i].second-1)*l[i].second/6 * l[j].second;
				ans += (l[j].second-2)*(l[j].second-1)*l[j].second/6 * l[i].second;
			} else if (it<=j) {
				av -= l[j].second*(l[j].second-1) / 2;
				ans += l[i].second*l[j].second*av;
				ans += (l[j].second-2)*(l[j].second-1)*l[j].second/6 * l[i].second;
			} else {
				ans += l[i].second*l[j].second*av;
			}
		}
		cout << ans << '\n';
	}

	return 0;
} 