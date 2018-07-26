// TODO

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <numeric>
#define PB push_back
#define REP(i,a,b) for (int i=a; i<=b; ++i)

using namespace std;
using ll = long long;

ll n, k;
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
		for (auto it=st.begin(); it!=st.end() && *it<=x-mid; ++it) ++ret;
		st.insert(x);
	}
	return ret;
}

// get cap biggest subsum of a
void get_big(vector<ll>& a, vector<ll>& big, ll cap) {
	vector<ll> s(a.size());
	partial_sum(a.begin(), a.end(), s.begin());
	ll l = -1e8, r = 1e8;
	while (l < r) {
		ll mid = (l + r) >> 1;
		ll cnt = count(s, mid);
		// printf("%d %d %d %d\n", l, r, mid, cnt);
		if (cnt<cap)
			r = mid - 1;
		else if (l+1==r) {
			if (count(s, l+1)>=cap) ++l;
			break;
		} else 
			l = mid;
	}
	multiset<ll> st = {0};
	for (auto x : s) {
		for (auto it=st.begin(); it!=st.end() && *it<x-l; ++it) big.PB(x - *it);
		st.insert(x);
	}
	big.insert(big.end(), cap-big.size(), l);
}

void get_big_small(vector<ll>& a, vector<ll>& big, vector<ll>& sml) {
	big.clear(), sml.clear();
	if (a.empty()) return;
	ll tot = a.size() * (a.size()+1) / 2;
	if ((k<<1) > tot) {
		get_big(a, big, tot/2);
		for (auto& x : a ) x = -x;
		get_big(a, sml, tot-tot/2);
	} else {
		get_big(a, big, k);
		for (auto& x : a ) x = -x;
		get_big(a, sml, k);
	}
	// if (big.size()+sml.size() != min(tot, k*2)) cout << 123 << endl;
	for (auto& x : sml) x = -x;
}

ll count2(vector<ll>& a, vector<ll>& b, ll mid) {
	ll cnt = 0;
	for (auto x : a) {
		if (x==0) {
			cnt += mid<=0 ? b.size() : 0;
		} else if (x<0) {
			ll lo = mid % x ? mid/x-1 : mid/x;
			cnt += upper_bound(b.begin(), b.end(), lo) - b.begin();
		} else {
			ll up = mid % x ? mid/x+1 : mid/x;
			cnt += b.end() - lower_bound(b.begin(), b.end(), up);
		}
	}
	return cnt;
}

// get k biggest product of ai*bj
vector<ll> get_big_prod(vector<ll>& a, vector<ll>& b, ll k) {
	if (a.empty() || b.empty()) return {};
	k = min<ll>(k, a.size()*b.size());
	ll l = -1e16, r = 1e16;
	sort(b.begin(), b.end());
	while (l<r) {
		ll mid = (l+r) >> 1;
		ll cnt = count2(a, b, mid);
		// printf("%lld %lld %lld %lld\n", l, r, mid, cnt);
		if (cnt<k) 
			r = mid - 1;
		else if (l+1==r) {
			if (count2(a, b, l+1)>=k) ++l;
			break;
		} else 
			l = mid;
	}
	vector<ll> ret;
	for (auto x : a)
		if (x>=0) 
			for (int i=b.size()-1; i>=0 && x*b[i]>=l+1; --i) ret.PB(x*b[i]);
		else 
			for (int i=0; i<b.size() && x*b[i]>=l+1; ++i) ret.PB(x*b[i]);
	ret.insert(ret.end(), k-ret.size(), l);
	return ret;
}

ll getk(vector<ll>& a, vector<ll> &b) {
	int now = 0, i=0, j=0;
	ll ret;
	while (now<k) {
		++now;
		if (i<a.size() && (j==b.size() || a[i]>b[j])) 
			ret = a[i++];
		else 
			ret = b[j++];
	}
	return ret;
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
		// for (auto x : abig) cout << x << ' '; cout << endl;
		// for (auto x : asml) cout << x << ' '; cout << endl;
		// for (auto x : bbig) cout << x << ' '; cout << endl;
		// for (auto x : bsml) cout << x << ' '; cout << endl;
		auto bg = get_big_prod(abig, bbig, k);
		// for (auto x : bg) cout << x << ' '; cout << endl;
		auto sm = get_big_prod(asml, bsml, k);
		// for (auto x : sm) cout << x << ' '; cout << endl;
		cout << getk(bg, sm) << '\n';
	}

	return 0;
} 