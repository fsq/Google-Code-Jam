#include <vector>
#include <algorithm>
#include <iostream>
#define REP(i,a,b) for (int i=a; i<=b; ++i)

using namespace std;
using ll = long long;

int n;
ll s[2003], fq[2003], d[2003];
ll f[2003][2003];
ll ts, tf;

ll near(ll fr, int i) {
	if (s[i]>=fr)
		return s[i] + d[i];
	else {
		ll x = (fr-s[i]) / fq[i];
		if ((fr-s[i]) % fq[i]) ++x;
		return s[i] + x*fq[i] + d[i];
	}
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	REP(t, 1, T) {
		cout << "Case #" << t << ": ";
		cin >> n >> ts >> tf;
		REP(i, 1, n-1) cin >> s[i] >> fq[i] >> d[i];

		f[1][0] = 0;
		bool imp = false;
		REP(i, 2, n) {
			f[i][0] = near(f[i-1][0], i-1);
			if (f[i][0]>tf) {
				imp = true;
				break;
			}
			REP(j, 1, i-2)  
				f[i][j] = min(near(f[i-1][j], i-1), near(f[i-1][j-1]+ts, i-1));
			f[i][i-1] = near(f[i-1][i-2]+ts, i-1);
		}

		if (imp) 
			cout << "IMPOSSIBLE\n";
		else {
			int ans = -1;
			for (int i=n-1; i>=0; --i) 
				if (f[n][i]<=tf) {
					ans = i;
					break;
				}
			cout << (ans==-1 ? "IMPOSSIBLE" : to_string(ans)) << '\n';
		}

	}

	return 0;
} 