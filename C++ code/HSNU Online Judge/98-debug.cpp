#include<bits/stdc++.h>
using namespace std;
const int maxn=1000000+10;
vector<int> v[maxn],tmp[maxn];
bool now[maxn];
int n;
bool dfs(int x,int last)
{
    if(last<0) return 0;
    if(x==n+1) return 1;
    if(now[x] || v[x].empty()) return dfs(x+1,last);
    for(int i=0;i<v[x].size();i++) if(!now[v[x][i]])
    {
        now[x]=1;
        if(dfs(x+1,last-1)) return 1;
        now[x]=0;break;
    }
    tmp[x].clear();
    for(int i=0;i<v[x].size();i++)if(!now[v[x][i]])
        now[v[x][i]]=1,tmp[x].push_back(v[x][i]);
    if( dfs(x+1,last-((int)tmp[x].size())) ) return 1;
    for(int i=0;i<tmp[x].size();i++) now[tmp[x][i]]=0;
    return 0;
}
bool check(int k)
{
    memset(now,0,sizeof(now));
    return dfs(1,n-k);
}
main()
{
	freopen("in.txt","r",stdin);
    int k,m;scanf("%d%d%d",&n,&k,&m);
    while(m--)
    {
        int x,y;scanf("%d%d",&x,&y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    if(!check(k)){printf("NIE\n");return 0;}
    int l=k,r=n,ok=0;
    while(r-l>1)
    {
        int mid=(r+l)/2;
        if(check(mid)) l=mid,ok=1;
        else r=mid,ok=0;
    }
    check(l);
    printf("%d\n",l);
    int cnt=0;
    for(int i=1;i<=n;i++) if(!now[i]) printf("%d%c",i,++cnt==l?'\n':' ');
}
