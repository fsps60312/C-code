#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct SegTree
{
	struct Node
	{
		int sum,lmx,mmx,rmx;
		Node(){}
		Node(const int _v):sum(_v),lmx(_v),mmx(_v),rmx(_v){}
		void Maintain(const Node &l,const Node &r)
		{
			if(l.sum==INF||r.sum==INF)
			{
				(*this)=(l.sum!=INF?l:r);
				return;
			}
			sum=l.sum+r.sum;
			lmx=max(l.lmx,l.sum+r.lmx);
			rmx=max(r.rmx,l.rmx+r.sum);
			mmx=max(l.rmx+r.lmx,max(l.mmx,r.mmx));
		}
	}data[200000];
	void Build(const int id,const int l,const int r,const int *s)
	{
		if(l==r){data[id]=Node(s[r]);return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,s),Build(id*2+1,mid+1,r,s);
		data[id].Maintain(data[id*2],data[id*2+1]);
	}
	void Modify(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r){data[id]=Node(val);return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(id*2,l,mid,loc,val);
		else Modify(id*2+1,mid+1,r,loc,val);
		data[id].Maintain(data[id*2],data[id*2+1]);
	}
	Node Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return Node(INF);
		if(bl<=l&&r<=br)return data[id];
		const int mid=(l+r)/2;
		Node ans;
		ans.Maintain(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
		return ans;
	}
}SEG_TREE;
int N,S[50000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	SEG_TREE.Build(1,0,N-1,S);
	int querycount;scanf("%d",&querycount);
	for(int type,x,y;querycount--;)
	{
		scanf("%d%d%d",&type,&x,&y);
		if(type==0)SEG_TREE.Modify(1,0,N-1,x-1,y);
		if(type==1)printf("%d\n",SEG_TREE.Query(1,0,N-1,x-1,y-1).mmx);
	}
	return 0;
}
