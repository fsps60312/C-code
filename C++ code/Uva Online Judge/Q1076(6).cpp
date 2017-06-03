#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
#define LL long long
#define debug(...) __VA_ARGS__
int WANTV,N,M;
struct Trie
{
    struct Node
    {
        int v,f;
        int ch[26];
    }n[101];
    int sz;
    void init(int u)
    {
        Node &a=n[u];
        for(int i=0;i<26;i++)a.ch[i]=0;
        a.v=0;
    }
    void clear(){sz=1;init(0);}
    int findnode(int u,int c)
    {
        int &ch=n[u].ch[c];
        if(ch)return ch;
        ch=sz;
        init(sz);
        return sz++;
    }
    void insert(char *s,int v)
    {
        int u=0;
        for(int i=0;s[i];i++)
        {
            u=findnode(u,s[i]-'a');
        }
        n[u].v|=v;
        //printf("n[%d].v=%d\n",u,n[u].v);
    }
    void getfail()
    {
        n[0].f=0;
        queue<int> q;
        for(int i=0;i<26;i++)
        {
            int c=n[0].ch[i];
            if(c)
            {
                n[c].f=0;
                q.push(c);
            }
        }
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=0;i<26;i++)
            {
                int &c=n[u].ch[i];
                if(c)
                {
                    int f=n[u].f;
                    while(f&&!n[f].ch[i])f=n[f].f;
                    n[c].f=n[f].ch[i];
                    n[c].v|=n[n[c].f].v;
                    q.push(c);
                }
                else
                {
                    c=n[n[u].f].ch[i];
                }
            }
        }
    }
    LL DP[101][26][1<<10];
    void clearDP()
    {
        for(int i=0;i<sz;i++)
        {
            for(int j=0;j<=N;j++)
            {
                for(int k=0;k<(1<<M);k++)
                {
                    DP[i][j][k]=-1;
                }
            }
        }
    }
    LL getDP(int u,int l,int vis)
    {
        vis|=n[u].v;
        LL &D=DP[u][l][vis];
        if(D!=-1)return D;
        if(l==N)return D=(vis==WANTV)?1:0;
        D=0;
        for(int i=0;i<26;i++)
        {
            int nu=n[u].ch[i];
            //if(!nu)nu=n[n[u].f].ch[i];
            D+=getDP(nu,l+1,vis);
        }
        return D;
    }
    int AL;
    char ANS[42][26];
    char TSTR[26];
    void summarize(int u,int l,int vis)
    {
        if(l>N||!DP[u][l][vis])return;
        vis|=n[u].v;
        if(vis==WANTV&&l==N)
        {
            for(int i=0;i<l;i++)ANS[AL][i]=TSTR[i];
            ANS[AL++][l]=0;
            return;
        }
        for(int i=0;i<26;i++)
        {
            TSTR[l]='a'+i;
            int nu=n[u].ch[i];
            //if(!nu)nu=n[n[u].f].ch[i];
            summarize(nu,l+1,vis);
        }
    }
    bool strcmp(char *a,char *b)
    {
        int i;
        for(int i=0;a[i]&&b[i];i++)
        {
            if(a[i]!=b[i])return a[i]<b[i]?true:false;
        }
        return a[i]==0?true:false;
    }
    void printANS()
    {
        AL=0;
        summarize(0,0,0);
        for(int i=0;i<AL;i++)
        {
            int a=i;
            for(int j=i+1;j<AL;j++)
            {
                if(strcmp(ANS[j],ANS[a]))a=j;
            }
            for(int j=0;j<26;j++)
            {
                char c=ANS[i][j];
                ANS[i][j]=ANS[a][j];
                ANS[a][j]=c;
            }
            printf("%s\n",ANS[i]);
        }
    }
}trie;
LL solve()
{
    trie.clear();
    char tstr[11];
    for(int i=0;i<M;i++)
    {
        scanf("%s",tstr);
        trie.insert(tstr,1<<i);
        //debug(printf("trie.sz=%d\n",trie.sz););
    }
    //for(int i=0;i<trie.sz;i++)printf("node[%d]=%d\n",i,trie.n[i].v);
    WANTV=(1<<M)-1;
    //debug(printf("WANTV=%d\n",WANTV););
    trie.getfail();
    trie.clearDP();
    trie.getDP(0,0,0);
    /*for(int i=0;i<trie.sz;i++)
    for(int j=0;j<=N;j++)
    for(int k=0;k<=WANTV;k++)
    if(trie.DP[i][j][k]!=-1)printf("u=%d,l=%d,vis=%d,DP=%lld\n",i,j,k,trie.DP[i][j][k]);*/
    return trie.getDP(0,0,0);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int kase=1;
    while(scanf("%d%d",&N,&M)==2&&(N||M))
    {
        LL ans=solve();
        printf("Case %d: %lld suspects\n",kase++,ans);
        if(ans<=42)
        {
            trie.printANS();
        }
    }
    return 0;
}
