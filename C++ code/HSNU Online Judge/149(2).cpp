#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
struct Bst
{
	vector<int>tag,mn;
	int GetMaxSz(const int id,const int l,const int r)
	{
		if(l==r)return id;
		const int mid=(l+r)/2;
		return max(GetMaxSz(id*2,l,mid),GetMaxSz(id*2+1,mid+1,r));
	}
	void Build(const int id,const int l,const int r)
	{
		tag[id]=mn[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Maintain(const int id){mn[id]=min(mn[id*2],mn[id*2+1]);}
	void PutDown(const int id){tag[id*2]+=tag[id],mn[id*2]+=tag[id],tag[id*2+1]+=tag[id],mn[id*2+1]+=tag[id],tag[id]=0;}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int v)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){tag[id]+=v,mn[id]+=v;return;}
		PutDown(id);
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,v),Modify(id*2+1,mid+1,r,bl,br,v);
		Maintain(id);
	}
	void Maintain(const int id,const int l,const int r)
	{
		if(l==r)
		{
			if(mn[id]==1)tag[id]--,mn[id]--;
			else assert(mn[id]<=0);
			return;
		}
		PutDown(id);
		const int mid=(l+r)/2;
		if(mn[id*2+1]==1)tag[id*2+1]--,mn[id*2+1]--,Maintain(id*2,l,mid);
		else assert(mn[id*2+1]<=0),Maintain(id*2+1,mid+1,r);
		Maintain(id);
	}
	void Output(const int id,const int l,const int r,vector<int>&ans)
	{
		if(l==r){assert(tag[id]==mn[id]),ans.push_back(tag[id]);return;}
		PutDown(id);
		const int mid=(l+r)/2;
		Output(id*2,l,mid,ans),Output(id*2+1,mid+1,r,ans);
	}
}SLOPE;
int N,M,S[3000000];
map<int,int>IDX;
vector<int>RIDX;
LL Solve()
{
	LL y=0LL;
	for(int i=0;i<N;i++)y+=S[i];
	vector<int>slopes;
	SLOPE.Output(1,0,M-2,slopes);
	for(int i=0;i<M-1;i++)
	{
		const LL v=(LL)slopes[i]*(LL)(RIDX[i+1]-RIDX[i]);
		if(v<0LL)y+=v;
		else return y;
	}
	return y;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	IDX.clear(),RIDX.clear();
	IDX[0]=-1; 
	for(int i=0;i<N;i++)scanf(1,"%d",&S[i]),IDX[S[i]]=-1;
	if(true)
	{
		int cnt=0;
		for(auto &it:IDX)it.second=cnt++,RIDX.push_back(it.first);
	}
	M=IDX.size();
	if(true)
	{
		const int sz=SLOPE.GetMaxSz(1,0,M-2);
		SLOPE.tag.resize(sz),SLOPE.mn.resize(sz);
	}
	SLOPE.Build(1,0,M-2);
	for(int i=0;i<N;i++)
	{
		SLOPE.Modify(1,0,M-2,0,IDX[S[i]]-1,-1);
		SLOPE.Modify(1,0,M-2,IDX[S[i]],M-2,1);
		SLOPE.Maintain(1,0,M-2);
	}
	assert(M==(int)IDX.size());
	IDX.clear();
	map<int,int>().swap(IDX);
	printf("%lld\n",Solve());
	return 0;
}
