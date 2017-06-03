#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?a=b,true:false;}
int N,M;
vector<int>TYPE[300000];
vector<int>ET[300000];
bool TVIS[300000],EVIS[300000];
void Dfs(const int u,set<int>&remain,int *color)
{
	if(TVIS[u])return;
	TVIS[u]=true;
//	const int k=(int)TYPE[u].size();
	for(const int t:TYPE[u])if(color[t]!=-1)remain.erase(color[t]);
	for(const int t:TYPE[u])if(color[t]==-1)color[t]=*remain.begin(),remain.erase(remain.begin());
	for(const int t:TYPE[u])remain.insert(color[t]);
	for(const int t:TYPE[u])if(!EVIS[t])
	{
		EVIS[t]=true;
		for(const int nxtu:ET[t])Dfs(nxtu,remain,color);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)TYPE[i].clear(),TVIS[i]=false;
		for(int i=0;i<M;i++)ET[i].clear(),EVIS[i]=false;
		int ans=1;
		for(int i=0,s;i<N;i++)
		{
			scanf("%d",&s);
			getmax(ans,s);
			for(int v;s--;)
			{
				scanf("%d",&v),--v;
				TYPE[i].push_back(v);
				ET[v].push_back(i);
			}
		}
		for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b);
		set<int>remain;
		for(int i=0;i<M;i++)remain.insert(i);
		static int color[300000];
		for(int i=0;i<M;i++)color[i]=-1;
		for(int i=0;i<N;i++)Dfs(i,remain,color);
		for(int i=0;i<M;i++)if(color[i]==-1)color[i]=0;
		printf("%d\n",ans);
		for(int i=0;i<M;i++)
		{
			if(i)putchar(' ');
			printf("%d",color[i]+1);
		}
		puts("");
	}
	return 0;
}
