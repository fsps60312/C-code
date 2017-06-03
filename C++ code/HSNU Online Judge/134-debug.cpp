#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+10 ;
 
int n,m ;
int dp[maxn] ;
void solve(vector<int> v[],int *mi)
{
    mi[1]=0 ;
    int num=0 ; dp[0]=0 ;
    for(int i=2;i<=n;i++)
    {
        for(int j=((int)v[i].size())-1;j>=0;j--)
        {
            int id=upper_bound(dp,dp+num+1,v[i][j])-dp ;
            dp[id]= (id==num+1 ? v[i][j] : min(dp[id],v[i][j])) ;
            if(id==num+1) num++ ;
        }
        mi[i]=i-1-num ;
    }
}
 
vector<int> v1[maxn],v2[maxn] ;
int a[maxn],b[maxn] ;
main()
{
	freopen("in.txt","r",stdin);
    int p,k ; scanf("%d%d%d%d",&n,&m,&p,&k) ;
    while(p--)
    {
        int x,y,type ; scanf("%d%d%d",&x,&y,&type) ;
        if(type==1) v1[x+1].push_back(m-y) ;
        else v2[n-x+1].push_back(m-y) ;
    }
    for(int i=2;i<=n;i++)
    {
        sort(v1[i].begin(),v1[i].end()) ;
        sort(v2[i].begin(),v2[i].end()) ;
        v1[i].resize(unique(v1[i].begin(),v1[i].end())-v1[i].begin()) ;
        v2[i].resize(unique(v2[i].begin(),v2[i].end())-v2[i].begin()) ;
    }
    solve(v1,a) ;
    solve(v2,b) ;
 
    int i=1,j=1,ans1=0 ;
    for(int z=0;z<=k;z++)
    {
        while(i<=n && a[i]<=z) i++ ; i-- ;
        while(j<=n && b[n-j+1]>k-z) j++ ;
        ans1=max(ans1,i-j+1) ;
    }
 
    i=n ; j=1 ;
    while(a[i]) i-- ;
    while(b[n+1-j]) j++ ;
    int ans2=max(0,i-j+1) ;
 
    printf("%d\n",ans1-ans2) ;
}
