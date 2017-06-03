#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<cassert>
using namespace std;
int N,K;
int VIS[100005],TMP,P,RECORDING;
vector<int>ET[100005],REC,QUE;
void Dfs(int u,int add)
{
	if(VIS[u])return;
	VIS[u]=true;
	if(RECORDING)REC.push_back(u);
	if(add>TMP)TMP=add,P=u;
	for(int i=0;i<ET[u].size();i++)
	{
		int v=ET[u][i];
		if(VIS[v])continue;
		Dfs(v,add+1);
		if(RECORDING)REC.pop_back();
	}
	if(RECORDING&&add==TMP)
	{
		QUE=REC;
		RECORDING=0;
	}
	VIS[u]=false;
	return;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=1;i<=N;i++)VIS[i]=false,ET[i].clear();
		TMP=0,RECORDING=0;
		REC.clear(),QUE.clear();
		for(int i=1;i<N;i++)
		{
			static int x,y;
			scanf("%d%d",&x,&y);
			ET[x].push_back(y);
			ET[y].push_back(x);
		}
		Dfs(1,0);
		Dfs(P,0);
		RECORDING=1;
		Dfs(P,0);
		REC.clear();
		int ans=2*(N-1)-(TMP-1);
		if(K==1)printf("%d\n",ans);
		else
		{
			for(int i=1;i<=N;i++)VIS[i]=false;
			for(int i=0;i<QUE.size();i++)VIS[QUE[i]]=true;
			int qw=0;
			for(int i=0;i<QUE.size();i++)
			{
				TMP=0;
				P=QUE[i];
				int pre=P;
				VIS[pre]=false;
				Dfs(P,0);
				VIS[pre]=true;
				REC.push_back(TMP);
				pre=P;
				VIS[pre]=false;
				VIS[QUE[i]]=false;
				Dfs(P,0);
				VIS[pre]=true;
				VIS[QUE[i]]=true;
				qw=max(qw,TMP);
			}
			for(int i=0;i<QUE.size();i++)for(int j=i+1;j<QUE.size();j++)qw=max(qw,REC[i]+REC[j]-(j-i));
			ans-=qw-1;
			printf("%d\n",ans);
		}
	}
}
