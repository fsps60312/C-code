#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 5010;
const int inf = 1e9;
int n, m, k, S, T;
struct Edges {
	int v, c, next;
	Edges(int v, int c, int next) :
			v(v), c(c), next(next) {
	}
	Edges() {
	}
} edge[10000007];
int head[maxn], E;
void add(int s, int t, int c) {
	edge[E] = Edges(t, c, head[s]);
	head[s] = E++;
	edge[E] = Edges(s, 0, head[t]);
	head[t] = E++;
}
void init() {
	memset(head, -1, sizeof(head));
	E = 0;
}
int gap[maxn], dis[maxn], pre[maxn], cur[maxn];
int sap(int s, int t, int n, int lim) {// s 源?，t??，n????, 限制最大增?的流量
    int i;
    for(i = 0; i <= n; i++) {
        dis[i] = gap[i] = 0;
        cur[i] = head[i];
    }
    gap[0] = n;
    int u = pre[s] = s, maxf = 0, aug = lim, v;
    while(dis[s] < n) {
        loop: for(i = cur[u]; ~i; i = edge[i].next) {
            v = edge[i].v;
            if(edge[i].c  && dis[u] == dis[v] + 1) {
                aug = min(aug, edge[i].c);
                pre[v] = u;
                cur[u] = i;
                u = v;
                if(u == t) {
                    while(u != s) {
                        u = pre[u];
                        edge[cur[u]].c -= aug;
                        edge[cur[u] ^ 1].c += aug;
                    }
                    maxf += aug;
                    lim -= aug;
                    aug = lim;
                    if(!lim) return maxf;
                }
                goto loop;
            }
        }
        int d = n;
        for(i = head[u]; ~i; i = edge[i].next) {
            v = edge[i].v;
            if(edge[i].c && dis[v] < d) {
                d = dis[v];
                cur[u] = i;
            }
        }
        if(!(--gap[dis[u]]))
            break;
        ++gap[dis[u] = d + 1];
        u = pre[u];
    }
    return maxf;
}
//*************************************
int u[203], v[203];
int ans;
void solve() {
	int i, j, maxf = 0;
	ans = 0;
	init();
	while(maxf < k) {
		ans++;
		for(i = 0; i < n; i++)
			add((ans-1)*n+i, ans*n+i, inf);
		for(i = 0; i < m; i++) {
			add((ans-1)*n+u[i]-1, ans*n+v[i]-1, 1);
			add((ans-1)*n+v[i]-1, ans*n+u[i]-1, 1);
		}
		maxf += sap(S-1, T+ans*n-1, (ans+1)*n, k-maxf);
	}
	printf("%d\n", ans);
}

int main() {
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout); 
    int i, j;
	while( ~scanf("%d%d%d%d%d", &n, &m, &k, &S, &T)) {
		for(i = 0; i < m; i++) scanf("%d%d", &u[i], &v[i]);
		solve();
		vector <int> pos(k, S);
		int idx = 0;
		for(int d = 1; d <= ans; d++) {
			idx += (n<<1);
			vector <int> a;
			vector <int> b;
			vector <bool> vis(k, 0);
			for(i = 0; i < m; i++) {
				//同?枚?2??避免上面第2?注意?
				int f1 = edge[idx^1].c; idx += 2;
				int f2 = edge[idx^1].c; idx += 2;
				if(f1 && !f2) a.push_back(u[i]), b.push_back(v[i]);
				if(!f1 && f2) a.push_back(v[i]), b.push_back(u[i]);
			}
			printf("%d", a.size());
			for(i = 0; i < a.size(); i++)
				for(j = 0; j < k; j++)
					if(!vis[j] && a[i] == pos[j]) {
						printf(" %d %d", j+1, b[i]);
						pos[j] = b[i];
						vis[j] = 1;
						break;
					}
            puts("");
		}
	}
	return 0;
}
