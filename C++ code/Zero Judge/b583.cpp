#include<bits/stdc++.h>
using namespace std;
int T,V,E;
set<int>AD[1000];
int VIS[1000],IN[1000];
int KASE=0;
bool Dfs(int u)
{
	if(VIS[u])return VIS[u]==KASE;
	VIS[u]=KASE;
	for(set<int>::iterator i=AD[u].begin();i!=AD[u].end();i++)if(Dfs(*i))return true;
}
bool Solve()
{
	for(int i=0;i<V;i++)
	{
		if(VIS[i]||IN[i]>0)continue;
		KASE++;
		if(Dfs(i))return true;
	}
	for(int i=0;i<V;i++)if(VIS[i]==0)return true;
	return false;
}
int main()
{
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
			for(int i=0,a,b;i<E;i++)
			{
				scanf("%d%d",&a,&b);
				a--,b--;
				assert(a>=0&&a<V&&b>=0&&b<V);
				AD[a].insert(b);
				IN[b]++;
			}
			puts(Solve()?"O______O":"W+W");
		}
	}
	return 0;
}
