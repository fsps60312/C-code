#include<cstdio>
#include<cstdlib>
#include<queue>
#include<map>
#include<string>
#include<vector>
using namespace std;
int N,VIS[19900];
map<string,int> IDX;
vector<int> CITY[200];
struct Pair
{
	int x,y;
	bool operator<(Pair a)const{return x<a.x;}
};
vector<Pair> ROAD;
int getidx(char *a)
{
	if(IDX.find(a)!=IDX.end())return IDX[a];
	int sz=IDX.size();
	IDX[a]=sz;
	return sz;
}
#define min(x,y) (x)<(y)?(x):(y)
int solve(int sp,int ep)
{
	priority_queue<Pair> pq;
	pq.push((Pair){10000,sp});
	while(!pq.empty())
	{
		Pair p=pq.top();pq.pop();
		if(p.y==ep)return p.x;
		for(int i=0;i<CITY[p.y].size();i++)
		{
			int j=CITY[p.y][i];
			if(VIS[j])continue;
			VIS[j]=1;
			pq.push((Pair){min(p.x,ROAD[j].x),ROAD[j].y});
		}
	}
	return 0;
}
char tstr[2][31];
int main()
{
	freopen("inn.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int r,kase=1;
	while(scanf("%d%d",&N,&r)==2&&(N||r))
	{
		IDX.clear();
		ROAD.clear();
		for(int i=0;i<N;i++)CITY[i].clear();
		for(int i=0;i<r;i++)
		{
			VIS[i]=0;
			int w;scanf("%s%s%d",tstr[0],tstr[1],&w);
			int a=getidx(tstr[0]),b=getidx(tstr[1]);
			int sz=ROAD.size();
			ROAD.push_back((Pair){w,b});
			CITY[a].push_back(sz++);
			ROAD.push_back((Pair){w,a});
			CITY[b].push_back(sz);
		}
		scanf("%s%s",tstr[0],tstr[1]);
		printf("Scenario #%d\n%d tons\n\n",kase++,solve(getidx(tstr[0]),getidx(tstr[1])));
	}
	return 0;
}
