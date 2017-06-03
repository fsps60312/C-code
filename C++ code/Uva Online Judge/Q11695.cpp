#include<cstdio>
#include<cstdlib>
#include<vector>
#include <utility>
using namespace std;
int T,N;
struct Edge
{
	int to,inuse;
};
int INUSE[2500],DIAMETER;
vector<Edge> TO[2501];
struct Point
{
	int x,y;
	bool operator>(Point a)
	{
		return y>a.y;
	}
};
Point H1[2501],H2[2501];
void update(int u,Point p)
{
	if(p>H1[u])
	{
		H2[u]=H1[u];
		H1[u]=p;
	}
	else
	{
		H2[u]=p;
	}
}
int dfs_wp_down(int u,int fa)
{
	H1[u].x=0;
	for(int i=0;i<TO[u].size();i++)
	{
		Edge &e=TO[u][i];
		if(e.to==fa||!INUSE[e.inuse])continue;
		update(u,(Point){e.to,dfs_wp_down(e.to,u)+1});
	}
	return H1[u].y;
}
void dfs_wp_up(int u,int fa)
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
	for(int i=0;i<TO[u].size();i++)
	{
		Edge &e=TO[u][i];
		if(e.to==fa||!INUSE[e.inuse])continue;
		dfs_wp_up(e.to,u);
	}
}
void getmax(int &a,int b){if(b>a)a=b;}
vector<int> OND;
void delete_DIAMETER(int u,int fa)
{
	OND.push_back(u);
	for(int i=0;i<TO[u].size();i++)
	{
		Edge &e=TO[u][i];
		if(e.to==fa||H1[e.to].y+H2[e.to].y!=DIAMETER)continue;
		INUSE[e.inuse]=0;
		delete_DIAMETER(e.to,u);
		return;
	}
}
int D1[2501],D2[2501];
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++)
		{
			TO[i].clear();
			H1[i]=H2[i]=(Point){-1,0};
		}
		for(int i=0;i<N-1;i++)
		{
			INUSE[i]=1;
			int a,b;scanf("%d%d",&a,&b);
			TO[a].push_back((Edge){b,i});
			TO[b].push_back((Edge){a,i});
		}
		dfs_wp_down(1,1);
		dfs_wp_up(1,1);
		DIAMETER=0;
		for(int i=1;i<=N;i++)getmax(DIAMETER,H1[i].y+H2[i].y);
		OND.clear();
		for(int i=1;i<=N;i++)
		{
			if(H1[i].y==DIAMETER)
			{
				delete_DIAMETER(i,i);
				break;
			}
		}
		for(int i=1;i<=N;i++)
		{
			H1[i]=H2[i]=(Point){-1,0};
		}
		for(int i=0;i<OND.size();i++)
		{
			int &root=OND[i];
			dfs_wp_down(root,root);
		}
		int n=OND.size()-1;
		D1[0]=D2[n]=0;
		for(int i=1;i<OND.size();i++)
		{
			D1[i]=i+H1[OND[i]].y;
			D2[n-i]=i+H1[OND[n-i]].y;
		}
		int ans=2147483647;
		int rx,ry,ax,ay;
		for(int i=0;i<n;i++)
		{
			int td=(D1[i]+1)/2+1+(D2[i+1]+1)/2;
			if(D1[i]>td)td=D1[i];
			if(D2[i+1]>td)td=D2[i+1];
			//printf("(%d,%d):%d(%d,%d)\n",OND[i],OND[i+1],td,D1[i],D2[i+1]);
			if(td<ans)
			{
				ans=td;
				rx=OND[i];
				ry=OND[i+1];
				if(rx>ry) swap(rx, ry);
				ax=OND[D1[i]/2];
				ay=OND[n-D2[i+1]/2];
				if(ax>ay) swap(ax, ay);
			}
		}
		printf("%d\n%d %d\n%d %d\n",ans,rx,ry,ax,ay);
	}
	return 0;
}
