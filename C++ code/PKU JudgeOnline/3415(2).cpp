#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int CHARSET=52;
typedef long long LL;
//struct Tree
//{
//	int N;
//	void Clear(const int _N)
//	{
//		N=_N;
//	}
//};
struct SuffixAutomaton
{
	vector<int>EDGE[CHARSET],GREEN,MAX_LEN,COUNT;
	int N;
	void Clear()
	{
		for(int i=0;i<CHARSET;i++)EDGE[i].clear();
		GREEN.clear(),MAX_LEN.clear();
		COUNT.clear();
		N=0;
		NewNode(0);
	}
	void NewNode(const int max_len)
	{
		for(int i=0;i<CHARSET;i++)EDGE[i].push_back(0);
		GREEN.push_back(-1),MAX_LEN.push_back(max_len);
		COUNT.push_back(0);
		N++;
	}
	void Extend(int &last,const int c)
	{
		int cur=last;NewNode(MAX_LEN[last]+1);last=N-1;
		for(;cur!=-1&&!EDGE[c][cur];cur=GREEN[cur])EDGE[c][cur]=last;
		if(cur==-1)GREEN[last]=0;
		else
		{
			const int pg=EDGE[c][cur];
			if(MAX_LEN[pg]==MAX_LEN[cur]+1)GREEN[last]=pg;
			else
			{
				NewNode(MAX_LEN[cur]+1);
				const int wish=N-1;
				for(;cur!=-1&&EDGE[c][cur]==pg;cur=GREEN[cur])EDGE[c][cur]=wish;
				for(int i=0;i<CHARSET;i++)EDGE[i][wish]=EDGE[i][pg];
				GREEN[wish]=GREEN[pg];
				GREEN[pg]=wish;
				GREEN[last]=wish;
			}
		}
		COUNT[last]++;
	}
	int Id(const char a)
	{
		if(a>='a'&&a<='z')return a-'a';
		if(a>='A'&&a<='Z')return a-'A'+26;
		assert(0);return -1;
	}
	vector<vector<int> >ET,PARENTS;
	vector<vector<LL> >COSTS;
	vector<int>DEPTH;
	void ClearTree()
	{
		ET.clear();
		ET.resize(N),PARENTS.resize(N),COSTS.resize(N);
		DEPTH.resize(N);
	}
	void BuildTree(const int u,const int parent,const int depth,int &counter)
	{
		counter++;
		DEPTH[u]=depth;
		PARENTS[u].clear(),COSTS[u].clear();
		if(parent!=-1)
		{
			int cur=parent;
			LL cost=(LL)COUNT[cur]*(MAX_LEN[cur]-(cur==0?-1:MAX_LEN[GREEN[cur]]));
			for(int i=0;;cost+=COSTS[cur][i],cur=PARENTS[cur][i],i++)
			{
				PARENTS[u].push_back(cur);
				COSTS[u].push_back(cost);
				if(i>=(int)PARENTS[cur].size())break;
			}
		}
		for(const int nxt:ET[u])BuildTree(nxt,u,depth+1,counter);
	}
	void Build(const char *str)
	{
		Clear();
		for(int i=0,u=0;str[i];i++)Extend(u,Id(str[i]));
		ClearTree();
		for(int i=1;i<N;i++)ET[GREEN[i]].push_back(i);
		queue<int>q;
		int *degree=new int[N];
		for(int i=0;i<N;i++)degree[i]=ET[i].size();
		for(int i=0;i<N;i++)if(!degree[i])q.push(i);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			if(GREEN[u]!=-1)
			{
				COUNT[GREEN[u]]+=COUNT[u];
				if(!--degree[GREEN[u]])q.push(GREEN[u]);
			}
		}
		for(int i=0;i<N;i++)assert(!degree[i]);
		delete[]degree;
		if(true){int counter=0;BuildTree(0,-1,0,counter);assert(counter==N);}
	}
	LL GetCostSum(int cur,const int max_len,const int low_limit)
	{
		if(max_len<low_limit)return 0LL;
		if(MAX_LEN[GREEN[cur]]<low_limit)return (LL)COUNT[cur]*(max_len-low_limit+1);
		LL ans=0LL;
		ans+=(LL)COUNT[cur]*(max_len-MAX_LEN[GREEN[cur]]);
		for(int i=30;i>=0;i--)if((1<<i)<=DEPTH[cur]&&MAX_LEN[PARENTS[cur][i]]>=low_limit)
		{
			ans+=COSTS[cur][i];
			cur=PARENTS[cur][i];
		}
		ans-=(LL)COUNT[cur]*((low_limit-1)-(MAX_LEN[GREEN[cur]]+1)+1);
		return ans;
	}
	LL Match(const char *str,const int low_limit)
	{
		LL ans=0LL;
		for(int i=0,u=0,len=0;str[i];i++)
		{
			const int c=Id(str[i]);
			while(u&&!EDGE[c][u])u=GREEN[u],len=MAX_LEN[u];
			if(EDGE[c][u])u=EDGE[c][u],len++;
			ans+=GetCostSum(u,len,low_limit);
		}
		return ans;
	}
}SAM;
int K;
char A[100001],B[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&K)==1&&K)
	{
		scanf("%s%s",A,B);
		SAM.Build(A);
		printf("%lld\n",SAM.Match(B,K));
	}
	return 0;
}
