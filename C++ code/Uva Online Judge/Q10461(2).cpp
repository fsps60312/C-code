#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int V,TIME[501],DOWN[501],UP[501],VIS[501];
vector<int> TO[501],FROM[501];
#define max(x,y) (x)>(y)?(x):(y)
int dfsdown(int u)
{
	if(VIS[u])return 0;
	VIS[u]=1;
	int ans=TIME[u];
	for(int i=0;i<TO[u].size();i++)
	{
		ans+=dfsdown(TO[u][i]);
	}
	return ans;
}
int dfsup(int u)
{
	if(VIS[u])return 0;
	VIS[u]=1;
	int ans=TIME[u];
	for(int i=0;i<FROM[u].size();i++)
	{
		ans+=dfsup(FROM[u][i]);
	}
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
			DOWN[i]=UP[i]=-1;
			scanf("%d",&TIME[i]);
			sum+=TIME[i];
		}
		while(e--)
		{
			int a,b;scanf("%d%d",&a,&b);
			TO[a].push_back(b);
			FROM[b].push_back(a);
		}
		int q;scanf("%d",&q);
		printf("Case #%d:\n",kase++);
		while(q--)
		{
			int a;scanf("%d",&a);
			if(DOWN[a]==-1)
			{
				for(int i=1;i<=V;i++)VIS[i]=0;
				DOWN[a]=dfsdown(a);
				for(int i=1;i<=V;i++)VIS[i]=0;
				UP[a]=dfsup(a);
			}
			printf("%d\n",(sum-DOWN[a])-(UP[a]-TIME[a]));
		}
		printf("\n");
	}
	return 0;
}
