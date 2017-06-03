#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF=(1LL<<61)-1LL;
LL N,P,Q,X,Y;
char S[1000001];
int SUM[4000001];
void Build(LL id,LL l,LL r)
{
	SUM[id]=0;
	if(l==r)return;
	LL mid=(l+r)/2LL;
	Build(id*2LL,l,mid);
	Build(id*2LL+1LL,mid+1LL,r);
}
void Add(LL id,LL l,LL r,const LL &v,const int &d)
{
	if(l==r){SUM[id]+=d;return;}
	LL mid=(l+r)/2LL;
	if(v<=mid)Add(id*2LL,l,mid,v,d);
	else Add(id*2LL+1LL,mid+1LL,r,v,d);
	SUM[id]=SUM[id*2LL]+SUM[id*2LL+1LL];
}
LL Query(LL id,LL l,LL r)
{
	if(l==r)return l;
	LL mid=(l+r)/2LL;
	if(SUM[id*2LL])return Query(id*2LL,l,mid);
	else return Query(id*2LL+1LL,mid+1LL,r);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld%lld%lld%lld%lld%s",&N,&P,&Q,&X,&Y,S);
	Build(1LL,0LL,N*2LL);
	LL l=N,r=N;
	for(LL i=0LL;i<N;i++)
	{
		if(S[i]=='+')r++;
		else r--;
		Add(1LL,0LL,N*2LL,r,1);
	}
	LL adjust=Q-(P+(r-N));
	adjust/=2LL;
	LL ans=INF,cyc=0LL;
	for(LL i=N-1LL,mn,opes,v,a,b;;i--,cyc++)
	{
		mn=P+((Query(1LL,0LL,N*2LL)-N)-(l-N));
		if(mn>0LL)mn=0LL;
		opes=(-mn+1LL)/2LL;
		a=b=opes;
		if(adjust>=0LL)
		{
			if(b>=adjust)b-=adjust;
			else a+=adjust-b,b=0LL;
		}
		else b+=-adjust;
		v=Y*cyc+X*(a+b);
		ans=min(ans,v);
		if(i==0LL)break;
		Add(1LL,0LL,N*2LL,r,-1);
		if(S[i]=='+')r--,l--;
		else r++,l++;
		Add(1LL,0LL,N*2LL,l,1);
	}
	printf("%lld\n",ans);
	return 0;
}
