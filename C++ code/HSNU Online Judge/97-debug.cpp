#include<bits/stdc++.h>
using namespace std;
const int maxn=5001 ;
bool G[maxn][maxn] ;
 
void getint(int &x)
{
    char c=getchar() ;
    while(c<'0' || c>'9') c=getchar() ;
    x=0 ;
    while(c>='0' && c<='9')
    {
        x*=10 ; x+=c-'0' ;
        c=getchar() ;
    }
}
 
int n,col[maxn] ;
 
bool dfs(int x,vector<int> &vec)
{
    vec.push_back(x) ;
    if(col[x]==0)
    {
        for(int i=1;i<=n;i++) if(i!=x && !G[i][x])
        {
            if(col[i]==1) continue ;
            if(col[i]==0) return 0 ;
            col[i]=1 ; if(!dfs(i,vec)) return 0 ;
        }
    }
    else
    {
        for(int i=1;i<=n;i++) if(i!=x && G[i][x])
        {
            if(col[i]==0) continue ;
            if(col[i]==1) return 0 ;
            col[i]=0 ; if(!dfs(i,vec)) return 0 ;
        }
    }
    return 1 ;
}
 
bool check()
{
    bool ok=1 ;
    int st ;
    for(st=1;st<=n;st++) if(col[st]==-1) { ok=0 ; break ; }
    if(ok) return 1 ;
 
    vector<int> tmp ;
    col[st]=0 ;
    if(dfs(st,tmp) && check()) return 1 ;
    for(int i=0;i<tmp.size();i++) col[tmp[i]]=-1 ;
    tmp.clear() ;
 
    col[st]=1 ;
    if(dfs(st,tmp) && check()) return 1 ;
    for(int i=0;i<tmp.size();i++) col[tmp[i]]=-1 ;
    return 0 ;
}
 
int deg[maxn] ;
main()
{
    scanf("%d",&n) ;
    int tot=0 ;
    for(int i=1;i<=n;i++)
    {
        int m ; scanf("%d",&m) ;
        deg[i]=m ; tot+=m ;
        while(m--)
        {
            int x ; getint(x) ;
            G[i][x]=1 ;
        }
    }
 
    if(tot==0 || tot==n*(n-1)) { printf("%d\n",n) ; return 0 ; }
 
    memset(col,-1,sizeof(col)) ;
    if(!check()) { printf("0\n") ; return 0 ; }
 
    int A=0 , B=0 ;
    for(int i=1;i<=n;i++)
        if(col[i]==0) A++ ;//A is alledge
        else B++ ;//B is noedge
 
    int ans=1 ;
    for(int i=1;i<=n;i++)
    {
        if(col[i]==0 && deg[i]<=A)
        {
            if(deg[i]==A-1) { ans++ ; continue ; }
            int j ;
            for(j=1; !(col[j]==1&&G[i][j]) ;j++) ;
            if(deg[j]==A) ans++ ;
        }
        else if(col[i]==1 && deg[i]>=A-1)
        {
            if(deg[i]==A) { ans++ ; continue ; }
            int j ;
            for(j=1; !(col[j]==0&&(!G[i][j])) ;j++) ;
            if(deg[j]==A-1) ans++ ;
        }
    }
    printf("%d\n",ans) ;
}
