#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
struct Point
{
	int x,y,z;
	bool operator<(Point a)const
	{
		return y>a.y;
	}
};
vector<Point> TO[100000];
int OUT[100000];
int VIS[100001];
vector<int> GP[100000];
int GPN;
int G_MAX[100000];
int T_MAX[100000];
void dfs_GPN(int u,int gpn)
{
	if(VIS[u])return;
	VIS[u]=1;
	GP[gpn].push_back(u);
	for(int i=0;i<TO[u].size();i++)
	{
		int nxu=TO[u][i].x;
		dfs_GPN(nxu,gpn);
	}
}
int N,M,L,ANS;
void getmax(int &a,int b){if(b>a)a=b;}
int dfs_MAX(int u)
{
	if(VIS[u])return 0;
	VIS[u]=1;
	T_MAX[u]=0;
	for(int i=0;i<TO[u].size();i++)
	{
		Point &p=TO[u][i];
		if(VIS[p.x])continue;
		getmax(T_MAX[u],dfs_MAX(p.x)+p.y);
	}
	return T_MAX[u];
}
int main()
{
	while(scanf("%d%d%d",&N,&M,&L)==3)
	{
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			OUT[i]=0;
			VIS[i]=0;
			T_MAX[i]=-1;
		}
		for(int i=0;i<M;i++)
		{
			int x,y,d;
			scanf("%d%d%d",&x,&y,&d);
			TO[x].push_back((Point){y,d,i});
			TO[y].push_back((Point){x,d,i});
			OUT[x]++,OUT[y]++;
		}
		GPN=0;
		for(int i=0;i<N;i++)
		{
			if(!VIS[i])
			{
				GP[GPN].clear();
				dfs_GPN(i,GPN);
				GPN++;
			}
		}
		ANS=0;
		for(int i=0;i<N;i++)VIS[i]=0;
		for(int g=0;g<GPN;g++)
		{
			for(int i=0;i<GP[g].size();i++)
			{
				if(OUT[GP[g][i]]<=1)
				{
					getmax(ANS,dfs_MAX(GP[g][i]));
					break;
				}
			}
		}
		for(int i=0;i<M;i++)VIS[i]=0;
		for(int g=0;g<GPN;g++)
		{
			//printf("group[%d]:",g);
			priority_queue<Point> pq;
			for(int j=0;j<GP[g].size();j++)
			{
				//printf(" %d(%d)",GP[g][j],OUT[GP[g][j]]);
				if(OUT[GP[g][j]]<=1)
				{
					pq.push((Point){GP[g][j],0,0});
				}
			}//printf("\n");
			Point p=(Point){0,0,0};
			while(!pq.empty())
			{
				p=pq.top();pq.pop();
				//printf("reach %d %d\n",p.x,p.y);
				for(int i=0;i<TO[p.x].size();i++)
				{
					Point &to=TO[p.x][i];
					if(VIS[to.z]||--OUT[to.x]>1)continue;
					VIS[to.z]=1;
					pq.push((Point){to.x,p.y+to.y,0});
				}
			}
			G_MAX[g]=p.y;
		}
		priority_queue<int> pq;
		for(int i=0;i<GPN;i++)
		{
			pq.push(G_MAX[i]);
			//printf("[%d]=%d\n",i,G_MAX[i]);
		}
		int ans=pq.top();pq.pop();
		getmax(ANS,ans+L+pq.top());
		printf("%d\n",ANS);
	}
	return 0;
}
