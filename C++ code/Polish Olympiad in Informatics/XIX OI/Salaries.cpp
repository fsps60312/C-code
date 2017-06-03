#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
struct SegTree
{
	int MN[4000000],TAG[4000000];
	void Build(const int id,const int l,const int r)
	{
		MN[id]=INF;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void PutDown(const int id)
	{
		if(!TAG[id])return;
		TAG[id*2]+=TAG[id],TAG[id*2+1]+=TAG[id];
		MN[id*2]+=TAG[id],MN[id*2+1]+=TAG[id];
		TAG[id]=0;
	}
	void Maintain(const int id)
	{
		assert(!TAG[id]);
		MN[id]=min(MN[id*2],MN[id*2+1]);
	}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int v)
	{
		if(bl<=l&&r<=br){MN[id]+=v,TAG[id]+=v;return;}
		if(r<bl||br<l)return;
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,v),Modify(id*2+1,mid+1,r,bl,br,v);
		Maintain(id);
	}
	void Set(const int id,const int l,const int r,const int loc,const int v)
	{
		if(l==r){MN[id]=v;return;}
		const int mid=(l+r)/2;
		PutDown(id);
		if(loc<=mid)Set(id*2,l,mid,loc,v);
		else Set(id*2+1,mid+1,r,loc,v);
		Maintain(id);
	}
}ST;
struct Bit
{
	int S[1000001];
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i,const int v){while(i<=N)S[i]+=v,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=S[i],i-=(i&(-i));return ans;}
}BIT;
int N,BOSS[1000001],SALARY[1000001];
int SZ[1000001];
void BuildSZ()
{
	static int deg[1000001];
	for(int i=1;i<=N;i++)deg[i]=SZ[i]=0;
	for(int i=1;i<=N;i++)if(BOSS[i]!=i)deg[BOSS[i]]++;
	queue<int>q;
	for(int i=1;i<=N;i++)if(ET[i].empty())SZ[i]++,q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(BOSS[u]==u){assert(q.empty());break;}
		SZ[BOSS[u]]+=SZ[u];
		if(!--deg[BOSS[u]])q.push(BOSS[u]);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d%d",&BOSS[i],&SALARY[i]);
	BuildSZ();
	ST.Build(1,1,N);
	for(int i)
	return 0;
}
