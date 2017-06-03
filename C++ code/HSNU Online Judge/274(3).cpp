#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
struct SzTree
{
	int SZ[400000];
	void Build(const int id,const int l,const int r)
	{
		if(l==r){SZ[id]=2;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		SZ[id]=SZ[id*2]+SZ[id*2+1];
	}
	int Query(const int id,const int l,const int r,const bool is_left,const int rank)
	{
		assert(rank>=0&&rank<SZ[id]);
		if(is_left&&rank==0)return l;
		if(!is_left&&rank==SZ[id]-1)return r;
		const int mid=(l+r)/2;
		if(rank<SZ[id*2])return Query(id*2,l,mid,is_left,rank);
		else return Query(id*2+1,mid+1,r,is_left,rank-SZ[id*2]);
	}
	void Merge(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br)
		{
			SZ[id]=0;
			if(l==bl)SZ[id]++;
			if(r==br)SZ[id]++;
			return;
		}
		const int mid=(l+r)/2;
		Merge(id*2,l,mid,bl,br),Merge(id*2+1,mid+1,r,bl,br);
		SZ[id]=SZ[id*2]+SZ[id*2+1];
	}
}SZTREE;
struct MxTree
{
	int MX[400000];
	void Build(const int id,const int l,const int r,const int *data_base)
	{
		if(l==r){MX[id]=data_base[r];return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,data_base),Build(id*2+1,mid+1,r,data_base);
		MX[id]=max(MX[id*2],MX[id*2+1]);
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return -INF;
		if(bl<=l&&r<=br)return MX[id];
		const int mid=(l+r)/2;
		return max(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
}ARCHER;
struct MxMnTree
{
	int MX[400000],MN[400000];
	void Build(const int id,const int l,const int r)
	{
		MX[id]=MN[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Maintain(const int id){MX[id]=max(MX[id*2],MX[id*2+1]),MN[id]=min(MN[id*2],MN[id*2+1]);}
	void PutDown(const int id)
	{
		if(MN[id]>MN[id*2])MN[id*2]=MN[id],getmax(MX[id*2],MN[id]);
		if(MN[id]>MN[id*2+1])MN[id*2+1]=MN[id],getmax(MX[id*2+1],MN[id]);
	}
	void Query(const int id,const int l,const int r,const int bl,const int br,int &mx,int &mn)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmax(mx,MX[id]),getmin(mn,MN[id]);return;}
		PutDown(id);
		const int mid=(l+r)/2;
		Query(id*2,l,mid,bl,br,mx,mn),Query(id*2+1,mid+1,r,bl,br,mx,mn);
	}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){MN[id]=MX[id]=val;return;}
		PutDown(id);
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
		Maintain(id);
	}
	int MaxPoint(const int id,const int l,const int r)
	{
		if(l==r)return r;
		PutDown(id);
		const int mid=(l+r)/2;
		if(MX[id*2]==MX[id])return MaxPoint(id*2,l,mid);
		else
		{
			assert(MX[id*2+1]==MX[id]);
			return MaxPoint(id*2+1,mid+1,r);
		}
	}
}ROUND;
struct Segment
{
	int l,r;
	Segment(){}
	Segment(const int _l,const int _r):l(_l),r(_r){}
};
vector<Segment>SEGMENT;
int N,C,R,S[99999];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(3,"%d%d%d",&N,&C,&R);
	for(int i=0;i+1<N;i++)scanf(1,"%d",&S[i]);
	SZTREE.Build(1,0,N-1);
	SEGMENT.clear();
	for(int i=0,s,e;i<C;i++)
	{
		scanf(2,"%d%d",&s,&e);
		const int l=SZTREE.Query(1,0,N-1,true,s*2),r=SZTREE.Query(1,0,N-1,false,e*2+1);
		SEGMENT.push_back(Segment(l,r));
		SZTREE.Merge(1,0,N-1,l,r);
	}
	ARCHER.Build(1,0,N-2,S);
	ROUND.Build(1,0,N-1);
	for(int i=C-1;i>=0;i--)
	{
		const Segment &seg=SEGMENT[i];
		assert(seg.l+1<=seg.r);
		const int oppo=ARCHER.Query(1,0,N-2,seg.l,seg.r-1);
		assert(oppo!=R);
		if(oppo>R)continue;
		int mx=-INF,mn=INF;
		ROUND.Query(1,0,N-1,seg.l,seg.r,mx,mn);
		assert(mx==mn);
		ROUND.Modify(1,0,N-1,seg.l,seg.r,mx+1);
	}
	printf("%d\n",ROUND.MaxPoint(1,0,N-1));
	return 0;
}
