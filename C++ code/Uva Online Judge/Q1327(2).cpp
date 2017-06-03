#include<cstdio>
#include<stack>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,PRE[4000],LOW[4000],PRE_CNT,SCC[4000],SCC_CNT;
vector<int>ET[4000];
stack<int>STK;
void Dfs(const int u)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(const int nxt:ET[u])
	{
		if(!PRE[nxt])Dfs(nxt),getmin(LOW[u],LOW[nxt]);
		else if(SCC[nxt]==-1)getmin(LOW[u],PRE[nxt]);
	}
	if(LOW[u]==PRE[u])
	{
		for(;;)
		{
			const int tmp=STK.top();STK.pop();
			SCC[tmp]=SCC_CNT;
			if(tmp==u)break;
		}
		SCC_CNT++;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		assert(N>=1&&N<=2000);
		for(int i=0;i<N*2;i++)ET[i].clear();
		for(int i=0,k,v;i<N;i++)
		{
			assert(scanf("%d",&k)==1);
			while(k--)
			{
				assert(scanf("%d",&v)==1);
				v--;assert(v>=0&&v<N);
				ET[i].push_back(v+N);
			}
		}
		for(int i=0,v;i<N;i++)
		{
			assert(scanf("%d",&v)==1),v--;
			assert(v>=0&&v<N);
			ET[v+N].push_back(i);
		}
		for(int i=0;i<N*2;i++)PRE[i]=0,SCC[i]=-1;
		PRE_CNT=SCC_CNT=0;
		for(int i=0;i<N*2;i++)if(!PRE[i])Dfs(i),assert(STK.empty());
		for(int i=0;i<N;i++)
		{
			vector<int>ans;
			for(const int nxt:ET[i])if(SCC[nxt]==SCC[i])ans.push_back(nxt);
			sort(ans.begin(),ans.end());
			ans.resize(unique(ans.begin(),ans.end())-ans.begin());
			printf("%d",ans.size());
			for(const int v:ans)printf(" %d",v-N+1);
			puts("");
		}
	}
	return 0;
}
