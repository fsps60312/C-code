#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
struct Path{int to,dis;};
vector<int> INTE[1001];
vector<Path> PATH;
int WAY[1001],MAX[1001],DONE[1001];
struct Trip
{
	int pos,dis;
	bool operator<(Trip a)const{return dis>a.dis;}
};
int N;
int query(int u)
{
	//printf("u=%d\n",u);
	int &w=WAY[u];
	if(w)return w;
	for(int i=0;i<INTE[u].size();i++)
	{
		Path p=PATH[INTE[u][i]];
		if(MAX[p.to]<MAX[u])w+=query(p.to);
	}
	return w;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		PATH.clear();
		for(int i=1;i<=N;i++)
		{
			INTE[i].clear();
			MAX[i]=2147483647;
			WAY[i]=DONE[i]=0;
		}
		int m;scanf("%d",&m);
		while(m--)
		{
			int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
			INTE[a].push_back(PATH.size());
			PATH.push_back((Path){b,dis});
			INTE[b].push_back(PATH.size());
			PATH.push_back((Path){a,dis});
		}
		priority_queue<Trip> pq;
		pq.push((Trip){1,0});
		while(!pq.empty())
		{
			Trip trip=pq.top();pq.pop();
			int pos=trip.pos,dis=trip.dis;
			if(DONE[pos])continue;
			DONE[pos]=true;
			MAX[pos]=dis;
			for(int i=0;i<INTE[pos].size();i++)
			{
				Path p=PATH[INTE[pos][i]];
				pq.push((Trip){p.to,dis+p.dis});
			}
		}
		WAY[1]=1;
		printf("%d\n",query(2));
	}
	return 0;
}
