#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXNODE = 405;
const int SIGMA_SIZE = 62;

struct AutoMac {

    int ch[MAXNODE][SIGMA_SIZE];
    int val[MAXNODE];
    int next[MAXNODE];
    int sz;

    double dp[MAXNODE][105];
    double p[SIGMA_SIZE];
    bool vis[MAXNODE][105];

    void init() {
	sz = 1;
	memset(ch[0], 0, sizeof(ch[0]));
	val[0] = 0;

	memset(p, 0, sizeof(p));
	memset(vis, false, sizeof(vis));
    }

    int idx(char c) {
	if (c >= 'a' && c <= 'z') return c - 'a';
	if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
	if (c >= '0' && c <= '9') return c - '0' + 52;
    }

    void insert(char *s) {
	int n = strlen(s);
	int u = 0;
	for (int i = 0; i < n; i++) {
	    int c = idx(s[i]);
	    if (!ch[u][c]) {
		val[sz] = 0;
		memset(ch[sz], 0, sizeof(ch[sz]));
		ch[u][c] = sz++;
	    }
	    u = ch[u][c];
	}
	val[u] = 1;
    }

    void getnext() {
	queue<int> Q;
	next[0] = 0;
	for (int c = 0; c < SIGMA_SIZE; c++) {
	    int u = ch[0][c];
	    if (u) {next[u] = 0; Q.push(u);}
	}
	while (!Q.empty()) {
	    int r = Q.front(); Q.pop();
	    for (int c = 0; c < SIGMA_SIZE; c++) {
		int u = ch[r][c];
		if (!u) {
		    ch[r][c] = ch[next[r]][c];
		    continue;
		}
		Q.push(u);
		int v = next[r];
		while (v && !ch[v][c]) v = next[v];
		next[u] = ch[v][c];
		val[u] |= val[next[u]];
	    }
	}
    }

    double solve(int u, int L) {
	if (vis[u][L]) return dp[u][L];
	vis[u][L] = true;
	if (!L) return dp[u][L] = 1;
	dp[u][L] = 0;
	for (int c = 0; c < SIGMA_SIZE; c++) {
	    if (val[ch[u][c]]) continue;
	    dp[u][L] += p[c] * solve(ch[u][c], L - 1);
	}
	return dp[u][L];
    }
};

AutoMac gao;

int t, n, L;
char str[25];

int main() {
	freopen("in.txt","r",stdin);
	//freopen("New.txt","w",stdout);
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	gao.init();
	scanf("%d", &n);
	while (n--) {
	    scanf("%s", str);
	    gao.insert(str);
	}
	gao.getnext();
	scanf("%d", &n);
	while (n--) {
	    scanf("%s", str);
	    scanf("%lf", &gao.p[gao.idx(str[0])]);
	}
	scanf("%d", &L);
	printf("Case #%d: %.6lf\n", ++cas, gao.solve(0, L));
    }
    return 0;
}
