#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int V,TIME[501],VIS1[501],VIS2[501],DOWN[501],UP[501];
vector<int> TO[501],FROM[501];
#define max(x,y) (x)>(y)?(x):(y)
int dfsdown(int u)
{
	if(VIS1[u])return DOWN[u];
	int &ans=DOWN[u];
	ans=TIME[u];
	for(int i=0;i<TO[u].size();i++)
	{
		ans+=dfsdown(TO[u][i]));
	}
	VIS1[u]=1;
	return ans;
}
int dfsup(int u)
{
	if(VIS2[u])return UP[u];
	int &ans=UP[u];
	ans=0;
	for(int i=0;i<FROM[u].size();i++)
	{
		ans=max(ans,dfsup(FROM[u][i]));
	}
	ans+=TIME[u];
	VIS2[u]=1;
	return ans;
}
int main()
{
	int e,kase=1;
	while(scanf("%d%d",&V,&e)==2&&(V||e))
	{
		int sum=0;
		for(int i=1;i<=V;i++)
		{
			TO[i].clear(),FROM[i].clear();
			VIS1[i]=VIS2[i]=0;
			scanf("%d",&TIME[i]);
			sum+=TIME[i];
		}
		while(e--)
		{
			int a,b;scanf("%d%d",&a,&b);
			TO[a].push_back(b);
			FROM[b].push_back(a);
		}
		for(int i=1;i<=V;i++)
		{
			if(!VIS1[i])dfsdown(i);
			if(!VIS2[i])dfsup(i);
		}
		int q;scanf("%d",&q);
		printf("Case #%d:\n",kase++);
		while(q--)
		{
			int a;scanf("%d",&a);
			printf(" %d %d\n",DOWN[a],UP[a]);
			printf("%d\n",(sum-DOWN[a])-UP[a]+TIME[a]*2);
		}
		printf("\n");
	}
	return 0;
}
