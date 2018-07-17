#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;
using ll = long long;
using PII = pair<int,int>;

vector<vector<PII>> cl; // left(0-based) ones
int n, m, mx;
ll f[203][70000];
ll p;
const ll INF = 1e18 + 1;

void clear() {
	cl.clear();
	cin >> n >> m >> p;
	mx = 0;
	cl.resize(n+1);
	for (int a,b,c,i=0; i<m; ++i) {
		cin >> a >> b >> c;
		cl[b].push_back({b-a, c});
		mx = max(mx, b-a+1);
	}
}

void dp() {
	memset(f, 0, sizeof(f));
	for (int i=0; i<(1<<mx); ++i)
		if (all_of(cl[n].begin(), cl[n].end(), [=](const PII& p) {
			int c = 0;
			for (int j=0; j<=p.first; ++j) c += i>>j & 1;
			return c == p.second;
		})) 
			f[n][i] = 1;

	for (int i=n-1; i>=1; --i)
		for (int j=0; j<(1<<mx); ++j)
			if (all_of(cl[i].begin(), cl[i].end(), [=](const PII& p) {
				int c = 0;
				for (int k=0; k<=p.first; ++k) c += j>>k & 1;
				return c == p.second;
			}))
				f[i][j] = min(INF, f[i+1][(j & ((1<<(mx-1))-1)) << 1]
						+ f[i+1][(j & ((1<<(mx-1))-1)) << 1 | 1]);
}

int str2dec(string ans) {
	int r = 0;
	for (int j=1, i=ans.size()-1; i>=0 && i>=(int)ans.size()-mx; j<<=1, --i) {
		r += (ans[i]-'0') * j;
	}
	return r;
}

string solve() {
	string ans;
	for (int i=1; i<=n; ++i) {
		
		ll c = all_of(cl[i].begin(), cl[i].end(), [&](const PII& p){
				return count(ans.end()-p.first, ans.end(), '1')==p.second;
			}) ? f[i][str2dec(ans+"0")] : 0;
		if (c>=p)
			ans.push_back('0');
		else {
			ans.push_back('1');
			p -= c;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t=1; t<=T; ++t) {
		clear();
		dp();
		cout << "Case #" << t << ": " << solve() << '\n';
	}

	return 0;
}
