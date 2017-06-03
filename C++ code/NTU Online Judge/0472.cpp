#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,M;
bool VIS[100];
int Dfs(const vector<int>*et,const int u)
{
	if(VIS[u])return 0;
	VIS[u]=true;
	int ans=1;
	for(int i=0;i<(int)et[u].size();i++)ans+=Dfs(et,et[u][i]);
	return ans;
}
vector<int>ET[100],EF[100];
bool Solve(const int u)
{
	for(int i=0;i<N;i++)VIS[i]=false;
	int sz=0;
	sz+=Dfs(ET,u)-1;
	VIS[u]=false;
	sz+=Dfs(EF,u);
	return sz==N;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),EF[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),EF[b].push_back(a);
		}
		int ans=0;
		for(int i=0;i<N;i++)if(Solve(i))++ans;
		printf("%d\n",ans);
	}
	return 0;
}
