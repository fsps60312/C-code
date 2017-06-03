#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = (int)1e6+10;
const int inf=~0u>>2;
int s[N];
struct splaytree{
    int cnt,root;
    int sz[N],ch[N][2],pre[N];
    int add[N],rev[N],minn[N],val[N];
    inline void newnode(int &t,int v){
        t=++cnt;
        ch[t][0]=ch[t][1]=0;
        add[t]=rev[t]=0;
        sz[t]=1;
        minn[t]=v;
        val[t]=v;
    }
    inline void pushup(int x){
        sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
        minn[x]=min(min(minn[ch[x][0]],minn[ch[x][1]]),val[x]);
    }
    inline void pushdown(int x){
        if(rev[x]){
            if(ch[x][0])rev[ch[x][0]]^=1;
            if(ch[x][1])rev[ch[x][1]]^=1;
            swap(ch[x][0],ch[x][1]);
            rev[x]^=1;
        }
        if(add[x]){
            if(ch[x][0])add[ch[x][0]]+=add[x],minn[ch[x][0]]+=add[x],val[ch[x][0]]+=add[x];
            if(ch[x][1])add[ch[x][1]]+=add[x],minn[ch[x][1]]+=add[x],val[ch[x][1]]+=add[x];
            add[x]=0;
        }
    }
    inline bool dir(int x){return ch[pre[x]][1]==x;}
    inline void link(int x,int y,int d){
        if(y)ch[y][d]=x;
        if(x)pre[x]=y;
    }
    inline void rotate(int x){
        int y=pre[x];bool d=dir(x);
        pushdown(y);pushdown(x);
        link(x,pre[y],dir(y));
        link(ch[x][!d],y,d);
        link(y,x,!d);
        pushup(y);
    }
    inline void splay(int x,int goal){
        pushdown(x);
        while(pre[x]!=goal){
            if(pre[pre[x]]==goal)rotate(x);
            else{
                if(dir(x)==dir(pre[x]))rotate(pre[x]);
                else rotate(x);
                rotate(x);
            }
        }
        pushup(x);
        if(goal==0)root=x;
    }
    inline void select(int k,int goal){
        int x=root;
        pushdown(x);
        while(sz[ch[x][0]]!=k){
            if(sz[ch[x][0]] > k ) x=ch[x][0];
            else{
                k-=(sz[ch[x][0]]+1);x=ch[x][1];
            }
            pushdown(x);
        }
        splay(x,goal);
    }
    inline int get(int L,int R){
        select(L-1,0);
        select(R+1,root);
        return ch[root][1];
    }
    inline void build(int l,int r,int &t,int p){
        if(l>r)return;
        int m=(l+r)>>1;
        newnode(t,s[m]);
        build(l,m-1,ch[t][0],t);
        build(m+1,r,ch[t][1],t);
        pre[t]=p;
        pushup(t);
    }
    void init(int n){
        cnt=root=0;
        sz[0]=ch[0][0]=ch[0][1]=pre[0]=0;
        add[0]=rev[0]=0;
        minn[0]=inf;
        val[0]=inf;
        newnode(root,inf);
        newnode(ch[root][1],inf);
        pre[cnt]=root;
        sz[root]=2;
        build(1,n,ch[ch[root][1]][0],ch[root][1]);
        pushup(ch[root][1]);
        pushup(root);
    }
    inline void ADD(int L,int R,int d){
        int x=get(L,R);
        add[ch[x][0]]+=d;
        minn[ch[x][0]]+=d;
        val[ch[x][0]]+=d;
        pushup(x);
        pushup(root);
    }
    inline void REVERSE(int L,int R){
        int x=get(L,R);
        rev[ch[x][0]]^=1;
    }
    inline void INSERT(int x,int val){
        select(x,0);
        select(x+1,root);
        newnode(ch[ch[root][1]][0],val);
        pre[ch[ch[root][1]][0]]=ch[root][1];
        pushup(ch[root][1]);
        pushup(root);
    }
    inline void REVOLVE(int L,int R,int t){
        int len=(R-L+1);t=(t%len+len)%len;
        if(t==0)return;
        REVERSE(L,R-t);
        REVERSE(R-t+1,R);
        REVERSE(L,R);
    }
    inline void DELETE(int P){
        int x=get(P,P);
        ch[x][0]=0;
        pushup(x);
        pushup(root);
    }
    inline int MIN(int L,int R){
        int x=get(L,R);
        return minn[ch[x][0]];
    }
};
splaytree a;
int main(){
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout);
    int n,m,x,y,t;
    char op[10];
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++)scanf("%d",&s[i]);
        a.init(n);
        scanf("%d",&m);
        while(m--){
            scanf("%s",op);
            if(op[0]=='A'){
                scanf("%d%d%d",&x,&y,&t);
                a.ADD(x,y,t);
            }else if(op[0]=='R'){
                if(op[3]=='E'){
                    scanf("%d%d",&x,&y);
                    a.REVERSE(x,y);
                }else{
                    scanf("%d%d%d",&x,&y,&t);
                    a.REVOLVE(x,y,t);
                }
            }else if(op[0]=='I'){
                scanf("%d%d",&x,&t);
                a.INSERT(x,t);
            }else if(op[0]=='D'){
                scanf("%d",&x);
                a.DELETE(x);
            }else{
                scanf("%d%d",&x,&y);
                printf("%d\n",a.MIN(x,y));
            }
        }
    }
    return 0;
}
