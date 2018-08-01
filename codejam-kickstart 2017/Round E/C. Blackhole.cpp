#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>
#define REP(i,a,b) for (int i=(a); i<=(b); ++i)
#define EPS 1e-9

using namespace std;

class Ball {
public:
	Ball(){}
	Ball(double _x, double _y, double _z):x(_x),y(_y),z(_z) {}
	double x, y, z;
	double length() {
		return sqrt(x*x + y*y + z*z);
	}
	double length2() {
		return x*x + y*y + z*z;
	}
};

double cross(Ball& a, Ball& b) {
	Ball ball(a.y*b.z - a.z*b.y, a.x*b.z - a.z*b.x, a.x*b.y - a.y*b.x);
	return ball.length();
}

double dot(Ball& a, Ball& b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline bool eq0(double x) { return fabs(x)<EPS; }

inline bool bg0(double x) { return x>EPS; }

inline double min3(double a, double b, double c) {
	return min(a, min(b, c));
}

bool ok(double a, double b, double c, double r) {
	double cs = (a*a + b*b - c*c) / (2*a*b);
	double c1 = (8*r*r-a*a) / (2*a*r), s1 = sqrt(1-c1*c1);
	double c2 = (8*r*r-b*b) / (2*b*r), s2 = sqrt(1-c2*c2);
	double c12 = c1*c2 - s1*s2;
	return bg0(cs - c12);
}

double solve(double a, double b, double c) {
	double lo=b/4, hi=b/3;
	while (hi-lo>=1e-7) {
		double r = (hi+lo) / 2;
		if (ok(a,b,c,r))
			hi = r;
		else 
			lo = r;
	}
	return (hi+lo)/2;
}


int main() {
	int T;
	cin >> T;
			cout.precision(8);

	REP(t, 1, T) {
		cout << "Case #" << t << ": ";
		vector<Ball> a(3);
		REP(i, 0, 2) cin >> a[i].x >> a[i].y >> a[i].z;

		REP(i, 1, 2) {
			a[i].x -= a[0].x;
			a[i].y -= a[0].y;
			a[i].z -= a[0].z;
		}

		if (eq0(cross(a[1], a[2]))) {
			if (bg0(dot(a[1], a[2]))) {
				double len = max(a[1].length(), a[2].length());
				cout << len/6 << '\n';
			} else {
				double len = a[1].length() + a[2].length();
				cout << len/6 << '\n';
			}
		} else {	

			Ball A(a[1].length(), 0, 0);

			double dt = dot(a[2], a[1])/a[1].length();
			Ball B(dt, sqrt(a[2].length2() - dt*dt), 0);
			vector<double> lens = {A.length(), B.length(), Ball(A.x-B.x, A.y-B.y, A.z-B.z).length()};
			sort(lens.begin(), lens.end());
			double ans = solve(lens[0], lens[1], lens[2]);
			cout << fixed << ans << '\n';
		}	
	}

	return 0;
}