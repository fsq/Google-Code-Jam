#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#define PB push_back
#define REP(i,a,b) for (int i=a; i<=b; ++i)

using namespace std;
using ll = long long;

int n, k;
vector<ll> a, b, abig, asml, bbig, bsml;

void init() {
	ll x1, y1, c, d, e1, e2, f;
	cin >> n >> k >> x1 >> y1 >> c >> d >> e1 >> e2 >> f;

	a.clear(), b.clear();

	a.PB(x1), b.PB(y1);
	int r1 = 0, s1 = 0;
	REP(i, 2, n) {
		ll xn = (c*x1 + d*y1 + e1) % f;
		ll yn = (d*x1 + c*y1 + e2) % f;
		int rn = (c*r1 + d*s1 + e1) % 2;
		int sn = (d*r1 + c*s1 + e2) % 2;
		a.PB(rn ? -xn : xn);
		b.PB(sn ? -yn : yn);
		x1 = xn, y1 = yn, r1 = rn, s1 = sn;
	}
}

ll count(const vector<ll>& s, ll mid) {
	multiset<ll> st = {0};
	ll ret = 0;
	for (auto x : s) {
		for (auto it=st.begin(); it!=st.end() && *it<=x-l; ++it) ++ret;
		st.insert(x);
	}
	return ret;
}

// get k biggest subsum of a
void get_big(vector<ll>& a, vector<ll>& big) {
	vector<ll> s(a.size());
	partial_sum(a.begin(), a.end(), s.begin());
	ll l = -1e8, r = 1e8;
	while (l < r) {
		ll mid = (l + r) >> 1;
		ll cnt = count(s, mid);
		if (cnt<k)
			l = mid + 1;
		else 
			r = mid;
	}
	multiset<ll> st = {0};
	for (auto x : s) {
		for (auto it=st.begin(); it!=st.end() && *it<=x-l; ++it) big.PB(x - y);
		st.insert(x);
	}
}

void get_big_small(vector<ll>& a, vector<ll>& big, vector<ll>& sml) {
	big.clear(), sml.clear();
	get_big(a, big); 
	for (auto& x : a ) x = -x;
	get_big(a, sml);
	for (auto& x : sml) x = -x;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	REP(t, 1, T) {
		cout << "Case #" << t << ": ";
		init();
		get_big_small(a, abig, asml);
		get_big_small(b, bbig, bsml);
		
		
	}

	return 0;
} 