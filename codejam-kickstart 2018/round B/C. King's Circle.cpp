#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
using ll = long long;
using PII = pair<ll, ll>;

ll n;
vector<int> ord;

vector<PII> init() {
	ll v, h, a, b, c, d, e, f, m;
	cin >> n >> v >> h >> a >> b >> c >> d >> e >> f >> m;

	vector<PII> s;
	s.push_back({v, h});
	ord.push_back(h);
	for (int i=1; i<n; ++i) {
		int vi = (a*v + b*h + c) % m, hi = (d*v + e*h + f) % m;
		s.push_back({vi, hi});
		ord.push_back(hi);
		v = vi, h = hi;
	}
	sort(s.begin(), s.end(), std::less<PII>());
	sort(ord.begin(), ord.end());
	ord.resize(unique(ord.begin(), ord.end()) - ord.begin());
	return s;
}

int get_pos(int y) {
	return lower_bound(ord.begin(), ord.end(), y) - ord.begin();
}

inline int lowbit(int i) { return i & -i; }

template<class T>
T query(const vector<T>& s, int i) {
	T tot = 0;
	for (++i; i>0; i-=lowbit(i)) tot += s[i];
	return tot;
}

void add(vector<ll>& s, int i, ll v) {
	for (++i; i<s.size(); i+=lowbit(i)) s[i]+=v;
}
void add(vector<int>& s, int i, int v) {
	for (++i; i<s.size(); i+=lowbit(i)) s[i]+=v;
}


int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t=1; t<=T; ++t) {
		auto grp = init();

		ll ans = 0, tot = 0, totru=0;
		vector<int> pre(ord.size()+1);
		vector<ll> ru(ord.size()+1), rd(ord.size()+1);

		for (int j,i=0; i<grp.size(); i=j) {
			vector<int> ins2ru, ins2rd, ps;
			for (j=i; j<grp.size() && grp[j].first==grp[i].first; ++j) {
				int y = grp[j].second, pos = get_pos(y);
				ps.push_back(pos);
				int rut = i - query(pre, pos);
				int rdt = query(pre, pos-1);
				ins2ru.push_back(rut);
				ins2rd.push_back(rdt);
				ll srut = totru - query(ru, pos);
				ll srdt = query(rd, pos-1);
				tot += srut + srdt;
			}

			for (int i=0; i<ins2ru.size(); ++i) {
				add(pre, ps[i], 1);
				add(ru,  ps[i], ins2ru[i]); totru += ins2ru[i];
				add(rd,  ps[i], ins2rd[i]);
			}
		}

		cout << "Case #" << t << ": " << (n*(n-1)*(n-2)/6-tot) << '\n';


	}
	return 0;
}