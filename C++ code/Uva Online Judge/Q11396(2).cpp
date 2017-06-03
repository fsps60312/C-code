#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int V,DEG[300];
vector<int>TO[300];
bool dfs(int u,int fa)
{
	if(DEG[u]!=3)
	{
		if(fa==-1)assert(0);
		if(DEG[u]+DEG[fa]==3)return true;
		else return false;
	}
	else if(fa==-1)DEG[u]=1;
	else DEG[u]=3-DEG[fa];
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(!dfs(j,u))return false;
	}
	return true;
}
bool solve()
{
	for(int a,b;scanf("%d%d",&a,&b)==2&&(a||b);)
	{
		a--,b--;
		if(a==b)assert(0);
		TO[a].push_back(b);
		TO[b].push_back(a);
		DEG[a]++,DEG[b]++;
	}
	for(int i=0;i<V;i++)if(DEG[i]!=3)assert(0);
	return dfs(0,-1);
}
int main()
{
	while(scanf("%d",&V)==1&&V)
	{
		for(int i=0;i<V;i++)
		{
			TO[i].clear();
			DEG[i]=0;
		}
		printf("%s\n",solve()?"YES":"NO");
	}
	return 0;
}
