#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
vector<int> connect[30];
bool grouped[30];
vector<int> group[30];
int start,now,strict,T,n,m;
int vis[30];
int area[30];
double odd[30][30];//remains sum, remains odd
double mom;
void dfs(int a,int b)
{
	if(grouped[a]) return;
	grouped[a]=true;
	if(a==1) start=b;
	group[b].push_back(a);
	for(int i=0;i<connect[a].size();i++)
	{
		dfs(connect[a][i],b);
	}
}
double fromtopath(double a,double b)//from, to
{
	return b/(1-a)/(1-a);
}
double search(double a,double b,int c)//steps to get here, chance to get here, area now
{
	double ans=b*a;
	if(c==n) return ans;
	for(int i=0;i<strict;i++)
	{
		if(!vis[i])
		{
			vis[i]=true;
			ans+=search(a+fromtopath((c-1)/mom,area[i]/mom),b*area[i]/mom,c+area[i]);
			vis[i]=false;
		}
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;i++)
		{
			connect[i].clear();
			group[i].clear();
			grouped[i]=false;
		}
		for(int i=0;i<m;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			connect[a].push_back(b);
			connect[b].push_back(a);
		}
		strict=0;
		start=-1;
		for(int i=1;i<=n;i++)
		{
			if(!grouped[i])
			{
				dfs(i,strict);
				strict++;
			}
		}
		for(int i=0;i<strict;i++)
		{
			area[i]=group[i].size();
			//for(int j=0;j<area[i];j++) printf(" %d",group[i][j]);printf("\n");
			vis[i]=0;
		}
		vis[start]++;
		now=1;
		double ans=0;
		mom=n-1;
		ans=search(0,1,area[start]);
		printf("Case %d: %.1llf\n",t,ans);
	}
	return 0;
}
