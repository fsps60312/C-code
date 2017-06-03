#include<bits/stdc++.h>
using namespace std;
const long long INF=(1LL<<61)-1LL;
int N,P,Q;
long long X,Y;
char S[1000001];
int SUM[4000001];
void Build(int id,int l,int r)
{
	SUM[id]=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	Build((id<<1),l,mid);
	Build((id<<1)+1,mid+1,r);
}
void Add(int id,int l,int r,const int &v,const int &d)
{
	if(l==r){SUM[id]+=d;return;}
	int mid=(l+r)>>1;
	if(v<=mid)Add((id<<1),l,mid,v,d);
	else Add((id<<1)+1,mid+1,r,v,d);
	SUM[id]=SUM[(id<<1)]+SUM[(id<<1)+1];
}
int Query(int id,int l,int r)
{
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(SUM[(id<<1)])return Query((id<<1),l,mid);
	else return Query((id<<1)+1,mid+1,r);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%lld%lld%s",&N,&P,&Q,&X,&Y,S);
	Build(1,0,N*2);
	int l=N,r=N;
	for(int i=0;i<N;i++)
	{
		if(S[i]=='+')r++;
		else r--;
		Add(1,0,N*2,r,1);
	}
	int adjust=Q-(P+(r-N));
	assert(!(adjust&1));
	adjust/=2;
	int cyc=0;
	long long ans=INF,v;
	for(int i=N-1,mn,opes,a,b;;i--,cyc++)
	{
		mn=P+((Query(1,0,N*2)-N)-(l-N));
		if(mn>0)mn=0;
		opes=(-mn+1)/2;
		a=b=opes;
		if(adjust>=0)
		{
			if(b>=adjust)b-=adjust;
			else a+=adjust-b,b=0;
		}
		else b-=adjust;
		v=Y*cyc+X*(a+b);
		ans=min(ans,v);
		if(!i)break;
		Add(1,0,N*2,r,-1);
		if(S[i]=='+')r--,l--;
		else r++,l++;
		Add(1,0,N*2,l,1);
	}
	printf("%lld\n",ans);
	return 0;
}
