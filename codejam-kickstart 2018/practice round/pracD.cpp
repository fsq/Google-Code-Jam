#include <vector>
#include <iostream>
#include <algorithm>

using ll = long long;
using namespace std;

int a[200007];
long long ps[200007], pps[200007];
int n, min_elem;

void init() {
	min_elem = 102;
	for (int i=1; i<=n; ++i) {
		cin >> a[i];
		ps[i] = ps[i-1] + a[i];
		pps[i] = pps[i-1] + ps[i];
		min_elem = min(min_elem, a[i]);
	}
}

inline ll g(int i, int j) { return ps[j] - ps[i-1]; }

inline ll row_sum(int r, int c) {
	return pps[c] - pps[r-1] - (c-r+1)*ps[r-1];
}

// count how many of n^2 <=x and sum of them
pair<ll, ll> count(int x) {
	ll sum=0, cnt=0;
	int i=n, j=n;
	while (i)
		if (g(i, j)>x)
			--j;
		else {
			cnt += j - i + 1;
			sum += row_sum(i, j);
			--i;
		}
	return {cnt, sum};
}

// rank, prefix
ll find(ll i) {
	if (i==0) return 0;

	int l = min_elem, r = ps[n];
	while (l<r) {
		int m = l + ((r-l)>>1);
		auto p = count(m);
		// printf("%d %lld %lld\n", m, p.first, p.second);
		if (p.first < i)
			l = m + 1;
		else 
			r = m;
	}
	auto res = count(l);
	if (res.first>i) res.second -= l*(res.first-i);
	return res.second;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int q,t=1; t<=T; ++t) {
		cout << "Case #" << t << ": \n";

		cin >> n >> q;
		init();
		
		ll l, r;
		// for (int i=1; i<=15; ++i) cout << find(i) << endl;
		// cout << find(3);
		while (q--) {
			cin >> l >> r;
			ll p1 = find(l-1), p2 = find(r);
			cout << p2 - p1<< '\n';
		}
	}
}
