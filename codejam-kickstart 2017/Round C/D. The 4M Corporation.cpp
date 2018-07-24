#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#define REP(i,a,b) for (int i=a; i<=b; ++i)

using namespace std;

#define ll long long

ll findOdd(ll min, ll max, ll mean, ll med) {
	if (mean*3==(min+max+med)) return 3;
	if (med+max<=2*mean) return INT_MAX;
	// ll x = std::max<ll>(2, ceil((double)(mean-min) / (med+max-2.0*mean)));

	for (int i=5; i<100000; i+=2) 
		if ((i/2*med+i/2*max+min)>=i*mean && (i/2*min+i/2*med+max)<=i*mean) return i;

	return INT_MAX;
	// return x*2+1;
}

ll findEven(ll min, ll max, ll mean, ll med) {
	if ((med+max)/2<=mean) return INT_MAX;
	ll x = std::max<ll>(2, ceil((double)(max-min) / ((double)(med+max)/2.0-mean)));
	// if (x&1) ++x;
	// if (x/2*med+max+(x/2-1)*min<=x*mean) return x;

	// return (x&1) ? x+1 : x;
	for (int i=4; i<100000; i+=2) 
		if ((i/2*med+min+(i/2-1)*max)>=i*mean && (i/2*med+max+(i/2-1)*min)<=i*mean) return i;
	
	return INT_MAX;
}

bool check(int min, int max, int mean, int med) {
	return min<=mean && mean<=max && min<=med && med<=max;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	REP(t, 1, T) {
		cout << "Case #" << t << ": ";
		ll min, max, mean, med;
		cin >> min >> max >> mean >> med;

		if (!check(min, max, mean, med)) {
			cout << "IMPOSSIBLE\n";
		} else if (min==max) {
			cout << "1\n";
	 	} else if (mean==(min+max)/2.0 && med==mean) {
	 		cout << "2\n";
	 	} else {

			ll odd = findOdd(min, max, mean, med);
			ll eve = findEven(min, max, mean, med);

			ll ans = std::min(odd, eve);
			cout << (ans==INT_MAX ? "IMPOSSIBLE" : to_string(ans)) << '\n';
		}

	}

	return 0;
}