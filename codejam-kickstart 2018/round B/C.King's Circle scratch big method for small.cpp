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
	sort(s.begin(), s.end(), [](const PII& a, const PII& b) {
		return a.F > b.F;
	});
	return s;
}


int main() {
	int T;
	cin >> T;
	for (int t=1; t<=T; ++t) {
		a = init();

		ll ans = 0, tot = 0;

		vector<ll> ru(n), rd(n);
		for (int i=0; i<n; ++i) {
			ll rut = 0, rdt = 0;
			for (int j=0; j<i; ++j)
				if (a[j].F>a[i].F)
					if (a[j].S>a[i].S) {
						tot += ru[j];
						++rut;
					} else if (a[j].S<a[i].S) {
						tot += rd[j];
						++rdt;
					}
			ru[i] = rut, rd[i] = rdt;
		}

		cout << "Case #" << t << ": " << (n*(n-1)*(n-2)/6-tot) << '\n';


	}
	return 0;
}