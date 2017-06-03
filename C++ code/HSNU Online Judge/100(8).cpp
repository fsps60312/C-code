#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
int N;
vector<int>ET[100000];
int PRE[100000],LOW[100000],SCC[100000],PRE_CNT,SCC_CNT;
stack<int>STK;
void Dfs(const int u)
{
	STK.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(int i=0;i<ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(!PRE[nxt])
		{
			Dfs(nxt);
			LOW[u]=min(LOW[u],LOW[nxt]);
		}
		else if(SCC[nxt]==-1)LOW[u]=min(LOW[u],PRE[nxt]);
	}
	if(PRE[u]==LOW[u])
	{
		while(STK.top()!=u)
		{
			SCC[STK.top()]=SCC_CNT;
			STK.pop();
		}
		SCC[u]=SCC_CNT++;
		STK.pop();
	}
}
vector<int>EA[100000];
LL SCC_SZ[100000];
struct Block
{
	int cnt,u;
	bool operator<(const Block &b)const{return cnt<b.cnt;}
}BLOCK[100000];
bool ANS[100000];
void Solve()
{
	for(int i=0;i<SCC_CNT;i++)EA[i].clear(),SCC_SZ[i]=0LL,BLOCK[i].cnt=0,BLOCK[i].u=i;
	for(int i=0;i<N;i++)
	{
		SCC_SZ[SCC[i]]++;
		for(int j=0;j<ET[i].size();j++)
		{
			if(SCC[i]==SCC[ET[i][j]])continue;
			EA[SCC[i]].push_back(SCC[ET[i][j]]);
		}
	}
	for(int i=0;i<SCC_CNT;i++)
	{
		sort(EA[i].begin(),EA[i].end());
		for(int l=0;l<EA[i].size();)
		{
			const int to=EA[i][l];
			int r=l;
			for(;r<EA[i].size()&&EA[i][r]==to;r++);
			if((LL)(r-l)==SCC_SZ[i]*SCC_SZ[to])BLOCK[to].cnt++;
			l=r;
		}
	}
	sort(BLOCK,BLOCK+SCC_CNT);
	for(int i=0;i<SCC_CNT;i++)ANS[i]=true;
//	printf("SCC_CNT=%d\n",SCC_CNT);
//	for(int i=0;i<N;i++)printf(" %d",SCC[i]);puts("");
//	for(int i=0;i<SCC_CNT;i++)printf("u=%d,cnt=%d\n",BLOCK[i].u,BLOCK[i].cnt);
	for(int i=0;i<SCC_CNT;i++)assert(BLOCK[i].cnt<=i);
	for(int i=SCC_CNT-1;i>=1&&BLOCK[i].cnt==i;i--)ANS[BLOCK[i].u]=false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		static int cnt;scanf("%d",&cnt);
		while(cnt--)
		{
			static int v;scanf("%d",&v);
			v--;ET[i].push_back(v);
		}
	}
	for(int i=0;i<N;i++)PRE[i]=0,SCC[i]=-1;
	PRE_CNT=SCC_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i);
	Solve();
	int ans=0;
	for(int i=0;i<N;i++)if(ANS[SCC[i]])ans++;
	printf("%d",ans);
	for(int i=0;i<N;i++)if(ANS[SCC[i]])printf(" %d",i+1);
	puts("");
	return 0;
}
