#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
struct Point
{
	int x,y;
	int Toint(){return x*60+y;}
};
struct Guest
{
	Point time,from,to;
}GUEST[500];
int T,M,T2[500],TO[500];
vector<int> GETO[500];
int abs(int a){return a>=0?a:-a;}
int dis(Point a,Point b){return abs(a.x-b.x)+abs(a.y-b.y);}
bool intime(Guest a,Guest b)
{
	return a.time.Toint()+dis(a.from,a.to)<b.time.Toint();
}
bool check_paired(int u)
{
	for(int i=0;i<GETO[u].size();i++)
	{
		int &j=GETO[u][i];
		if(T2[j])continue;
		T2[j]=1;
		if(TO[j]==-1||check_paired(TO[j]))
		{
			TO[j]=u;
			return true;
		}
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin); 
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&M);
		for(int i=0;i<M;i++)
		{
			Guest &g=GUEST[i];
			scanf("%d:%d%d%d%d%d",&g.time.x,&g.time.y,&g.from.x,&g.from.y,&g.to.x,&g.to.y);
		}
		for(int i=0;i<M;i++)
		{
			GETO[i].clear();
		}
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<M;j++)
			{
				if(intime(GUEST[i],GUEST[j]))
				{
					GETO[i].push_back(j);
				}
			}
		}
		for(int i=0;i<M;i++)
		{
			TO[i]=-1;
		}
		int edge_find=0;
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<M;j++)T2[j]=0;
			if(check_paired(i))edge_find++;
		}
		printf("%d\n",M-edge_find);
	}
	return 0;
}
