#include<cstdio>
#include<cassert>
#include<utility>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
LL MOD=1e9+7;
pair<double,LL>PASS[2000000],END[2000000];
LL X[500000],Y[500000];
pair<double,LL>operator+(const pair<double,LL>&a,const pair<double,LL>&b){return make_pair(a.first+b.first,a.second*b.second%MOD);}
void Build(const int id,const int l,const int r)
{
	if(l==r){PASS[id]=make_pair(log(X[r]),X[r]),END[id]=PASS[id]+make_pair(log(Y[r]),Y[r]);return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	PASS[id]=PASS[id*2]+PASS[id*2+1];
	END[id]=max(END[id*2],PASS[id*2]+END[id*2+1]);
}
void ModifyX(const int id,const int l,const int r,const int loc,const LL v)
{
	if(l==r)
	{
		assert(r==loc);
		X[r]=v;
		PASS[id]=make_pair(log(X[r]),X[r]),END[id]=PASS[id]+make_pair(log(Y[r]),Y[r]);
		return;
	}
	const int mid=(l+r)/2;
	if(loc<=mid)ModifyX(id*2,l,mid,loc,v);
	else ModifyX(id*2+1,mid+1,r,loc,v);
	PASS[id]=PASS[id*2]+PASS[id*2+1];
	END[id]=max(END[id*2],PASS[id*2]+END[id*2+1]);
}
void ModifyY(const int id,const int l,const int r,const int loc,const LL v)
{
	if(l==r)
	{
		assert(r==loc);
		Y[r]=v;
		END[id]=PASS[id]+make_pair(log(Y[r]),Y[r]);
		return;
	}
	const int mid=(l+r)/2;
	if(loc<=mid)ModifyY(id*2,l,mid,loc,v);
	else ModifyY(id*2+1,mid+1,r,loc,v);
	END[id]=max(END[id*2],PASS[id*2]+END[id*2+1]);
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lld",&X[i]);
		for(int i=0;i<N;i++)scanf("%lld",&Y[i]);
		Build(1,0,N-1);
		int querycount;scanf("%d",&querycount);
		printf("%lld\n",END[1].second);
		for(int k,p,v;querycount--;)
		{
			scanf("%d%d%d",&k,&p,&v);
			if(k==1)ModifyX(1,0,N-1,p,v);
			else if(k==2)ModifyY(1,0,N-1,p,v);
			else assert(0);
			printf("%lld\n",END[1].second);
		}
	}
	return 0;
}
