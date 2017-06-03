#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int BSTSZ=600000;
typedef long long LL;
int N,D;
LL K;
LL max(const LL &a,const LL &b,const LL &c){return max(max(a,b),c);}
struct Bst
{
	int *INFO[BSTSZ*2],SZ;
	LL SUM_BASE[BSTSZ],LMX_BASE[BSTSZ],RMX_BASE[BSTSZ],CMX_BASE[BSTSZ],TMP;
	LL &Sum(const int id){return INFO[id]?SUM_BASE[*INFO[id]]:TMP=0LL;}
	LL &Lmx(const int id){return INFO[id]?LMX_BASE[*INFO[id]]:TMP=0LL;}
	LL &Rmx(const int id){return INFO[id]?RMX_BASE[*INFO[id]]:TMP=0LL;}
	LL &Cmx(const int id){return INFO[id]?CMX_BASE[*INFO[id]]:TMP=0LL;}
	void Maintain(const int id)
	{
		Sum(id)=Sum(id*2)+Sum(id*2+1);
		Lmx(id)=max(Lmx(id*2),Sum(id*2)+Lmx(id*2+1));
		Rmx(id)=max(Rmx(id*2)+Sum(id*2+1),Rmx(id*2+1));
		Cmx(id)=max(Cmx(id*2),Cmx(id*2+1),Rmx(id*2)+Lmx(id*2+1));
	}
	void Build(const int id,const int l,const int r,const LL &v,const int bound)
	{
		INFO[id]=(l<=bound?new int(SZ++):NULL);
		if(l==r){Sum(id)=v;Lmx(id)=Rmx(id)=Cmx(id)=0LL;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,v,bound),Build(id*2+1,mid+1,r,v,bound);
		Maintain(id);
	}
	void Modify(const int id,const int l,const int r,const int loc,const LL &v)
	{
		if(l==r){assert(r==loc);Sum(id)+=v;Lmx(id)=Rmx(id)=Cmx(id)=max(0LL,Sum(id));return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(id*2,l,mid,loc,v);
		else Modify(id*2+1,mid+1,r,loc,v);
		Maintain(id);
	}
	LL Query(const int id,const int l,const int r,const int bl,const int br,const int type)
	{
		if(r<bl||br<l)return 0LL;
		if(bl<=l&&r<=br)
		{
			switch(type)
			{
				case 0:return Sum(id);
				case 1:return Lmx(id);
				case 2:return Rmx(id);
				case 3:return Cmx(id);
				default:assert(0);return -1LL; 
			}
		}
		const int mid=(l+r)/2;
		switch(type)
		{
			case 0:return Query(id*2,l,mid,bl,br,0)+Query(id*2+1,mid+1,r,bl,br,0);
			case 1:return max(Query(id*2,l,mid,bl,br,1),Query(id*2,l,mid,bl,br,0)+Query(id*2+1,mid+1,r,bl,br,1));
			case 2:return max(Query(id*2,l,mid,bl,br,2)+Query(id*2+1,mid+1,r,bl,br,0),Query(id*2+1,mid+1,r,bl,br,2));
			case 3:return max(Query(id*2,l,mid,bl,br,3),Query(id*2+1,mid+1,r,bl,br,3),Query(id*2,l,mid,bl,br,2)+Query(id*2+1,mid+1,r,bl,br,1));
			default:assert(0);return -1LL;
		}
	}
}BST;
void Resize(vector<LL>&s,const int sz){s.reserve(sz);while((int)s.size()<sz)s.push_back(0LL);}
int main()
{
//	freopen("in.txt","r",stdin);
	static int eventcount;
	scanf(4,"%d%d%lld%d",&N,&eventcount,&K,&D);
	BST.SZ=0;
	BST.Build(1,1,N+D,-K,N);
	while(eventcount--)
	{
		static int r,x;scanf(2,"%d%d",&r,&x);
		BST.Modify(1,1,N+D,r,x);
		const LL &result=BST.Query(1,1,N+D,1,N,3);
		puts(result<=K*D?"TAK":"NIE");
	}
	return 0;
}
