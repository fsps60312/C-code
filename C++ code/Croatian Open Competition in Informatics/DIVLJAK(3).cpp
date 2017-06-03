#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#define PRINT_RUN_TIME
#ifdef PRINT_RUN_TIME
#include<ctime>
#endif
using namespace std;
struct SegTree
{
	int n;
	vector<int>sum;
	void Build(const int _n){n=_n;sum.resize(n+1);for(int i=1;i<=n;i++)sum[i]=0;}
	void Modify(int i,const int val){i++;while(i<=n)sum[i]+=val,i+=(i&(-i));}
	int Query(int i){i++;int ans=0;while(i)ans+=sum[i],i-=(i&(-i));return ans;}
	int Query(const pair<int,int>&p){return Query(p.second)-Query(p.first-1);}
};
struct TreeSequence
{
	vector<vector<int> >et,parents;
	vector<pair<int,int> >segs;
	vector<int>deps;
	void Clear(const int n)
	{
		et.clear(),segs.clear(),parents.clear(),deps.clear();
		et.resize(n),segs.resize(n),parents.resize(n),deps.resize(n);
	}
	void Build(const int u,const int parent,const int dep,int &clock)
	{
		deps[u]=dep;
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
		for(const int nxt:et[u])Build(nxt,u,dep+1,clock);
		segs[u].second=clock++;
	}
	int LowestCommonAncestor(int a,int b)
	{
		if(deps[a]<deps[b])swap(a,b);
		for(int i=0,dis=deps[a]-deps[b];(1<<i)<=dis;i++)if(dis&(1<<i))a=parents[a][i];
		assert(deps[a]==deps[b]);
		if(a==b)return a;
		for(int i=30;i>=0;i--)if((1<<i)<=deps[a]&&parents[a][i]!=parents[b][i])a=parents[a][i],b=parents[b][i];
		assert(parents[a][0]==parents[b][0]);
		return parents[a][0];
	}
	const pair<int,int>&operator[](const int i)const{return segs[i];}
};
struct AC_Automaton
{
	int ch_buffer[2000001*26],*newch;
	int sz;
	vector<int*>ch;
	vector<bool>is_end;
	void Clear(){sz=0,newch=ch_buffer;ch.clear(),is_end.clear();Expand();}
	void Expand()
	{
		for(int i=0;i<26;i++)newch[i]=0;
		ch.push_back(newch),newch+=26;
		is_end.push_back(false);
		sz++;
	}
	int GetNxt(const int u,const int c)
	{
		if(ch[u][c]==0)Expand(),ch[u][c]=sz-1;
		return ch[u][c];
	}
	int Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]-'a');
		is_end[u]=true;
		return u;
	}
	vector<int>fail;
	TreeSequence seq;
	SegTree seg_tree;
	void BuildFail()
	{
		clock_t start_time=clock();
		fail.clear(),fail.resize(sz,0);
		queue<int>q;
		for(int i=0;i<26;i++)if(ch[0][i])q.push(ch[0][i]);
		seq.Clear(sz);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			seq.et[fail[u]].push_back(u);
			for(int i=0;i<26;i++)if(ch[u][i])
			{
				int &f=fail[ch[u][i]]=fail[u];
				while(f&&ch[f][i]==0)f=fail[f];
				f=ch[f][i];
				if(is_end[f])is_end[ch[u][i]]=true;
				q.push(ch[u][i]);
			}
		}
		printf("aaa = %.3f\n",(double)(clock()-start_time)/CLOCKS_PER_SEC),start_time=clock();
		int tick=0;
		seq.Build(0,-1,0,tick);
		assert(tick==sz);
		printf("bbb = %.3f\n",(double)(clock()-start_time)/CLOCKS_PER_SEC),start_time=clock();
		seg_tree.Build(sz);
		printf("ccc = %.3f\n",(double)(clock()-start_time)/CLOCKS_PER_SEC),start_time=clock();
	}
	void Match(const char *str)
	{
//		static int kase=0;kase++;
		int u=0;
		vector<int>nodes;
		for(int i=0;str[i];i++)
		{
			while(u&&ch[u][str[i]-'a']==0)u=fail[u];
			u=ch[u][str[i]-'a'];
			if(is_end[u])nodes.push_back(u);
		}
		if(nodes.empty())return;
		sort(nodes.begin(),nodes.end(),[this](const int a,const int b)->bool{return seq[a].second<seq[b].second;});
		seg_tree.Modify(seq[nodes[0]].second,1);
		for(int i=1;i<(int)nodes.size();i++)
		{
			seg_tree.Modify(seq[nodes[i]].second,1);
			seg_tree.Modify(seq[seq.LowestCommonAncestor(nodes[i-1],nodes[i])].second,-1);
		}
	}
	int Query(const int u){return seg_tree.Query(seq[u]);}
}AC;
int N;
int main()
{
	freopen("inn.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
#ifdef PRINT_RUN_TIME
		clock_t start_time=clock();
#endif
		AC.Clear();
		vector<int>nodes;
		for(int i=0;i<N;i++)
		{
			static char str[2000001];
			scanf("%s",str);
			nodes.push_back(AC.Insert(str));
		}
		AC.BuildFail();
#ifdef PRINT_RUN_TIME
		printf("initialize time = %.3f s.\n",(double)(clock()-start_time)/CLOCKS_PER_SEC),start_time=clock();
#endif
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
#ifndef PRINT_RUN_TIME
				printf("%d\n",AC.Query(nodes[--val]));
#endif
			}
			else assert(0);
		}
#ifdef PRINT_RUN_TIME
		printf("run time = %.3f s.\n",(double)(clock()-start_time)/CLOCKS_PER_SEC);
#endif
	}
	return 0;
}
