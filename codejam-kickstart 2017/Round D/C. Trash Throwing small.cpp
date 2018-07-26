#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#define REP(i,a,b) for (int i=a; i<=b; ++i)

using namespace std;

double xi[21], yi[21];
int n;
double p, h;

void init() {
	cin >> n >> p >> h;
	REP(i, 1, n) {
		cin >> xi[i] >> yi[i];
		if (xi[i] > p/2)
			xi[i] = p - xi[i];
	}
}

inline double dis(double x1, double y1, double x2, double y2) {
	return pow(x1-x2, 2) + pow(y1-y2, 2);
}

bool safe(double a, double x, double y, double rad) {
	if (y>=rad) return true;
	double l = 0, r = p/2;
	double last_dis = min(dis(x,y,0,0), dis(x,y,r,a*r*(r-p)));
	while (r-l>=1e-5) {
		double d = r-l, u=l+d/3, v=l+2*d/3;
		double d1 = dis(x, y, u, a*u*(u-p));
		double d2 = dis(x, y, v, a*v*(v-p));
		double now_dis = min(d1, d2);
		if (fabs(now_dis-last_dis)<=1e-5) {
			l = u;
			break;
		}
		if (d1<d2)
			r = v;
		else if (d1>d2) 
			l = u;
		else 
			l = u, r = v; 
	}
	return dis(x, y, l, a*l*(l-p)) >= rad*rad;
}

bool ok(double r) {
	for (double t=0; t<=h-r; t+=h-r) {
		double a = -4*t/pow(p, 2);
		bool valid = true;
		REP(i, 1, n)
			if (!safe(a, xi[i], yi[i], r)) {
				valid = false;
				break;
			}
		if (valid) return true;
	}
	return false;
}

int main() {
	int T;
	cin >> T;

	REP(t, 1, T) {
		cout << "Case #" << t << ": ";
		init();

		double l=0, r=h;

		while (r-l>=1e-5) {
			double rad = (l+r) / 2;
			if (ok(rad))
				l = rad;
			else
				r = rad;
		}
		printf("%.6lf\n", l);
	}

	return 0;
} 