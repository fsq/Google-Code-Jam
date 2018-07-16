#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;
using ll = long long;
using PII = pair<int,int>;

int main() {
	ios::sync_with_stdio(false);
	int T, n, m;
	ll p;
	cin >> T;
	for (int t=1; t<=T; ++t) {
		cin >> n >> m >> p;
		string ans(n, ' ');
		for (int a,b,c,i=0; i<m; ++i) {
			cin >> a >> b >> c;
			ans[a-1] = c + '0';
		}
		--p;
		for (ll i=ans.size()-1, j=0; i>=0; --i)
			if (ans[i]==' ')
				ans[i] = (p >> min<int>(j,63) & 1) + '0', ++j; // !
		cout << "Case #" << t << ": " << ans << '\n';
	}

	return 0;
}
