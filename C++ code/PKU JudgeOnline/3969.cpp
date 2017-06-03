#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,M,K;
vector<int>ET[9999];
bool VIS[9999];
set<int>COLOR[9999];
void Dfs(const int u)
{
	if(VIS[u])return;
	VIS[u]=true;
	for(int i=0;i<(int)ET[u].size();i++)Dfs(ET[u][i]);
	assert(!COLOR[u].empty());
	const int color=*COLOR[u].begin();
	COLOR[u].clear(),COLOR[u].insert(color);
	for(int i=0;i<(int)ET[u].size();i++)COLOR[ET[u][i]].erase(color);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),a--,b--,ET[a].push_back(b),ET[b].push_back(a);
		K=0;
		for(int i=0;i<N;i++)getmax(K,(int)ET[i].size());
		if(K%2==0)K++;
		int mn=INF,source=-1;
		for(int i=0;i<N;i++)if((int)ET[i].size()<mn)mn=(int)ET[i].size(),source=i;
		for(int i=0;i<N;i++)
		{
			VIS[i]=false;
			COLOR[i].clear();
			for(int c=1;c<=K;c++)COLOR[i].insert(c);
		}
		Dfs(source);
		printf("%d\n",K);
		for(int i=0;i<N;i++)printf("%d\n",*COLOR[i].begin());
		break;
	}
	return 0;
}
