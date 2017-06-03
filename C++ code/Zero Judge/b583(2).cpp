#include<bits/stdc++.h>
using namespace std;
int T,V,E;
vector<int>AD[1000];
int ADD[1000][1000],VIS[1000],IN[1000],KASE=0;
bool Dfs(int u)
{
	if(VIS[u])return VIS[u]==KASE;
	VIS[u]=KASE;
	for(int i=0;i<AD[u].size();i++)if(Dfs(AD[u][i]))return true;
	VIS[u]=0;
	return false;
}
void Tag(int u)
{
	if(VIS[u])return;
	VIS[u]=KASE;
	for(int i=0;i<AD[u].size();i++)Tag(AD[u][i]);
}
bool Solve()
{
	for(int i=0;i<V;i++)
	{
		if(VIS[i]||IN[i]>0)continue;
		KASE++;
		if(Dfs(i))return true;
		Tag(i);
	}
	for(int i=0;i<V;i++)if(VIS[i]==0)return true;
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
