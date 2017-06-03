#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int maxn=1000000+10 ;
 
int bit[2][maxn] ;
void add(int id,int x,int val)
{
    for(;x<maxn;x+=lowbit(x)) bit[id][x]+=val ;
}
int query(int id,int x)
{
    int ret=0 ;
    for(;x;x-=lowbit(x)) ret+=bit[id][x] ;
    return ret ;
}
 
int a[maxn],b[maxn],fail[maxn] ;
vector<int> v,ans ;
main()
{
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
    int n,m ; scanf("%d%d",&m,&n) ;
    for(int i=1;i<=m;i++)
    {
        int x ; scanf("%d",&x) ;
        b[x]=i ;
    }
    for(int i=1;i<=n;i++) scanf("%d",&a[i]) , v.push_back(a[i]) ;
    sort(v.begin(),v.end()) ;
    for(int i=1;i<=n;i++) a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1 ;
    for(int i=2,j=0;i<=m;i++)
    {
        while(j && query(0,b[j+1]-1)!=query(1,b[i]-1))
        {
            int j2=fail[j] ;
            for(;j!=j2;j--)
                add(0,b[j],-1) , add(1,b[i-j],-1) ;
        }
        if(query(0,b[j+1]-1)==query(1,b[i]-1))
            j++ , add(0,b[j],1) , add(1,b[i],1) ;
        fail[i]=j ;
    }
    for(int i=0;i<=m;i++)printf(" %d",fail[i]);puts("");
    memset(bit,0,sizeof(bit)) ;
    for(int i=1,j=0;i<=n;i++)
    {
        while(j && query(0,b[j+1]-1)!=query(1,a[i]-1))
        {
            int j2=fail[j] ;
            for(;j!=j2;j--)
                add(0,b[j],-1) , add(1,a[i-j],-1) ;
        }
        if(query(0,b[j+1]-1)==query(1,a[i]-1))
            j++ , add(0,b[j],1) , add(1,a[i],1) ;
        if(j==m)
        {
            ans.push_back(i-j+1) ;
            int j2=fail[j] ;
            for(;j!=j2;j--)
                add(0,b[j],-1) , add(1,a[i-j+1],-1) ;
        }
    }
    printf("%d\n",ans.size()) ;
    for(int i=0;i<ans.size();i++) printf("%d%c",ans[i],i+1==ans.size()?'\n':' ') ;
}
