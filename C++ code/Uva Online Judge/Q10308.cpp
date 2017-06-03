#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int CN=0,RN=0;
void getmax(int &a,int b){if(b>a)a=b;}
struct Point
{
	int x,y;
	bool operator>(Point a)
	{
		return y>a.y;
	}
};
vector<Point> TO[10001];
Point H1[10001],H2[10001];
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
		Point &nxp=TO[u][i];
		if(nxp.x==fa)continue;
		update(u,(Point){nxp.x,dfs_wp_down(nxp.x,u)+nxp.y});
	}
	return H1[u].y;
}
void dfs_wp_up(int u,int fa,int len)
{
	if(u!=fa)
	{
		if(H1[fa].x==u)
		{
			update(u,(Point){fa,H2[fa].y+len});
		}
		else
		{
			update(u,(Point){fa,H1[fa].y+len});
		}
	}
	for(int i=0;i<TO[u].size();i++)
	{
		Point &nxp=TO[u][i];
		if(nxp.x==fa)continue;
		dfs_wp_up(nxp.x,u,nxp.y);
	}
}
int get_diameter()
{
	dfs_wp_down(1,1);
	dfs_wp_up(1,1,0);
	int ans=0;
	for(int i=1;i<=CN;i++)
	{
		getmax(ans,H1[i].y+H2[i].y);
	}
	return ans;
}
void outputans()
{
	for(int i=1;i<=CN;i++)
	{
		H1[i]=H2[i]=(Point){-1,0};
	}
	printf("%d\n",get_diameter());
	for(int i=1;i<=CN;i++)TO[i].clear();
	CN=RN=0;
}
char INPUT[1000000];
int main()
{
	//freopen("in.txt","r",stdin);
	int x,y,d;
	while(gets(INPUT))
	{
		if(sscanf(INPUT,"%d%d%d",&x,&y,&d)!=3)
		{
			outputans();
			continue;
		}
		getmax(CN,x);
		getmax(CN,y);
		RN++;
		TO[x].push_back((Point){y,d});
		TO[y].push_back((Point){x,d});
	}
	outputans();
	return 0;
}
