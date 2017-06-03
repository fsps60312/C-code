#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int INF=2147483647;
struct SegTree1
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
	int GetLoc(const int id,const int l,const int r)
	{
		assert(MN[id]==0);
		if(l==r){MN[id]=INF;return r;}
		const int mid=(l+r)/2;
		PutDown(id);
		int ans;
		if(MN[id*2]==0)ans=GetLoc(id*2,l,mid);
		else ans=GetLoc(id*2+1,mid+1,r);
		Maintain(id);
		return ans;
	}
}ST1;
struct SegTree2
{
	int SUM[4000000];
	void Build(const int id,const int l,const int r)
	{
		SUM[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Modify(const int id,const int l,const int r,const int loc,const int v)
	{
		SUM[id]+=v;
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Modify(id*2,l,mid,loc,v);
			else Modify(id*2+1,mid+1,r,loc,v);
		}
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(bl<=l&&r<=br)return SUM[id];
		if(r<bl||br<l)return 0;
		const int mid=(l+r)/2;
		return Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br);
	}
}ST2;
int N,BOSS[1000001],SALARY[1000001];
int SZ[1000001];
vector<int>ET[1000001];
void BuildSZ()
{
	static int deg[1000001];
	for(int i=1;i<=N;i++)deg[i]=SZ[i]=0;
	for(int i=1;i<=N;i++)if(BOSS[i]!=i)deg[BOSS[i]]++,ET[BOSS[i]].push_back(i);
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
	for(int i=1;i<=N;i++)scanf("%d%d",&BOSS[i],&SALARY[i]);
	for(int i=1;i<=N;i++)if(BOSS[i]==i){if(SALARY[i]==0)SALARY[i]=N;break;}
	BuildSZ();
	ST2.Build(1,1,N);
	set<int>st2s;
	for(int i=1;i<=N;i++)ST2.Modify(1,1,N,i,1),st2s.insert(i);
	for(int i=1;i<=N;i++)if(SALARY[i]!=0)ST2.Modify(1,1,N,SALARY[i],-1),sts;
	ST1.Build(1,1,N);
	static int id[1000001];
	for(int i=1;i<=N;i++)
	{
		const int bs=SALARY[BOSS[i]];
		if(BOSS[i]!=i&&SALARY[i]==0&&bs!=0)ST1.Set(1,1,N,bs,ST2.Query(1,1,N,1,bs-1)-SZ[i]),id[bs]=i;
	}
	while(ST1.MN[1]==0)
	{
		const int u=id[ST1.GetLoc(1,1,N)];
		SALARY[u]=
	}
	assert(ST1.MN[1]>0);
	for(int i=1;i<=N;i++)printf("%d\n",SALARY[i]);
	return 0;
}
