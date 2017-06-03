#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
#include<cassert>
#include<queue>
using namespace std;
int N,M,S,P,OCASH[500000],CASH[500000],IN[500000],DP[500000];
bool OHUB[500000],HUB[500000],VIS[500000];
vector<int>OET[500000],ET[500000];
int LOW[500000],PRE[500000],PRE_CNT,SCC[500000],SCC_CNT;
stack<int>BEEN;
void Dfs(const int &u,const int &fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	BEEN.push(u);
	for(int i=0;i<OET[u].size();i++)
	{
		const int &j=OET[u][i];
		if(!PRE[j])
		{
			Dfs(j,u);
			LOW[u]=min(LOW[u],LOW[j]);
		}
		else if(SCC[j]==-1)LOW[u]=min(LOW[u],PRE[j]);
	}
	if(LOW[u]==PRE[u])
	{
		while(BEEN.top()!=u)SCC[BEEN.top()]=SCC_CNT,BEEN.pop();
		SCC[u]=SCC_CNT++,BEEN.pop();
	}
}
void Rebuild()
{
	for(int i=0;i<SCC_CNT;i++)CASH[i]=0,HUB[i]=false,ET[i].clear();
	for(int i=0;i<N;i++)
	{
		assert(SCC[i]>=0&&SCC[i]<SCC_CNT);
		CASH[SCC[i]]+=OCASH[i];
		HUB[SCC[i]]|=OHUB[i];
		for(int j=0;j<OET[i].size();j++)
		{
			const int &k=OET[i][j];
			if(SCC[i]!=SCC[k])ET[SCC[i]].push_back(SCC[k]);
		}
	}
	for(int i=0;i<SCC_CNT;i++)
	{
		sort(ET[i].begin(),ET[i].end());
		ET[i].resize(unique(ET[i].begin(),ET[i].end())-ET[i].begin());
	}
}
int Solve()
{
	for(int i=0;i<SCC_CNT;i++)IN[i]=0,DP[i]=0,VIS[i]=false;
	queue<int>q;
	q.push(S);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(VIS[u])continue;
		VIS[u]=true;
		for(int i=0;i<ET[u].size();i++)
		{
			const int &j=ET[u][i];
			IN[j]++;
			q.push(j);
		}
	}
	q.push(S);
	DP[S]=CASH[S];
	int ans=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(HUB[u])ans=max(ans,DP[u]);
		for(int i=0;i<ET[u].size();i++)
		{
			const int &j=ET[u][i];
			DP[j]=max(DP[j],DP[u]+CASH[j]);
			if(!--IN[j])q.push(j);
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)OET[i].clear(),OHUB[i]=false,PRE[i]=0,SCC[i]=-1;
		PRE_CNT=0;
		for(int i=0;i<M;i++)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			OET[a].push_back(b);
		}
		for(int i=0;i<N;i++)scanf("%d",&OCASH[i]);
		scanf("%d%d",&S,&P);
		S--;
		for(int i=0;i<P;i++)
		{
			static int u;scanf("%d",&u);
			u--;
			OHUB[u]=true;
		}
		for(int i=0;i<N;i++)if(PRE[i]==0)Dfs(i,-1);
		S=SCC[S];
		Rebuild();
//		for(int i=0;i<N;i++)
//		{
//			printf("%d:%d\n",i+1,SCC[i]);
//		}
//		for(int i=0;i<SCC_CNT;i++)
//		{
//			printf("%d,cash=%d,hub=%d\n",i,CASH[i],HUB[i]);
//			for(int j=0;j<ET[i].size();j++)printf(" %d",ET[i][j]);puts("");
//		}
		int ans=Solve();
		printf("%d\n",ans);
		break;
	}
	return 0;
}
