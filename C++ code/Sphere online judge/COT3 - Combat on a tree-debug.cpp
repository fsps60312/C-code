//SPOJ11414; COT3; Game Theory + Trie Merging
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef long double ld;
#define pair(x, y) make_pair(x, y)
#define runtime() ((double)clock() / CLOCKS_PER_SEC)

#define N 100000
#define LOG 17
struct edge {
	int next, node;
} e[N << 1 | 1];
int head[N + 1], tot;

inline void addedge(int a, int b) {
	e[++tot].next = head[a];
	head[a] = tot, e[tot].node = b;
}

#define SIZE 2000000
struct Node {
	int l, r;
	bool full;
	int d;
} tree[SIZE + 1];
#define l(x) tree[x].l
#define r(x) tree[x].r
#define d(x) tree[x].d
#define full(x) tree[x].full
int root[N + 1], tcnt;
int n, col[N + 1], sg[N + 1], sum[N + 1], up[N + 1];
bool v[N + 1];

inline int newnode() {
	return ++tcnt;
}

inline void update(int x) {
	full(x) = full(l(x)) && full(r(x));
}

inline void push(int x) {
	if (d(x)) {
		if (l(x)) d(l(x)) ^= d(x) >> 1;
		if (r(x)) d(r(x)) ^= d(x) >> 1;
		if (d(x) & 1) swap(l(x), r(x));
		d(x) = 0;
	}
}

int merge(int l, int r) {
	if (!l || full(r)) return r;
	if (!r || full(l)) return l;
	push(l), push(r);
	int ret = newnode();
	l(ret) = merge(l(l), l(r));
	r(ret) = merge(r(l), r(r));
	update(ret);
	return ret;
}

inline int rev(int x) {
	int r = 0;
	for (int i = LOG; i > 0; --i)
		if (x >> i - 1 & 1) r += 1 << LOG - i;
	return r;
}

void insert(int x, int v, int p) {
	push(x);
	if (v >> p - 1 & 1) {
		if (!r(x)) r(x) = newnode();
		if (p != 1) insert(r(x), v, p - 1);
		else full(r(x)) = true;
	} else {
		if (!l(x)) l(x) = newnode();
		if (p != 1) insert(l(x), v, p - 1);
		else full(l(x)) = true;
	}
	update(x);
}

int mex(int x) {
	int r = 0;
	for (int i = LOG; x; --i) {
		push(x);
		if (full(l(x))) r += 1 << i - 1, x = r(x);
		else x = l(x);
	}
	return r;
}

void calc(int x) {
	v[x] = true;
	int xorsum = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int node = e[i].node;
		if (v[node]) continue;
		calc(node);
		v[node] = false;
		xorsum ^= sg[node];
	}
	for (int i = head[x]; i; i = e[i].next) {
		int node = e[i].node;
		if (v[node]) continue;
		d(root[node]) ^= rev(xorsum ^ sg[node]);
		root[x] = merge(root[x], root[node]);
	}
	if (!col[x]) insert(root[x], xorsum, LOG);
	sg[x] = mex(root[x]);
	sum[x] = xorsum;
}

int ans[N + 1], cnt;

void find(int x) {
	v[x] = true;
	if ((up[x] ^ sum[x]) == 0 && col[x] == 0) ans[++cnt] = x;
	for (int i = head[x]; i; i = e[i].next) {
		int node = e[i].node;
		if (v[node]) continue;
		up[node] = up[x] ^ sum[x] ^ sg[node];
		find(node);
	}
}
#include<cstring>
int main(int argc, char* argv[]) {
	freopen("in.txt", "r", stdin);
//	freopen("new.txt", "w", stdout);
	
	while(scanf("%d", &n)==1)
	{
		cnt=tcnt=tot=0;
		memset(e,0,sizeof(e));
		memset(head,0,sizeof(head));
		memset(tree,0,sizeof(tree));
		memset(root,0,sizeof(root));
		memset(sg,0,sizeof(sg));
		memset(col,0,sizeof(col));
		memset(sum,0,sizeof(sum));
		memset(up,0,sizeof(up));
		memset(v,0,sizeof(v));
		memset(ans,0,sizeof(ans));
		for (int i = 1; i <= n; ++i) scanf("%d", col + i);
		for (int i = 1; i < n; ++i) {
			static int x, y;
			scanf("%d%d", &x, &y);
			addedge(x, y), addedge(y, x);
		}
		for (int i = 1; i <= n; ++i) root[i] = newnode();
		calc(1);
		for (int i = 1; i <= n; ++i) v[i] = false;
		find(1);
		
		if (cnt == 0) printf("-1\n");
		else {
			sort(ans + 1, ans + cnt + 1);
			for (int i = 1; i <= cnt; ++i) printf("%d\n", ans[i]);
		}
		
	//	cerr << runtime() << endl;
	//	for (int i = 1; i <= n; ++i) printf("%d ", sg[i]);
		
	}
	return 0;
}

