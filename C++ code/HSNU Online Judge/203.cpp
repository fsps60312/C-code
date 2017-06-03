#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,L;
int W[100001],H[100001],SUM[100001];
int DP[400000];
void Build(const int &id,const int &l,const int &r)
{
	DP[id]=INF;
	if(l==r)return;
	int mid=(l+r)>>1;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void Set(const int &id,const int &l,const int &r,const int &i,const int &v)
{
	if(l==r){DP[id]=v;return;}
	int mid=(l+r)>>1;
	if(i<=mid)Set(id*2,l,mid,i,v);
	else Set(id*2+1,mid+1,r,i,v);
	DP[id]=min(DP[id*2],DP[id*2+1]);
}
void Set(const int &i,const int &v){Set(1,0,N,i,v);}
int Get(const int &id,const int &l,const int &r,const int &i)
{
	if(l==r)return DP[id];
	int mid=(l+r)>>1;
	if(i<=mid)return Get(id*2,l,mid,i);
	else return Get(id*2+1,mid+1,r,i);
}
int Get(const int &i,const int &v){Get(1,0,N,i);}
int main()
{
	scanf("%d%d",&N,&L);
	SUM[0]=0;
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d",&H[i],&W[i]);
		SUM[i]=SUM[i-1]+W[i];
	}
	Build(1,1,N);
	Set(0,0);
	for(int i=1;i<=N;i++)
	{
		
	}
	return 0;
}
