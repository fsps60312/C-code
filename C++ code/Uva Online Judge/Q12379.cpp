#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
vector<int> TO[10001];
struct Point
{
	int x,y;
	bool operator>(Point a)
	{
		return y>a.y;
	}
}H1[10001],H2[10001];
void update(int u,Point p)
{
	if(p>H1[u])
	{
		H2[u]=H1[u];
		H1[u]=p;
	}
	else if(p>H2[u])
	{
		H2[u]=p;
	}
}
int dfs_wp_down(int u,int fa)
{
	for(int i=0;i<TO[u].size();i++)
	{
		int nxp=TO[u][i];
		if(nxp==fa)continue;
		update(u,(Point){nxp,dfs_wp_down(nxp,u)+1});
	}
	return H1[u].y;
}
void dfs_wp_up(int u,int fa,int &rec)
{
	if(u!=fa)
	{
		if(H1[fa].x==u)
		{
			update(u,(Point){fa,H2[fa].y+1});
		}
		else
		{
			update(u,(Point){fa,H1[fa].y+1});
		}
	}
	int ans=H1[u].y+H2[u].y;
	if(ans>rec)rec=ans;
	for(int i=0;i<TO[u].size();i++)
	{
		int nxp=TO[u][i];
		if(nxp==fa)continue;
		dfs_wp_up(nxp,u,rec);
	}
}
int N,T;
int get_diameter()
{
	for(int i=1;i<=N;i++)
	{
		H1[i]=H2[i]=(Point){-1,0};
	}
	dfs_wp_down(1,1);
	int ans=0;
	dfs_wp_up(1,1,ans);
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)
		{
			TO[i].clear();
		}
		for(int i=1;i<=N;i++)
		{
			int a;scanf("%d",&a);
			while(a--)
			{
				int b;scanf("%d",&b);
				TO[i].push_back(b);
			}
		}
		printf("%d\n",(N-1)*2-get_diameter());
	}
	return 0;
}
