#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int CHARSET=52;
typedef long long LL;
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
	void Build(const char *str)
	{
		Clear();
		for(int i=0,u=0;str[i];i++)Extend(u,Id(str[i]));
		queue<int>q;
		int *degree=new int[N];
		for(int i=0;i<N;i++)degree[i]=0;
		for(int i=1;i<N;i++)degree[GREEN[i]]++;
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
	}
	LL GetCostSum(int cur,const int max_len,const int low_limit)
	{
		if(max_len<low_limit)return 0LL;
		return GetCostSum(GREEN[cur],MAX_LEN[GREEN[cur]],low_limit)+(LL)COUNT[cur]*(max_len-max(MAX_LEN[GREEN[cur]]+1,low_limit)+1);
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
