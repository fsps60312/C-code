#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<queue>
using namespace std;
struct SegTree
{
	int n;
	vector<int>sum;
	void Build(const int id,const int l,const int r)
	{
		while(id>=(int)sum.size())sum.push_back(0);
		sum[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _n){n=_n;Build(1,0,n-1);}
	void Add(const int id,const int l,const int r,const int loc)
	{
		sum[id]++;
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Add(id*2,l,mid,loc);
			else Add(id*2+1,mid+1,r,loc);
		}
	}
	void Add(const int loc){Add(1,0,n-1,loc);}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return 0;
		if(bl<=l&&r<=br)return sum[id];
		const int mid=(l+r)/2;
		return Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br);
	}
	int Query(const pair<int,int>&p){return Query(1,0,n-1,p.first,p.second);}
};
struct TreeSequence
{
	vector<vector<int> >et,parents;
	vector<pair<int,int> >segs;
	void Clear(const int n)
	{
		et.clear(),segs.clear(),parents.clear();
		et.resize(n),segs.resize(n),parents.resize(n);
	}
	void Build(const int u,const int parent,int &clock)
	{
		parents[u].clear();
		if(parent!=-1)
		{
			for(int cur=parent,i=0;;cur=parents[cur][i++])
			{
				parents[u].push_back(cur);
				if(i>=(int)parents[cur].size())break;
			}
		}
		segs[u].first=clock;
		for(const int nxt:et[u])Build(nxt,u,clock);
		segs[u].second=clock++;
	}
	const pair<int,int>&operator[](const int i)const{return segs[i];}
};
struct AC_Automaton
{
	int sz;
	vector<map<char,int> >ch;
	vector<bool>is_end;
	void Clear(){sz=0;ch.clear(),is_end.clear();Expand();}
	void Expand(){ch.push_back(map<char,int>()),is_end.push_back(false);sz++;}
	int GetNxt(const int u,const char c)
	{
		const auto &it=ch[u].find(c);
		if(it==ch[u].end()){Expand();return ch[u][c]=sz-1;}
		else return it->second;
	}
	int Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]);
		is_end[u]=true;
		return u;
	}
	vector<int>fail;
	void BuildFail()
	{
		fail.clear(),fail.resize(sz,0);
		queue<int>q;
		for(const auto &it:ch[0])q.push(it.second);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(const auto &it:ch[u])
			{
				int &f=fail[it.second]=fail[u];
				while(f&&ch[f].find(it.first)==ch[f].end())f=fail[f];
				if(true)
				{
					const auto &iu=ch[f].find(it.first);
					if(iu!=ch[f].end())f=iu->second;
				}
				if(is_end[f])is_end[it.second]=true;
				q.push(it.second);
			}
		}
	}
	TreeSequence seq;
	SegTree seg_tree;
	void BuildFailTree()
	{
		seq.Clear(sz);
		for(int i=1;i<sz;i++)seq.et[fail[i]].push_back(i);
		int clock=0;
		seq.Build(0,-1,clock);
		assert(clock==sz);
		seg_tree.Build(sz);
	}
	void Match(const char *str)
	{
//		static int kase=0;kase++;
		int u=0;
		for(int i=0;str[i];i++)
		{
			while(u&&ch[u].find(str[i])==ch[u].end())u=fail[u];
			const auto it=ch[u].find(str[i]);
			if(it!=ch[u].end())u=it->second;
			if(is_end[u])seg_tree.Add(seq[u].second);
		}
	}
	int Query(const int u){return seg_tree.Query(seq[u]);}
}AC;
int N;
int main()
{
	freopen("in.txt","r",stdin);
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
		AC.BuildFailTree();
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
		puts("pass");
	}
	return 0;
}
