#include<bits/stdc++.h>
#define LL long long
#define INF (1LL<<60)
#define F first
#define S second
#define mkp(x,y) make_pair(x,y)
#define MAX(x,y,z) max(x,max(y,z))
#define MIN(x,y,z) min(x,min(y,z))
using namespace std;
 
int a[25] ;
LL sum2 ;
 
set<LL> st ;
pair<LL,LL> solve(const vector<int> &v)
{
    int n1=v.size()/2 , n2=v.size()-n1 ;
    st.clear() ;
    pair<LL,LL> ret=mkp(0,sum2) ;
    for(int i=0;i<(1<<n1);i++)
    {
        LL s=0LL ;
        for(int j=0;j<n1;j++) if(i&(1<<j))
            s+=v[j] ;
        st.insert(s) ;
    }
 
    LL h=sum2/2 ;
    for(int i=0;i<(1<<n2);i++)
    {
        LL s=0LL ;
        for(int j=0;j<n2;j++) if(i&(1<<j))
            s+=v[j+n1] ;
        auto it=st.lower_bound(h-s) ;
        if(it!=st.end())
        {
            LL x=*it+s , y=sum2-x ;
            if(x>y) swap(x,y) ;
            if(y-x < ret.S-ret.F) ret=mkp(x,y) ;
        }
    }
    return ret ;
}
 
main()
{
    //freopen("in.txt","r",stdin) ;
    int n ; scanf("%d",&n) ;
    LL sum=0LL ;
    for(int i=0;i<n;i++) scanf("%d",&a[i]) , sum+=a[i] ;
    LL ans=INF ;
 
    for(int i=1;i<(1<<n);i++)
    {
        int bcnt=0 ;
        for(int j=0;j<n;j++) if(i&(1<<j))
            bcnt++ ;
        if(bcnt>n/3) continue ;
 
        sum2=sum ;
        vector<int> tmp ;
        for(int j=0;j<n;j++)
        {
            if(i&(1<<j)) sum2-=a[j] ;
            else tmp.push_back(a[j]) ;
        }
 
        if(abs(sum-sum2 - sum2/2) >= ans) continue ;
// 		static int aaa=0;if(aaa++%1000==0)printf("aaa=%d,i=%d\n",aaa,i);
        pair<LL,LL> p=solve(tmp) ;
        LL x=p.F , y=p.S , z=sum-sum2 ;
        if(x>y) swap(x,y) ;
        if(y>z) swap(y,z) ; if(x>y) swap(x,y) ;
        ans=min(ans,z-x) ;
    }
    printf("%I64d\n",ans) ;
}
