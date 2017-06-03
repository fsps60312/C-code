#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Bst
{
	int MX[400000];
	void Maintain(const int id){MX[id]=max(MX[id*2],MX[id*2+1]);}
	void Build(const int id,const int l,const int r,const int *s)
	{
		if(l==r){MX[id]=s[r];return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,s),Build(id*2+1,mid+1,r,s);
		Maintain(id);
	}
	void Modify(const int id,const int l,const int r,const int loc,const int value)
	{
		if(l==r){assert(r==loc);MX[id]=value;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(id*2,l,mid,loc,value);
		else Modify(id*2+1,mid+1,r,loc,value);
		Maintain(id);
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return -INF;
		if(bl<=l&&r<=br)return MX[id];
		const int mid=(l+r)/2;
		return max(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
}BST;
int main()
{
//	freopen("in.txt","r",stdin);
	static int n,querycount;assert(scanf("%d%d",&n,&querycount)==2);
	if(1)
	{
		static int s[100001];
		for(int i=1;i<=n;i++)assert(scanf("%d",&s[i])==1);
		BST.Build(1,1,n,s);
	}
	while(querycount--)
	{
		static int type;assert(scanf("%d",&type)==1);
		if(type==1)
		{
			static int a,b;assert(scanf("%d%d",&a,&b)==2);
			BST.Modify(1,1,n,a,b);
		}
		else if(type==2)
		{
			static int l,r;assert(scanf("%d%d",&l,&r)==2);
			printf("%d\n",BST.Query(1,1,n,l,r));
		}
		else assert(0);
	}
	return 0;
}
