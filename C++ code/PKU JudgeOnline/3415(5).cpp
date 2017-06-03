#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAX_EDGE=2000000;
void assert(bool valid){if(valid)return;for(;;);int *a=NULL;for(;;)delete a--;}
typedef long long LL;
struct SuffixAutomaton
{
	int HEAD[200000],NEXT[MAX_EDGE],VALUE[MAX_EDGE],NSZ;
	char CHAR[MAX_EDGE];
	int GREEN[200000],MAX_LEN[200000],COUNT[200000];
	int N;
	void Clear()
	{
		N=NSZ=0;
		NewNode(0);
	}
	void NewNode(const int max_len)
	{
		HEAD[N]=-1;
		GREEN[N]=-1,MAX_LEN[N]=max_len;
		COUNT[N]=0;
		N++;
	}
	int GetChild(const int u,const char c)
	{
		for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])if(CHAR[cur]==c)return VALUE[cur];
		return 0;
	}
	void AddChild(const int u,const char c,const int val)
	{
		NEXT[NSZ]=HEAD[u];
		HEAD[u]=NSZ;
		CHAR[NSZ]=c;
		VALUE[NSZ]=val;
		NSZ++;
	}
	bool SetChild(const int u,const char c,const int target_val,const int val)
	{
		for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])if(CHAR[cur]==c)
		{
			if(VALUE[cur]==target_val){VALUE[cur]=val;return true;}
			return false;
		}
		return false;
	}
	void Extend(int &last,const char c)
	{
		int cur=last;NewNode(MAX_LEN[last]+1);last=N-1;
		for(;cur!=-1&&!GetChild(cur,c);cur=GREEN[cur])AddChild(cur,c,last);
		if(cur==-1)GREEN[last]=0;
		else
		{
			const int pg=GetChild(cur,c);
			if(MAX_LEN[pg]==MAX_LEN[cur]+1)GREEN[last]=pg;
			else
			{
				NewNode(MAX_LEN[cur]+1);
				const int wish=N-1;
				for(;cur!=-1&&SetChild(cur,c,pg,wish);cur=GREEN[cur]);
				for(cur=HEAD[pg];cur!=-1;cur=NEXT[cur])AddChild(wish,CHAR[cur],VALUE[cur]);
				GREEN[wish]=GREEN[pg];
				GREEN[pg]=wish;
				GREEN[last]=wish;
			}
		}
		COUNT[last]++;
	}
	vector<int>ET[200000],PARENTS[200000];
	vector<LL>COSTS[200000];
	int DEPTH[200000];
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
				if((1<<i)>DEPTH[cur])break;
			}
		}
		for(vector<int>::iterator nxt=ET[u].begin();nxt!=ET[u].end();nxt++)BuildTree(*nxt,u,depth+1,counter);
	}
	void Build(const char *str)
	{
		Clear();
		for(int i=0,u=0;str[i];i++)Extend(u,str[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1;i<N;i++)ET[GREEN[i]].push_back(i);
		static int q[200000],l,r;l=0,r=-1;
		static int degree[200000];
		for(int i=0;i<N;i++)degree[i]=ET[i].size();
		for(int i=0;i<N;i++)if(!degree[i])q[++r]=i;
		while(l<=r)
		{
			const int u=q[l++];
			if(GREEN[u]!=-1)
			{
				COUNT[GREEN[u]]+=COUNT[u];
				if(!--degree[GREEN[u]])q[++r]=GREEN[u];
			}
		}
		for(int i=0;i<N;i++)assert(!degree[i]);
		int counter=0;
		BuildTree(0,-1,0,counter);
		assert(counter==N);
	}
	LL GetCostSum(int cur,const int max_len,const int low_limit)
	{
		if(max_len<low_limit)return 0;
		assert(GREEN[cur]!=-1);
		if(MAX_LEN[GREEN[cur]]<low_limit)return (LL)COUNT[cur]*(max_len-low_limit+1);
		LL ans=0;
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
		LL ans=0;
		for(int i=0,u=0,len=0;str[i];i++)
		{
			while(u&&!GetChild(u,str[i]))u=GREEN[u],len=MAX_LEN[u];
			if((u=GetChild(u,str[i]))!=0)len++;
			ans+=GetCostSum(u,len,low_limit);
		}
		return ans;
	}
}SAM;
int K;
char A[100001],B[100001];
int main()
{
//	assert(0);
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&K)==1&&K)
	{
		scanf("%s%s",A,B);
		SAM.Build(A);
		printf("%lld\n",SAM.Match(B,K));
	}
	return 0;
}
