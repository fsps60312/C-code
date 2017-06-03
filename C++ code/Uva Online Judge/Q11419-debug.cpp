#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1000 + 10;
const int maxm = 1000000 + 10;

int R, C, fa[maxn], mo[maxn], v[maxm], head[maxn], nxt[maxm], ecnt;
bool S[maxn], T[maxn];

void init(){
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void addEdge(int uu, int vv){
    v[ecnt] = vv;
    nxt[ecnt] = head[uu];
    head[uu] = ecnt;
    ecnt++;
}

bool match(int i){
    S[i] = 1;
    for(int e = head[i]; e != -1; e = nxt[e]) if(!T[v[e]]){
        T[v[e]] = 1;
        if(!fa[v[e]] || match(fa[v[e]])){
            fa[v[e]] = i;
            return 1;
        }
    }
    return 0;
}

void solve(){
    memset(fa, 0, sizeof(fa));
    int ret = 0;
    for(int i = 1; i <= R; i++){
        memset(S, 0, sizeof(S));
        memset(T, 0, sizeof(T));
        if(match(i)) ret++;
    }
    memset(mo, 0, sizeof(mo));
    memset(S, 0, sizeof(S));
    memset(T, 0, sizeof(T));
    for(int i = 1; i <= C; i++) mo[fa[i]] = 1;
    for(int i = 1; i <= R; i++) if(!mo[i]) match(i);
    printf("%d", ret);
    for(int i = 1; i <= R; i++) if(!S[i]) printf(" r%d", i);
    for(int i = 1; i <= C; i++) if(T[i]) printf(" c%d", i);
    puts("");
}

int main()
{
    int N, x, y;
    while(scanf("%d%d%d", &R, &C, &N) == 3){
        if(!R && !C && !N) return 0;
        init();
        for(int i = 1; i <= N; i++){
            scanf("%d%d", &x, &y);
            addEdge(x, y);
        }
        solve();
    }
    return 0;
}		
