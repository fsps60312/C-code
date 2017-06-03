#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
struct Point
{
	int x,y;
	bool operator>(Point a)const
	{
		return y>a.y;
	}
};
vector<Point> TO[200001];
Point H1[200001],H2[200001];
int SUM[200001];
void update(int u,Point p)
{
	if(p>H1[u])H2[u]=H1[u],H1[u]=p;
	else if(p>H2[u])H2[u]=p;
}
Point newpoint(int a,int b)
{
	Point ans;
	ans.x=a,ans.y=b;
	return ans;
}
int dfs_weight_1(int u,int fa)
{
	H1[u].y=H2[u].y=0;
	SUM[u]=0;
	for(int i=0;i<TO[u].size();i++)
	{
		Point &p=TO[u][i];
		if(p.x==fa)continue;
		int sum=dfs_weight_1(p.x,u)+p.y;
		update(u,newpoint(p.x,sum));
		SUM[u]+=sum;
	}
	return SUM[u];
}
int T,N;
void dfs_weight_2(int u,int fa,int len)
{
	if(u!=fa)
	{
		if(H1[fa].x==u)
		{
			if(H2[fa].x!=-1)update(u,newpoint(fa,N-1-SUM[u]));
		}
		else
		{
			if(H1[fa].x!=-1)update(u,newpoint(fa,N-1-SUM[u]));
		}
	}
	for(int i=0;i<TO[u].size();i++)
	{
		Point &p=TO[u][i];
		if(p.x==fa)continue;
		dfs_weight_2(p.x,u,p.y);
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++)
		{
			TO[i].clear();
			H1[i]=newpoint(-1,-1);
			H2[i]=newpoint(-1,-1);
		}
		for(int i=0;i<N-1;i++)
		{
			int x,y,d;scanf("%d%d",&x,&y);
			d=1;
			TO[x].push_back(newpoint(y,d));
			TO[y].push_back(newpoint(x,d));
		}
		dfs_weight_1(1,1);
		dfs_weight_2(1,1,0);
		Point ans=newpoint(-1,2147483647);
		for(int i=1;i<=N;i++)
		{
			//printf("[%d]:%d %d %d %d\n",i,H1[i].x,H1[i].y,H2[i].x,H2[i].y);
			Point tp=newpoint(i,H1[i].y);
			if(ans>tp)ans=tp;
		}
		printf("%d %d\n",ans.x,ans.y);
	}
	return 0;
}
