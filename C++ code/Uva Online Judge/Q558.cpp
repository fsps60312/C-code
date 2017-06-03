#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int T,N,TIME[1000],DIS[1000];
vector<int> SOSYS[1000];
struct Hole{int to,time;};
vector<Hole> HOLE;
bool solve()
{
	queue<int> q;
	q.push(0);
	TIME[0]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<SOSYS[u].size();i++)
		{
			int ti=SOSYS[u][i],tu=HOLE[ti].to;
			//printf(" %d:%d:%d",tu,TIME[tu],TIME[u]+HOLE[ti].time);
			if(TIME[tu]!=2147483647&&TIME[tu]<=TIME[u]+HOLE[ti].time)continue;
			//printf("p");
			TIME[tu]=TIME[u]+HOLE[ti].time;
			DIS[tu]=DIS[u]+1;
			if(DIS[tu]>=N)return true;
			q.push(tu);
		}
	}
	return false;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int m;scanf("%d%d",&N,&m);
		for(int i=0;i<N;i++)
		{
			SOSYS[i].clear();
			TIME[i]=2147483647;
			DIS[i]=0;
		}HOLE.clear();
		while(m--)
		{
			int a,to,time;scanf("%d%d%d",&a,&to,&time);
			SOSYS[a].push_back(HOLE.size());
			HOLE.push_back((Hole){to,time});
		}
		if(solve())printf("possible\n");
		else printf("not possible\n");
		//for(int i=0;i<N;i++)printf(" %d",TIME[i]);printf("\n");
	}
	return 0;
}
