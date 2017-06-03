/*
	Author: mowayao
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

typedef long long LL;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
#define REP(_,a,b) for(int _ = (a); _ <= (b); _++)
#define RREP(_,a,b) for(int _ = (a); _ >= (b); _--)
#define mk make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define all(a) (a.begin()),(a.end())
#define zero(a) memset(a,0,sizeof(a))
#define MID(a,b) ((a)+(b)) >> 1
const int maxn = 100000+10;
struct node {
    int maxv;
    int sum;
    int flag;
    int minv;
}tree[maxn<<2];
struct person {
    int b,c;
    person(int b = 0, int c = 0):b(b),c(c){}
};
void build(int L,int R,int rt) {
    tree[rt].maxv = tree[rt].sum = tree[rt].flag = tree[rt].minv = 0;
    if(L==R) return;
    int mid = MID(L,R);
    build(L,mid,rt<<1);
    build(mid+1,R,rt<<1|1);
}
void push(int L,int R,int rt,int x) {
    tree[rt].flag = 1;
    tree[rt].sum = (R-L+1)*x;
    tree[rt].maxv = tree[rt].minv = x;
}
void pushUp(int rt) {
    tree[rt].maxv = max(tree[rt<<1].maxv,tree[rt<<1|1].maxv);
    tree[rt].minv = tree[rt<<1|1].minv;
    tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}
void pushDown(int L,int R,int rt) {
    if(tree[rt].flag) {
        int mid = MID(L,R);
        push(L,mid,rt<<1,tree[rt].maxv);
        push(mid+1,R,rt<<1|1,tree[rt].maxv);
        tree[rt].flag = 0;  
    }
}
void update(int l,int r,int L,int R,int rt,int x) {
    if(tree[rt].minv >= x) return;
    if(l <= L && r >= R && tree[rt].maxv < x) {
        push(L,R,rt,x);
        return;
    }
    pushDown(L,R,rt);
    int mid = MID(L,R);
    if(l <= mid) {
        update(l,r,L,mid,rt<<1,x);
    }
    if(r > mid){
        update(l,r,mid+1,R,rt<<1|1,x);
    }
    pushUp(rt);
}

vector<person> vp[maxn];
int n,m;
int maxa;
void init() {
    REP(i,0,m) vp[i].clear();
    maxa = 0;
}
void input () {
    REP(i,1,n) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        maxa = max(a,maxa);
        vp[a].pb(person(b,c));
    }
}
void solve() {
    build(1,m,1);
    LL ans = LL(m)*m*m;
    RREP(i,maxa,1) {
        REP(j,0,sz(vp[i])-1) {
            update(1,vp[i][j].b,1,m,1,vp[i][j].c);
        }
        ans -= LL(tree[1].sum);
    }
    printf("%lld\n",ans);
}
int  main() {
    while(~scanf("%d%d",&n,&m) && n+m) {
        init();
        input();
        solve();
    }
    return 0;
}
