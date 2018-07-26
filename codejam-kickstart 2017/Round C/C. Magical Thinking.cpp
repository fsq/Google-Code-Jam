#include <vector>
#include <algorithm>
#include <iostream>
#define REP(i,a,b) for (int i=a; i<=b; ++i)
#define MEMSET(a,v) memset(a, v, sizeof(a))

using namespace std;

int n, q, s1, s2;
int a[103], b[103], c[103];

int solve1() {
	int f[q+2][q+2];
	MEMSET(f, 0x80);
	f[0][0] = 0;
	REP(i, 1, q) 
		REP(j, 0, min(s1, i)) { 
			if (j>0) f[i][j] = f[i-1][j-1] + (a[i]==c[i]);
			f[i][j] = max(f[i][j], f[i-1][j] + (a[i]!=c[i]));
		}
	return f[q][s1];
}

int solve2() {
	int f[q+2][q+2][q+2];
	MEMSET(f, 0x80);
	f[0][0][0] = 0;
	REP(i, 1, q)
		REP(j, 0, min(s1, i))
			REP(k, 0, min(s2, i)) {
				if (a[i]==b[i]) {
					if (j>0 && k>0) f[i][j][k] = max(f[i][j][k], f[i-1][j-1][k-1]+(c[i]==a[i]));
					f[i][j][k] = max(f[i][j][k], f[i-1][j][k]+(c[i]!=a[i]));
				} else {
					if (j>0) 
						f[i][j][k] = max(f[i][j][k], f[i-1][j-1][k]+(c[i]==a[i]));
					if (k>0)
						f[i][j][k] = max(f[i][j][k], f[i-1][j][k-1]+(c[i]==b[i]));
				}
				// printf("f[%d][%d][%d]=%d\n", i,j,k,f[i][j][k]);
			}
	return f[q][s1][s2];
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	REP(t, 1, T) {
		cout << "Case #" << t << ": ";
		cin >> n >> q;
		if (n==1) {
			string s;
			cin >> s; REP(i, 1, q) a[i] = s[i-1];
			cin >> s; REP(i, 1, q) c[i] = s[i-1];
			cin >> s1;

			cout << solve1() << '\n';
		} else {
			string s;
			cin >> s; REP(i, 1, q) a[i] = s[i-1];
			cin >> s; REP(i, 1, q) b[i] = s[i-1];
			cin >> s; REP(i, 1, q) c[i] = s[i-1];
			cin >> s1 >> s2;
			cout << solve2() << '\n';
		}

	}

	return 0;
}