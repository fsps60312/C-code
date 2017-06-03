#include<bits/stdc++.h>
using namespace std;
int T,V,E;
vector<int>AD[1000];
int ADD[1000][1000],VIS[1000],IN[1000];
bool Dfs(int u)
{
	if(VIS[u]==1)return true;
	else if(VIS[u]==2)return false;
	else assert(VIS[u]==0);
	VIS[u]=1;
	for(int i=0;i<AD[u].size();i++)
	{
		if(Dfs(AD[u][i]))return true;
	}
	VIS[u]=2;
	return false;
}
bool Solve()
{
	for(int i=0;i<V;i++)
	{
		if(VIS[i]||IN[i]>0)continue;
		if(Dfs(i))return true;
	}
	for(int i=0;i<V;i++)
	{
		if(VIS[i]==0)return true;
		else assert(VIS[i]==2);
	}
	return false;
}
int main()
{
	for(int i=0;i<1000;i++)for(int j=0;j<1000;j++)ADD[i][j]=0;
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&V,&E);
			assert(V>=1&&V<=1000);
			for(int i=0;i<V;i++)
			{
				VIS[i]=IN[i]=0;
				AD[i].clear();
			}
			static int kase=0;kase++;
			for(int i=0,a,b;i<E;i++)
			{
				scanf("%d%d",&a,&b);
				a--,b--;
				assert(a>=0&&a<V&&b>=0&&b<V);
				if(ADD[a][b]==kase)continue;
				ADD[a][b]=kase;
				AD[a].push_back(b);
				IN[b]++;
			}
			puts(Solve()?"O______O":"W+W");
		}
	}
	return 0;
}
