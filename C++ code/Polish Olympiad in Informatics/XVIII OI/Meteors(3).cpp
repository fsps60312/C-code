#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL SUM[1200000];
void Build(const int id,const int l,const int r)
{
	SUM[id]=0;
	if(l<r)
	{
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
}
void Modify(const int id,const int l,const int r,const int bl,const int br,const LL &val)
{
	if(r<bl||br<l)return;
	if(bl<=l&&r<=br){SUM[id]+=val;return;}
	const int mid=(l+r)/2;
	Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
}
LL Query(const int id,const int l,const int r,const int loc)
{
	if(l==r)return SUM[id];
	const int mid=(l+r)/2;
	if(loc<=mid)return SUM[id]+Query(id*2,l,mid,loc);
	else return SUM[id]+Query(id*2+1,mid+1,r,loc);
}
int N,M,K;
vector<int>SECTORS[300000];
LL GOAL[300000];
struct MeteorShower
{
	int l,r;
	LL a;
};
void Modify(const MeteorShower &ms,const LL &sign)
{
	if(ms.l<=ms.r)Modify(1,0,M-1,ms.l,ms.r,ms.a*sign);
	else Modify(1,0,M-1,ms.l,M-1,ms.a*sign),Modify(1,0,M-1,0,ms.r,ms.a*sign);
}
vector<MeteorShower>MS;
int ANS[300000];
void Solve(const int l,const int r,const vector<int>&states)
{
	if(l==r)
	{
		for(int i=0;i<(int)states.size();i++)ANS[states[i]]=r;
		return;
	}
	const int mid=(l+r)/2;
	for(int i=l;i<=mid;i++)Modify(MS[i],1);
	vector<int>left_states,right_states;
	for(int i=0;i<(int)states.size();i++)
	{
		const int s=states[i];
		LL sum=0;
		for(int j=0;j<(int)SECTORS[s].size();j++)sum+=Query(1,0,M-1,SECTORS[s][j]);
		(sum<GOAL[s]?right_states:left_states).push_back(s);
	}
	Solve(mid+1,r,right_states);
	for(int i=mid;i>=l;i--)Modify(MS[i],-1);
	Solve(l,mid,left_states);
	vector<int>().swap(left_states);
	vector<int>().swap(right_states);
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("met8b.in","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)SECTORS[i].clear();
	for(int i=0,v;i<M;i++)scanf("%d",&v),SECTORS[--v].push_back(i);
	for(int i=0;i<N;i++)scanf("%lld",&GOAL[i]);
	scanf("%d",&K);
	MS.clear();
	for(int i=0;i<K;i++)
	{
		static MeteorShower m;
		scanf("%d%d%lld",&m.l,&m.r,&m.a),m.l--,m.r--;
		MS.push_back(m);
	}
	vector<int>states;
	for(int i=0;i<N;i++)states.push_back(i);
	Build(1,0,M-1);
	Solve(0,K,states);
	vector<int>().swap(states);
	for(int i=0;i<N;i++)
	{
		if(ANS[i]==K)puts("NIE");
		else printf("%d\n",ANS[i]+1);
	}
	return 0;
}
