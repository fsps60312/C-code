#include<cstdio>
#include<cassert>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
int N;
LL A[500000],B[500000];
pair<double,LL>END[500000*4],PAS[500000*4];
pair<double,LL>operator+(const pair<double,LL>&a,const pair<double,LL>&b){return make_pair(a.first+b.first,a.second*b.second%MOD);}
void Build(const int id,const int l,const int r)
{
	if(l==r){PAS[id]=make_pair(log(A[r]),A[r]),END[id]=PAS[id]+make_pair(log(B[r]),B[r]);return;}
	const int mid=(l+r)/2;
	const int li=id*2,ri=id*2+1;
	Build(li,l,mid),Build(ri,mid+1,r);
	END[id]=max(END[li],PAS[li]+END[ri]);
	PAS[id]=PAS[li]+PAS[ri];
}
void ModifyGrow(const int id,const int l,const int r,const int loc,const LL &v)
{
	if(l==r){assert(r==loc);A[r]=v;PAS[id]=make_pair(log(v),v),END[id]=PAS[id]+make_pair(log(B[r]),B[r]);return;}
	const int mid=(l+r)/2;
	const int li=id*2,ri=id*2+1;
	if(loc<=mid)ModifyGrow(li,l,mid,loc,v);
	else ModifyGrow(ri,mid+1,r,loc,v);
	END[id]=max(END[li],PAS[li]+END[ri]);
	PAS[id]=PAS[li]+PAS[ri];
}
void ModifySell(const int id,const int l,const int r,const int loc,const LL &v)
{
	if(l==r){assert(r==loc);B[r]=v;END[id]=PAS[id]+make_pair(log(v),v);return;}
	const int mid=(l+r)/2;
	const int li=id*2,ri=id*2+1;
	if(loc<=mid)ModifySell(li,l,mid,loc,v);
	else ModifySell(ri,mid+1,r,loc,v);
	END[id]=max(END[li],PAS[li]+END[ri]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%lld",&A[i]);
	for(int i=0;i<N;i++)scanf("%lld",&B[i]);
	int querycount;scanf("%d",&querycount);
	Build(1,0,N-1);
	printf("%lld\n",END[1].second);
	for(int type,p,v;querycount--;)
	{
		scanf("%d%d%d",&type,&p,&v);
		switch(type)
		{
			case 1:ModifyGrow(1,0,N-1,p,v);break;
			case 2:ModifySell(1,0,N-1,p,v);break;
			default:assert(0);break;
		}
		printf("%lld\n",END[1].second);
	}
	return 0;
}
