#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct SegTree
{
	int frog[800000];
	void Build(const int id,const int l,const int r)
	{
		frog[id]=INF;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){frog[id]=val;return;}
		const int mid=(l+r)/2;
		getmin(frog[id*2],frog[id]);
		getmin(frog[id*2+1],frog[id]);
		Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r){assert(loc==r);return frog[r];}
		const int mid=(l+r)/2;
		if(loc<=mid)return Query(id*2,l,mid,loc);
		else return Query(id*2+1,mid+1,r,loc);
	}
}SET_TREE;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		
	}
	return 0;
}
