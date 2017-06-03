#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N,M;
vector<int>ET[10000];
int PRE[10000],PRE_CNT;
int DJ[10000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int Dfs(const int u)
{
	PRE[u]=++PRE_CNT;
	int ans=-1;
	for(const int nxt:ET[u])
	{
		if(!PRE[nxt])
		{
			const int result=Dfs(nxt);
			if(result==-1)return -1;
			assert(result<=PRE[u]);
			if(result==PRE[u]){ans=0;continue;}
			else return result;
		}
		else return PRE[nxt];
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&N,&M)==2);
		assert(N>0&&N<=10000);
		for(int i=0;i<N;i++)ET[i].clear(),PRE[i]=0;
		PRE_CNT=0;
		for(int i=0,a,b;i<M;i++)
		{
			assert(scanf("%d%d",&a,&b)==2&&a>=0&&a<N&&b>=0&&b<N);
			ET[a].push_back(b);
		}
	}
	return 0;
}
