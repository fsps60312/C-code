#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
struct Tree
{
	static int s[400000];
	struct Sz
	{
		static void Build(const int id,const int l,const int r)
		{
			if(l==r){s[id]=2;return;}
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
			s[id]=s[id*2]+s[id*2+1];
		}
		static int Query(const int id,const int l,const int r,const bool is_left,const int rank)
		{
			assert(rank>=0&&rank<s[id]);
			if(is_left&&rank==0)return l;
			if(!is_left&&rank==s[id]-1)return r;
			const int mid=(l+r)/2;
			if(rank<s[id*2])return Query(id*2,l,mid,is_left,rank);
			else return Query(id*2+1,mid+1,r,is_left,rank-s[id*2]);
		}
		static void Merge(const int id,const int l,const int r,const int bl,const int br)
		{
			if(r<bl||br<l)return;
			if(bl<=l&&r<=br)
			{
				s[id]=0;
				if(l==bl)s[id]++;
				if(r==br)s[id]++;
				return;
			}
			const int mid=(l+r)/2;
			Merge(id*2,l,mid,bl,br),Merge(id*2+1,mid+1,r,bl,br);
			s[id]=s[id*2]+s[id*2+1];
		}
	};
	struct Edge
	{
		static void Build(const int id,const int l,const int r)
		{
			if(l==r){s[id]=l;return;}
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
			s[id]=INF;
		}
		static void Query(const int id,const int l,const int r,const int bl,const int br,set<int>&et,const int val)
		{
			if(r<bl||br<l)return;
			if(s[id]!=INF){assert(bl<=l&&r<=br),et.insert(s[id]),s[id]=val;return;}
			const int mid=(l+r)/2;
			Query(id*2,l,mid,bl,br,et,val),Query(id*2+1,mid+1,r,bl,br,et,val);
			if(s[id*2]==s[id*2+1])s[id]=s[id*2];
		}
	};
};
int Tree::s[400000]={};
struct Segment
{
	int l,r;
	Segment(){}
	Segment(const int _l,const int _r):l(_l),r(_r){}
};
vector<Segment>SEGMENT;
int N,C,R,S[99999];
set<int>ET[200000];
vector<int>FA[200000];
void BuildFA(const int u,const int fa)
{
	FA[u].clear();
	for(int cur=fa,i=0;;cur=FA[cur][i++])
	{
		FA[u].push_back(cur);
		if(i>=(int)FA[cur].size())break;
	}
	for(const int nxt:ET[u])BuildFA(nxt,u);
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf(3,"%d%d%d",&N,&C,&R);
	for(int i=0;i+1<N;i++)scanf(1,"%d",&S[i]);
	Tree::s[1]=0;
	Tree::Sz::Build(1,0,N-1);
	SEGMENT.clear();
	for(int i=0,s,e;i<C;i++)
	{
		scanf(2,"%d%d",&s,&e);
		const int l=Tree::Sz::Query(1,0,N-1,true,s*2),r=Tree::Sz::Query(1,0,N-1,false,e*2+1);
		SEGMENT.push_back(Segment(l,r));
		Tree::Sz::Merge(1,0,N-1,l,r);
	}
	for(int i=0;i<N+C;i++)ET[i].clear();
	Tree::Edge::Build(1,0,N-1);
	for(int i=0;i<C;i++)
	{
		const Segment &s=SEGMENT[i];
		Tree::Edge::Query(1,0,N-1,s.l,s.r,ET[i+N],i);
	}
	static int deg[200000];
	for(int i=0;i<N+C;i++)deg[i]=0;
	for(int i=0;i<N+C;i++)for(const int nxt:ET[i])deg[nxt]++;
	for(int i=0;i<N+C;i++)if(deg[i]==0)for(const int nxt:ET[i])BuildFA(nxt,i);
	for(int i=0;i<N;i++)
	{
		
	}
	return 0;
}
