#include <vector>
#include <algorithm>
#include <iostream>
#define  F first
#define  S second

using namespace std;
using ll = long long;
using PII = pair<ll, ll>;

int n;
vector<PII> a;

vector<PII> init() {
	cin >> n;
	ll v, h, a, b, c, d, e, f, m;
	cin >> v >> h >> a >> b >> c >> d >> e >> f >> m;

	vector<PII> s;
	s.push_back({v, h});
	for (int i=1; i<n; ++i) {
		ll vi = (a*v + b*h + c) % m, hi = (d*v + e*h + f) % m;
		s.push_back({vi, hi});
		v = vi, h = hi;
	}
	sort(s.begin(), s.end());
	return s;
}

bool ok(const PII& a, const PII& b, const PII& c) {
	return !(a.F<b.F && b.F<c.F && min(a.S, c.S)<b.S && b.S<max(a.S, c.S));
}

int main() {
	int T;
	cin >> T;
	for (int t=1; t<=T; ++t) {
		a = init();

		ll ans = 0;
		for (int i=0; i<n; ++i)
			for (int j=i+1; j<n; ++j)
				for (int k=j+1; k<n; ++k) 
					if (ok(a[i], a[j], a[k]))
						++ans;


		cout << "Case #" << t << ": " << ans << '\n';


	}
	return 0;
}