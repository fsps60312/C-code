#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXLEN = 200005;
const int INF = 0x3f3f3f3f;

char str[55555];
int k, tdp, an, v[MAXLEN];

struct Ans {
	int len, pos;
	Ans() {}
	Ans(int len, int pos) {
		this->len = len;
		this->pos = pos;
	}
} ans[MAXLEN];

bool cmp(Ans a, Ans b) {
	if (a.len == b.len) return a.pos < b.pos;
	return a.len > b.len;
}

struct Suffix {

	int s[MAXLEN];
	int sa[MAXLEN], t[MAXLEN], t2[MAXLEN], c[MAXLEN], n;
	int rank[MAXLEN], height[MAXLEN];

	void build_sa(int m) {
		n++;
		int i, *x = t, *y = t2;
		for (i = 0; i < m; i++) c[i] = 0;
		for (i = 0; i < n; i++) c[x[i] = s[i]]++;
		for (i = 1; i < m; i++) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
		for (int k = 1; k <= n; k <<= 1) {
			int p = 0;
			for (i = n - k; i < n; i++) y[p++] = i;
			for (i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
			for (i = 0; i < m; i++) c[i] = 0;
			for (i = 0; i < n; i++) c[x[y[i]]]++;
			for (i = 0; i < m; i++) c[i] += c[i - 1];
			for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1; x[sa[0]] = 0;
			for (i = 1; i < n; i++)
				x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
			if (p >= n) break;
			m = p;
		}
		n--;
	}

	void getHeight() {
		int i, j, k = 0;
		for (i = 1; i <= n; i++) rank[sa[i]] = i;
		for (i = 0; i < n; i++) {
			if (k) k--;
			int j = sa[rank[i] - 1];
			while (s[i + k] == s[j + k]) k++;
			height[rank[i]] = k;
		}
	}

	void init() {
		tdp = 0; n = 0; an = 0;
		gets(str);
		while (gets(str)) {
			if (strcmp(str, "END TDP CODEBASE") == 0) break;
			int len = strlen(str);
			str[len] = '\n';
			for (int i = 0; i <= len; i++)
				s[n++] = str[i];
		}
		tdp = n;
		s[n++] = 260;
		gets(str);
		while (gets(str)) {
			if (strcmp(str, "END JCN CODEBASE") == 0) break;
			int len = strlen(str);
			str[len] = '\n';
			for (int i = 0; i <= len; i++)
				s[n++] = str[i];
		}
		s[n] = 0;
	}

	void solve() {
		init();
		build_sa(261);
		getHeight();
		memset(v, 0, sizeof(v));
		int Min = -1;
		for (int i = 1; i <= n; i++) {
			if (sa[i] < tdp) Min = INF;
			else if (sa[i] > tdp) {
				if (Min == -1) continue;
				Min = min(height[i], Min);
				v[sa[i] - tdp - 1] = max(Min, v[sa[i] - tdp - 1]);
			}
		}
		Min = -1;
		for (int i = n; i >= 1; i--) {
			if (sa[i] < tdp) Min = INF;
			else if (sa[i] > tdp) {
				if (Min == -1) continue;
				Min = min(height[i + 1], Min);
				v[sa[i] - tdp - 1] = max(Min, v[sa[i] - tdp - 1]);
			}
		}
		int r = -1;
		for (int i = 0; i < n - tdp; i++) {
			if (i + v[i] <= r) continue;
			if (v[i] == 0) continue;
			ans[an++] = Ans(v[i], i);
			r = i + v[i];
		}
		sort(ans, ans + an, cmp);
		for (int i = 0; i < min(an, k); i++) {
			printf("INFRINGING SEGMENT %d LENGTH %d POSITION %d\n", i + 1, ans[i].len, ans[i].pos);
			for (int j = ans[i].pos + tdp + 1; j < ans[i].pos + tdp + 1 + ans[i].len; j++)
				printf("%c", s[j]);
			printf("\n");
		}
	}

} gao;

int main() {
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	int bo = 0;
	int cas = 0;
	while (~scanf("%d%*c", &k) && k) {
		if (bo) printf("\n");
		else bo = 1;
		printf("CASE %d\n", ++cas);
		gao.solve();
	}
	return 0;
}
