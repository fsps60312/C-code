#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M,MX[800000];
void Modify(const int id,const int l,const int r,const int loc,const int val)
{
	if(l==r){assert(loc==r);MX[id]=val;return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Modify(id*2,l,mid,loc,val);
	else Modify(id*2+1,mid+1,r,loc,val);
	MX[id]=max(MX[id*2],MX[id*2+1]);
}
int Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(r<bl||br<l)return -INF;
	if(bl<=l&&r<=br)return MX[id];
	const int mid=(l+r)/2;
	return max(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1,v;i<=N;i++)scanf("%d",&v),Modify(1,1,N,i,v);
		for(int a,b;M--;)
		{
			static char type[2];
			scanf("%s%d%d",type,&a,&b);
			if(type[0]=='Q')printf("%d\n",Query(1,1,N,a,b));
			else if(type[0]=='U')Modify(1,1,N,a,b);
			else assert(0);
		}
	}
	return 0;
}
