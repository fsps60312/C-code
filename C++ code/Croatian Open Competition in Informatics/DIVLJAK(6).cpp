#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct SegTree
{
	int n;
	int sum[2000002];
	void Build(const int _n){assert(n<=2000001);n=_n;for(int i=1;i<=n;i++)sum[i]=0;}
	void Modify(int i,const int val){i++;while(i<=n)sum[i]+=val,i+=(i&(-i));}
	int Query(int i){i++;int ans=0;while(i)ans+=sum[i],i-=(i&(-i));return ans;}
	int Query(int *p){return Query(p[1])-Query(p[0]-1);}
};
struct TreeSequence
{
	int head[2000001],next[2000001],deps[2000001],nsz;
	int parents[2000001][25],psz[2000001];
	int segs[2000001][2];
	void Clear(const int n)
	{
		assert(n<=2000001);
		nsz=0;
		for(int i=0;i<n;i++)head[i]=next[i]=-1;
	}
	void AddEdge(const int a,const int b)
	{
		next[b]=head[a],head[a]=b;//because it's a tree
	}
	void Build(const int u,const int parent,const int dep,int &clock)
	{
		deps[u]=dep;
		int &tpsz=psz[u]=0;
		if(parent!=-1)
		{
			for(int cur=parent,i=0;;cur=parents[cur][i++])
			{
				parents[u][tpsz++]=cur;
				if(i>=psz[cur])break;
			}
		}
		segs[u][0]=clock;
		for(int cur=head[u];cur!=-1;cur=next[cur])Build(cur,u,dep+1,clock);
		segs[u][1]=clock++;
	}
	int LowestCommonAncestor(int a,int b)
	{
		if(deps[a]<deps[b])swap(a,b);
		for(int i=0,dis=deps[a]-deps[b];(1<<i)<=dis;i++)if(dis&(1<<i))a=parents[a][i];
		assert(deps[a]==deps[b]);
		if(a==b)return a;
		for(int i=24;i>=0;i--)if((1<<i)<=deps[a]&&parents[a][i]!=parents[b][i])a=parents[a][i],b=parents[b][i];
		assert(parents[a][0]==parents[b][0]);
		return parents[a][0];
	}
	int *operator[](const int i){return segs[i];}
};
struct AC_Automaton
{
	int sz;
	int head[2000001],next[2000001];
	char charactor[2000001];
	bool is_end[2000001];
	void Clear(){sz=1;head[0]=-1,is_end[0]=false;}
	int Find(const int u,const char c)
	{
		for(int cur=head[u];cur!=-1;cur=next[cur])if(charactor[cur]==c)return cur;
		return -1;
	}
	int GetNxt(const int u,const char c)
	{
		const int ans=Find(u,c);
		if(ans!=-1)return ans;
		head[sz]=-1;
		charactor[sz]=c;
		is_end[sz]=false;
		next[sz]=head[u];
		head[u]=sz;
		return sz++;
	}
	int Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]);
		is_end[u]=true;
		return u;
	}
	int fail[2000001];
	TreeSequence seq;
	SegTree seg_tree;
	void BuildFail()
	{
		fail[0]=0;
		static int q[2000001],l,r;l=0,r=-1;
		for(int cur=head[0];cur!=-1;cur=next[cur])fail[q[++r]=cur]=0;
		seq.Clear(sz);
		while(l<=r)
		{
			const int u=q[l++];
			seq.AddEdge(fail[u],u);
			for(int cur=head[u];cur!=-1;cur=next[cur])
			{
				int &f=fail[cur]=fail[u];
				while(f&&Find(f,charactor[cur])==-1)f=fail[f];
				f=max(0,Find(f,charactor[cur]));
				is_end[cur]|=is_end[f];
				q[++r]=cur;
			}
		}
		int tick=0;
		seq.Build(0,-1,0,tick);
		assert(tick==sz);
		seg_tree.Build(sz);
	}
	void Match(const char *str)
	{
		int u=0;
		static int nodes[2000001],nodes_size;nodes_size=0;
		for(int i=0;str[i];i++)
		{
			while(u&&Find(u,str[i])==-1)u=fail[u];
			u=max(0,Find(u,str[i]));
			if(is_end[u])nodes[nodes_size++]=u;
		}
		if(nodes_size==0)return;
		sort(nodes,nodes+nodes_size,[this](const int a,const int b)->bool{return seq[a][1]<seq[b][1];});
		seg_tree.Modify(seq[nodes[0]][1],1);
		for(int i=1;i<nodes_size;i++)
		{
			seg_tree.Modify(seq[nodes[i]][1],1);
			seg_tree.Modify(seq[seq.LowestCommonAncestor(nodes[i-1],nodes[i])][1],-1);
		}
	}
	int Query(const int u){return seg_tree.Query(seq[u]);}
}AC;
int N;
#include<vector>
int main()
{
//	freopen("inn.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		AC.Clear();
		vector<int>nodes;
		for(int i=0;i<N;i++)
		{
			static char str[2000001];
			scanf("%s",str);
			nodes.push_back(AC.Insert(str));
		}
		AC.BuildFail();
		int querycount;scanf("%d",&querycount);
		for(int type,val;querycount--;)
		{
			scanf("%d",&type);
			if(type==1)
			{
				static char str[2000001];
				scanf("%s",str);
				AC.Match(str);
			}
			else if(type==2)
			{
				scanf("%d",&val);
				printf("%d\n",AC.Query(nodes[--val]));
			}
			else assert(0);
		}
		break;
	}
	return 0;
}
