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
		const int mid=(l+r)>>1;
		return max(GetMaxSz(id<<1,l,mid),GetMaxSz((id<<1)+1,mid+1,r));
	}
	inline void Maintain(const int id){mn[id]=min(mn[id<<1],mn[(id<<1)+1]);}
	inline void PutDown(const int id)
	{
		int &v=tag[id];
		tag[id<<1]+=v,mn[id<<1]+=v,tag[(id<<1)+1]+=v,mn[(id<<1)+1]+=v;
		v=0;
	}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int v)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){tag[id]+=v,mn[id]+=v;return;}
		PutDown(id);
		const int mid=(l+r)>>1;
		Modify(id<<1,l,mid,bl,br,v),Modify((id<<1)+1,mid+1,r,bl,br,v);
		Maintain(id);
	}
	void Maintain(const int id,const int l,const int r)
	{
		if(l==r)
		{
			if(mn[id]==1)tag[id]--,mn[id]--;
			return;
		}
		PutDown(id);
		const int mid=(l+r)>>1,rid=(id<<1)+1;
		if(mn[id*2+1]==1)tag[rid]--,mn[rid]--,Maintain(id<<1,l,mid);
		else assert(mn[rid]<=0),Maintain(rid,mid+1,r);
		Maintain(id);
	}
	void Output(const int id,const int l,const int r,int *ans)
	{
		if(l==r){ans[r]=tag[id];return;}
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
	int *slopes=new int[2999999];
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
		SLOPE.tag.clear(),SLOPE.mn.clear();
		SLOPE.tag.resize(sz+1,0),SLOPE.mn.resize(sz+1,0);
	}
	for(int i=0;i<N;i++)
	{
		const int idx=IDX[S[i]];
		SLOPE.Modify(1,0,M-2,0,idx-1,-1);
		SLOPE.Modify(1,0,M-2,idx,M-2,1);
		SLOPE.Maintain(1,0,M-2);
	}
	assert(M==(int)IDX.size());
	IDX.clear();
	map<int,int>().swap(IDX);
	printf("%lld\n",Solve());
	return 0;
}
