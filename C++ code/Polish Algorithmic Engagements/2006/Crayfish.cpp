#include<cstdio>
#include<cassert>
#include<vector>
#include<stack>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
vector<int>ET[20000];
int PRE[20000],PRE_CNT,SCC[20000],SCC_CNT;
stack<int>STK;
bool VIS[10000];
vector<int>ANS[20000];
int N,M;
int Dfs(const int u)
{
	int ans=PRE[u]=++PRE_CNT;
	STK.push(u);
	for(int i=0;i<(int)ET[u].size();i++)if(SCC[ET[u][i]]==-1)
	{
		const int nxt=ET[u][i];
		if(!PRE[nxt])getmin(ans,Dfs(nxt));
		else getmin(ans,PRE[nxt]);
	}
	if(ans==PRE[u])
	{
		ANS[SCC_CNT].clear();
		for(;;)
		{
			const int v=STK.top();STK.pop();
			SCC[v]=SCC_CNT;
			if(!VIS[v%N])ANS[SCC_CNT].push_back(v%N),VIS[v%N]=true;
			if(v==u)break;
		}
		for(int i=0;i<(int)ANS[SCC_CNT].size();i++)VIS[ANS[SCC_CNT][i]]=false;
		SCC_CNT++;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N*2;i++)ET[i].clear();
		for(int i=0,a,b,s;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&s),a--,b--;
			ET[a].push_back(s?N+b:b);
			ET[N+b].push_back(s?a:N+a);
		}
		for(int i=0;i<N*2;i++)PRE[i]=0,SCC[i]=-1;
		PRE_CNT=SCC_CNT=0;
		for(int i=0;i<N;i++)VIS[i]=false;
		for(int i=0;i<N*2;i++)if(!PRE[i])Dfs(i),assert(STK.empty());
		for(int i=0;i<N;i++)printf("%d\n",(int)ANS[SCC[N+i]].size()-1);
	}
	return 0;
}
