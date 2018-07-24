#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#define PB push_back
#define REP(i,a,b) for (int i=a; i<=b; ++i)

using namespace std;
using ll = long long;

int n, k;
vector<ll> a, b, apos, aneg, bpos, bneg;
ll azr, bzr;

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

void split(vector<ll>& a, vector<ll>& pos, vector<ll>& neg, ll& zero) {
	vector<ll> s;
	REP(i, 0, n-1) {
		ll acc = 0;
		REP(j, i, n-1) {
			acc += a[j];
			s.PB(acc);
		}
	}
	sort(s.begin(), s.end());
	pos.clear(), neg.clear(), zero = 0;
	
	int i = 0;
	while (i<s.size() && s[i]<0) neg.PB(s[i++]);
	while (i<s.size() && s[i]==0) ++zero, ++i;
	while (i<s.size()) pos.PB(s[i++]);

	reverse(pos.begin(), pos.end());
}

vector<ll> get(vector<ll>& a, vector<ll>& b) {
	if (a.empty() || b.empty()) return {};
	multiset<pair<ll,int>, std::greater<pair<ll,int>>> st;
	int n = a.size();
	vector<int> ptr(n);
	vector<ll> ret;
	REP(i, 0, n-1) {
		ptr[i] = 0;
		st.insert({a[i]*b[0], i});
	}

	while (ret.size()<k && st.size()) {
		auto pr = *st.begin();
		st.erase(st.begin());
		ret.PB(pr.first);
		int i = pr.second;
		if (ptr[i]<b.size()) {
			++ptr[i];
			st.insert({a[i]*b[ptr[i]], i});
		}
	}
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

vector<ll> gen(vector<ll>& a) {
	vector<ll> s;
	REP(i, 0, n-1) {
		ll acc = 0;
		REP(j, i, n-1) {
			acc += a[j];
			s.PB(acc);
		}
	}
	sort(s.begin(), s.end());
	return s;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	REP(t, 1, T) {
		cout << "Case #" << t << ": ";
		init();

		auto sa = gen(a), sb = gen(b);
		multiset<ll, greater<ll>> st;
		for (auto x : sa)
			for (auto y : sb) {
				st.insert(x*y);
				if (st.size()>k) st.erase(prev(st.end(), 1));
			}
		
		cout << *prev(st.end(), 1) << '\n';
	}

	return 0;
} 