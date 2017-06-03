#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<set>
#include<stack>
#include<map>
using namespace std;
int N;
bool ANS[100000];
vector<int>EO[100000];
int PRE[100000],LOW[100000],PRE_CNT,BCC[100000],BCC_CNT;
stack<int>STK;
int IN[100000];
int GetHead()
{
	for(int i=0;i<BCC_CNT;i++)IN[i]=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<EO[i].size();j++)
		{
			if(BCC[i]==BCC[EO[i][j]])continue;
			IN[BCC[EO[i][j]]]++;
		}
	}
	int ans=-1;
	for(int i=0;i<BCC_CNT;i++)
	{
		if(IN[i]==0)
		{
			if(ans!=-1)return -1;
			ans=i;
		}
	}
	assert(ans!=-1);
	return ans;
}
void Dfs(const int u)
{
	STK.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(int i=0;i<EO[u].size();i++)
	{
		const int nxt=EO[u][i];
//		if(nxt==fa)continue;
		if(!PRE[nxt])
		{
			Dfs(nxt);
			LOW[u]=min(LOW[u],LOW[nxt]);
		}
		else if(BCC[nxt]==-1)LOW[u]=min(LOW[u],PRE[nxt]);
	}
	if(LOW[u]==PRE[u])
	{
		while(STK.top()!=u)
		{
			const int i=STK.top();STK.pop();
			BCC[i]=BCC_CNT;
		}
		STK.pop();
		BCC[u]=BCC_CNT++;
	}
}
void Solve()
{
	for(int i=0;i<N;i++)ANS[i]=true,BCC[i]=-1,PRE[i]=0;
	PRE_CNT=BCC_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i);
	int head=GetHead();
	for(int i=0;i<N;i++)if(BCC[i]!=head)ANS[i]=false;
}
int VIS[100000],KASE;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)VIS[i]=0,EO[i].clear();
	KASE=0;
	for(int i=0,cnt,v;i<N;i++)
	{
		scanf("%d",&cnt);
		KASE++;
		while(cnt--)
		{
			scanf("%d",&v);
			v--;
			VIS[v]=KASE;
		}
		for(int j=0;j<N;j++)if(VIS[j]!=KASE)EO[j].push_back(i);
	}
	Solve();
	int ans=0;
	for(int i=0;i<N;i++)if(ANS[i])ans++;
	printf("%d",ans);
	for(int i=0;i<N;i++)if(ANS[i])printf(" %d",i+1);
	puts("");
	return 0;
}
