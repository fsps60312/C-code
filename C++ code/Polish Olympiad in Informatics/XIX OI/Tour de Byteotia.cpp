#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
set<int>ET[1000000];
int N,M,K;
int PRE[1000000],PRE_CNT,DEGREE[1000000];
vector<int>STK;
int Dfs(const int u,const int parent)
{
	STK.push_back(u);
	int low=PRE[u]=++PRE_CNT;
	for(set<int>::iterator nxt=ET[u].begin();nxt!=ET[u].end();nxt++)
	{
		if(*nxt==parent)continue;
		if(!PRE[*nxt])
		{
			const int nxtlow=Dfs(*nxt,u);
			getmin(low,nxtlow);
			if(nxtlow>=PRE[u])
			{
				for(;;)
				{
					const int v=STK.back();
					DEGREE[v]++;
					if(v==u)break;
					STK.pop_back();
				}
			}
		}
		else getmin(low,PRE[*nxt]);
	}
	return low;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].insert(b),ET[b].insert(a);
	}
	for(int i=0;i<N;i++)PRE[i]=DEGREE[i]=0;
	PRE_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1),STK.pop_back(),assert(STK.empty());
	int ans=0;
	for(int i=0;i<K;i++)
	{
		ans+=(int)ET[i].size()-DEGREE[i];
		for(set<int>::iterator nxt=ET[i].begin();nxt!=ET[i].end();nxt++)ET[*nxt].erase(i);
		ET[i].clear();
	}
	printf("%d\n",ans);
	return 0;
}
