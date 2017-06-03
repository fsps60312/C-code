#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define nfor(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
#define correct(x, y, n, m) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
#define all(a) (a).begin(), (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define mp(x, y) make_pair((x), (y))
#define x first
#define y second

using namespace std;

typedef long long li;
typedef double ld;
typedef pair<int, int> pt;

template<typename X> inline X abs(const X& a) { return a < 0? -a: a; }
template<typename X> inline X sqr(const X& a) { return a * a; }

template<typename A, typename B> inline ostream& operator<< (ostream& out, const pair<A, B>& p) { return out << "(" << p.x << ", " << p.y << ")"; }
template<typename T> inline ostream& operator<< (ostream& out, const vector<T>& a) { out << "["; forn(i, sz(a)) { if (i) out << ','; out << ' ' << a[i]; } return out << " ]"; } 
template<typename T> inline ostream& operator<< (ostream& out, const set<T>& a) { return out << vector<T>(all(a)); }

inline ld gett() { return ld(clock()) / CLOCKS_PER_SEC; }

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = 1e-9, PI = 3.1415926535897932384626433832795;

int n, k;
vector<int> a;

bool read() {
	if (!(cin >> n >> k)) return false;
	a.resize(n);
	forn(i, n) assert(scanf("%d", &a[i]) == 1);
	return true;
}

struct base {
	ld re, im;
	base() { }
	base(ld re, ld im): re(re), im(im) { }
	ld slen() const { return sqr(re) + sqr(im); }
	ld real() { return re; }
};

inline base conj(const base& a) { return base(a.re, -a.im); }
inline base operator+ (const base& a, const base& b) { return base(a.re + b.re, a.im + b.im); }
inline base operator- (const base& a, const base& b) { return base(a.re - b.re, a.im - b.im); }
inline base operator* (const base& a, const base& b) { return base(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re); }
inline base operator/ (const base& a, const ld& b) { return base(a.re / b, a.im / b); }
inline base operator/ (const base& a, const base& b) { return base(a.re * b.re + a.im * b.im, a.im * b.re - a.re * b.im) / b.slen(); }
inline base& operator/= (base& a, const ld& b) { a.re /= b, a.im /= b; return a; }

int reverse(int x, int logn) {
	int ans = 0;
	forn(i, logn) if (x & (1 << i)) ans |= 1 << (logn - 1 - i);
	return ans;
}

const int LOGN = 20, N = (1 << LOGN) + 3;
void fft(base a[N], int n, bool inv) {
	static base vv[LOGN][N];
	static bool prepared = false;
	if (!prepared) {
		prepared = true;
		forn(i, LOGN) {
			ld ang = 2 * PI / (1 << (i + 1));
			forn(j, 1 << i) vv[i][j] = base(cos(ang * j), sin(ang * j));
		}
	}
	int logn = 0; while ((1 << logn) < n) logn++;
	forn(i, n) {
		int ni = reverse(i, logn);
		if (i < ni) swap(a[i], a[ni]);
	}
	for (int i = 0; (1 << i) < n; i++)
		for (int j = 0; j < n; j += (1 << (i + 1)))
			for (int k = j; k < j + (1 << i); k++) {
				base cur = inv ? conj(vv[i][k - j]) : vv[i][k - j];
				base l = a[k], r = cur * a[k + (1 << i)];
				a[k] = l + r;
				a[k + (1 << i)] = l - r;
			}
	if (inv) forn(i, n) a[i] /= ld(n);
}

void mul(int a[N], int b[N], int ans[N]) {
	static base fp[N], p1[N], p2[N];
	int n = 1 << LOGN, m = 1 << LOGN;
	while (n && !a[n - 1]) n--;
	while (m && !b[m - 1]) m--;
	int cnt = n + m;
	while (cnt & (cnt - 1)) cnt++;
	if (cnt > (1 << LOGN)) return;
	
	forn(i, cnt) fp[i] = base(a[i], b[i]);
	fft(fp, cnt, false);
	forn(i, cnt) {
		p1[i] = (fp[i] + conj(fp[(cnt - i) % cnt])) / base(2, 0);
		p2[i] = (fp[i] - conj(fp[(cnt - i) % cnt])) / base(0, 2);
	}
	forn(i, cnt) fp[i] = p1[i] * p2[i];
	fft(fp, cnt, true);

	forn(i, cnt) ans[i] = int(fp[i].real() + 0.5),printf("v=(%.9f,%.9f)\n",(double)fp[i].real(),(double)fp[i].im);
}

void mul(int* a, int* b) {
	forn(i, 1 << LOGN) {
		a[i] = !!a[i];
		b[i] = !!b[i];
	}
	mul(a, b, a);
}

void binPow(int* a, int b) {
	static int ans[N];
	forn(i, 1 << LOGN) ans[i] = !i;
	while (b) {
		if (b & 1) mul(ans, a);
		mul(a, a);
		b >>= 1;
	}
	forn(i, 1 << LOGN) a[i] = ans[i];
}

void solve() {
	static int ans[N];
	memset(ans, 0, sizeof(ans));
	forn(i, sz(a)) ans[a[i]] = 1;

	binPow(ans, k);

	bool f = true;
	forn(i, 1 << LOGN)
		if (ans[i]) {
			if (f) f = false;
			else putchar(' ');
			printf("%d", i);
		}
	puts("");
}

int main() {
#ifdef SU1
    //assert(freopen("output.txt", "wt", stdout));
#endif
    
    assert(freopen("in.txt", "r", stdin));
    cout << setprecision(10) << fixed;
    cerr << setprecision(5) << fixed;

    while (read()) {
		ld stime = gett();
		solve();
		cerr << "Time: " << gett() - stime << endl;
		//break;
	}
	
    return 0;
}

