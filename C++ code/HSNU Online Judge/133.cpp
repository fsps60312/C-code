#include<cstdio>
#include<cassert>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
int N,D;
LL K;
LL max(const LL &a,const LL &b,const LL &c){return max(max(a,b),c);}
struct Bst
{
	vector<LL>sum,lmx,rmx,cmx;
	void Maintain(const int id)
	{
		sum[id]=sum[id*2]+sum[id*2+1];
		lmx[id]=max(lmx[id*2],sum[id*2]+lmx[id*2+1]);
		rmx[id]=max(rmx[id*2]+sum[id*2+1],rmx[id*2+1]);
		cmx[id]=max(cmx[id*2],cmx[id*2+1],rmx[id*2]+lmx[id*2+1]);
	}
	void Build(const int id,const int l,const int r,const LL &v,const int bound)
	{
		while((int)sum.size()<=id)sum.push_back(0LL),lmx.push_back(0LL),rmx.push_back(0LL),cmx.push_back(0LL);
		if(l==r){sum[id]=(r<=bound?v:0LL);lmx[id]=rmx[id]=cmx[id]=0LL;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,v,bound),Build(id*2+1,mid+1,r,v,bound);
		Maintain(id);
	}
	void Modify(const int id,const int l,const int r,const int loc,const LL &v)
	{
		if(l==r){assert(r==loc);sum[id]+=v;lmx[id]=rmx[id]=cmx[id]=max(0LL,sum[id]);return;}
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
				case 0:return sum[id];
				case 1:return lmx[id];
				case 2:return rmx[id];
				case 3:return cmx[id];
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
int main()
{
//	freopen("in.txt","r",stdin);
	static int eventcount;
	scanf(4,"%d%d%lld%d",&N,&eventcount,&K,&D);
	BST.Build(1,1,N+D,-K,N);
//	printf("sum=%lld\n",BST.Query(1,1,N+D,1,N+D,0));
	while(eventcount--)
	{
		static int r,x;scanf(2,"%d%d",&r,&x);
		BST.Modify(1,1,N+D,r,x);
		const LL &result=BST.Query(1,1,N+D,1,N,3);
//		printf("result=%lld\n",result);
		puts(result<=K*D?"TAK":"NIE");
	}
	return 0;
}
