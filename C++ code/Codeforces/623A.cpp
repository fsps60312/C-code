#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
bool EDGE[500][500];
int COLOR[500],GID[500];
vector<int>GROUP[500];
bool Dfs(const int u,const int color,const int gid)
{
	if(COLOR[u]!=-1)return COLOR[u]==color;
	COLOR[u]=color;
	GROUP[GID[u]=gid].push_back(u);
	for(int i=0;i<N;i++)if(i!=u&&!EDGE[u][i])if(!Dfs(i,color^2,gid))return false;
	return true;
}
bool Solve()
{
	for(int i=0;i<N;i++)COLOR[i]=-1,GID[i]=-1,GROUP[i].clear();
	int gid=0;
	for(int i=0;i<N;i++)if(COLOR[i]==-1)if(!Dfs(i,0,gid++))return false;
	vector<int>order;
	for(int i=0;i<gid;i++)order.push_back(i);
	sort(order.begin(),order.end(),[](int a,int b)->bool{return GROUP[a].size()>GROUP[b].size();});
	for(int i=gid-1;i>=0&&(int)GROUP[order[i]].size()==1;i==)order.pop_back();
	for(int i=1;i<order.size();i++)
	{
		const int ga=order[i-1],gb=order[i];
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=false;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			EDGE[a][b]=EDGE[b][a]=true;
		}
		if(!Solve())puts("NO");
		else
		{
			puts("YES");
			for(int i=0;i<N;i++)putchar('a'+COLOR[i]);puts("");
		}
	}
	return 0;
}
