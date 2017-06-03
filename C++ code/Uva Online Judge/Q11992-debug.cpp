#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
#define LL long long
using namespace std;
const LL maxn=100010<<2;
LL setv[30][maxn],addv[30][maxn],sum[30][maxn],maxnum[30][maxn],minnum[30][maxn];
void PushUp(LL num,LL rt)
{
    LL ls=rt<<1,rs=rt<<1|1;
    sum[num][rt]=sum[num][ls]+sum[num][rs];
    maxnum[num][rt]=max(maxnum[num][ls],maxnum[num][rs]);
    minnum[num][rt]=min(minnum[num][ls],minnum[num][rs]);
}
void PushDown(LL num,LL l,LL r,LL rt)
{
    LL m=(l+r)>>1;
    LL ls=rt<<1,rs=rt<<1|1;
    if(setv[num][rt]>0)
    {
        setv[num][ls]=setv[num][rs]=setv[num][rt];
        addv[num][ls]=addv[num][rs]=0;
        sum[num][ls]=(m-l+1)*setv[num][rt];
        sum[num][rs]=(r-m)*setv[num][rt];
        maxnum[num][ls]=maxnum[num][rs]=setv[num][rt];
        minnum[num][ls]=minnum[num][rs]=setv[num][rt];
        setv[num][rt]=-1;
    }
    if(addv[num][rt]>0)
    {
        addv[num][ls]+=addv[num][rt];
        addv[num][rs]+=addv[num][rt];
        sum[num][ls]+=(m-l+1)*addv[num][rt];
        sum[num][rs]+=(r-m)*addv[num][rt];
        maxnum[num][ls]+=addv[num][rt];
        maxnum[num][rs]+=addv[num][rt];
        minnum[num][ls]+=addv[num][rt];
        minnum[num][rs]+=addv[num][rt];
        addv[num][rt]=0;
    }
}
void build(LL num,LL l,LL r,LL rt)
{
    setv[num][rt]=-1;
    addv[num][rt]=0;
    if(l==r)
    {
        sum[num][rt]=maxnum[num][rt]=minnum[num][rt]=0;
        return;
    }
    LL m=(l+r)>>1;
    build(num,l,m,rt<<1);
    build(num,m+1,r,rt<<1|1);
    PushUp(num,rt);
}
void Update(LL num,LL type,LL value,LL L,LL R,LL l,LL r,LL rt)
{
    if(l>=L&&r<=R)
    {
        if(type==1)
        {
            addv[num][rt]+=value;
            sum[num][rt]+=(r-l+1)*value;
            minnum[num][rt]+=value;
            maxnum[num][rt]+=value;
        }
        if(type==0)
        {
            addv[num][rt]=0;
            setv[num][rt]=value;
            sum[num][rt]=(r-l+1)*value;
            minnum[num][rt]=maxnum[num][rt]=value;
        }
        return;
    }
    PushDown(num,l,r,rt);
    LL m=(l+r)>>1;
    if(m>=L)
      Update(num,type,value,L,R,l,m,rt<<1);
    if(m<R)
      Update(num,type,value,L,R,m+1,r,rt<<1|1);
    PushUp(num,rt);
}
void Query(LL num,LL L,LL R,LL l,LL r,LL rt,LL& s,LL& maxv,LL& minv)
{
    if(l>=L&&r<=R)
    {
        s=sum[num][rt];
        maxv=maxnum[num][rt];
        minv=minnum[num][rt];
        return;
    }
    PushDown(num,l,r,rt);
    LL m=(l+r)>>1;
    LL tsum,tminv,tmaxv;
    s=0;maxv=-1;minv=inf;
    if(m>=L)
    {
        Query(num,L,R,l,m,rt<<1,tsum,tmaxv,tminv);
        s+=tsum;
        maxv=max(maxv,tmaxv);
        minv=min(minv,tminv);
    }
    if(m<R)
    {
        Query(num,L,R,m+1,r,rt<<1|1,tsum,tmaxv,tminv);
        s+=tsum;
        maxv=max(maxv,tmaxv);
        minv=min(minv,tminv);
    }
}
int main()
{
    freopen("in.txt","r",stdin);
    freopen("New.txt","w",stdout);
    LL m,n,q;
    while(cin>>m>>n>>q)
    {
        for(LL i=1;i<=m;++i)
        {
            build(i,1,n,1);
        }
        LL type,x1,y1,x2,y2,v;
        while(q--)
        {
            cin>>type;
            if(type==1)
            {
                cin>>x1>>y1>>x2>>y2>>v;
                for(LL i=x1;i<=x2;++i)
                  Update(i,1,v,y1,y2,1,n,1);
            }
            else if(type==2)
            {
                cin>>x1>>y1>>x2>>y2>>v;
                for(LL i=x1;i<=x2;++i)
                  Update(i,0,v,y1,y2,1,n,1);
            }
            else
            {
                cin>>x1>>y1>>x2>>y2;
                LL s=0,minv=inf,maxv=-1;
                LL ts,tmin,tmax;
                for(LL i=x1;i<=x2;++i)
                {
                    Query(i,y1,y2,1,n,1,ts,tmax,tmin);
                    s+=ts;
                    maxv=max(maxv,tmax);
                    minv=min(minv,tmin);
                    printf(" %lld %lld %lld\n",s,minv,maxv);
                }
                printf("query:%lld %lld %lld %lld\n",x1,y1,x2,y2);
                cout<<s<<" "<<minv<<" "<<maxv<<endl;
            }
        }
    }
    return 0;
}

