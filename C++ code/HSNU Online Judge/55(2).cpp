#include<cstdio>
#include<vector>
#include<stack>
using namespace std;
int N;
vector<int>OET[100000];
int PRE[100000],PRE_CNT,LOW[100000],SCC[100000],SCC_CNT;
stack<int>STK;
void Dfs(const int &u)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(int i=0;i<OET[u].size();i++)
	{
		const int &et=OET[u][i];
		if(!PRE[et])
		{
			Dfs(et);
			LOW[u]=min(LOW[u],LOW[et]);
		}
		else if(SCC[et]==-1)LOW[u]=min(LOW[u],PRE[et]);
	}
	if(LOW[u]==PRE[u])
	{
		while(STK.top()!=u)SCC[STK.top()]=SCC_CNT,STK.pop();
		SCC[u]=SCC_CNT++,STK.pop();
	}
}
void BuildSCC()
{
	for(int i=0;i<N;i++)PRE[i]=0,SCC[i]=-1;
	PRE_CNT=SCC_CNT=0;
	for(int i=0;i<N;i++)
	{
		if(PRE[i])continue;
		Dfs(i);
	}
}
vector<int>ET[100000];
bool IN[100000],OUT[100000];
void Rebuild()
{
	for(int i=0;i<SCC_CNT;i++)ET[i].clear(),IN[i]=OUT[i]=false;
	for(int a=0;a<N;a++)
	{
		for(int i=0;i<OET[a].size();i++)
		{
			const int &b=OET[a][i];
			if(SCC[a]==SCC[b])continue;
			ET[SCC[a]].push_back(SCC[b]);
			OUT[SCC[a]]=IN[SCC[b]]=true;
		}
	}
//	for()
//	for(int i=0;i<SCC_CNT;i++)
//	{
//		printf("i=%d\n",i);
//		for(int j:ET[i])printf("(%d,%d)\n",i,j);
//	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)OET[i].clear();
	for(int a=0,b;a<N;a++)while(scanf("%d",&b)==1&&b)OET[a].push_back(--b);
	BuildSCC();
//	printf("SCC_CNT=%d\n",SCC_CNT);
	Rebuild();
	int in_cnt=0,out_cnt=0;
	for(int i=0;i<SCC_CNT;i++)
	{
		if(!IN[i])in_cnt++;
		if(!OUT[i])out_cnt++;
	}
	int ans=max(in_cnt,out_cnt);
	if(SCC_CNT==1)ans=0;
	printf("%d\n%d\n",in_cnt,ans);
	return 0;
}
