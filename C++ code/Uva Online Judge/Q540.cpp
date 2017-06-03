#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
int N,IDX[1000000];
queue<int>Q;
vector<bool>INQ;
vector<queue<int> >TEAM;
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		TEAM.clear(),INQ.clear();
		for(int i=0,cnt,v;i<N;i++)
		{
			scanf("%d",&cnt);
			while(cnt--)scanf("%d",&v),IDX[v]=i;
			INQ.push_back(false);
			TEAM.push_back(queue<int>());
		}
		static char command[8];
		while(!Q.empty())Q.pop();
		static int kase=1;
		printf("Scenario #%d\n",kase++);
		while(scanf("%s",command)==1)
		{
			if(command[0]=='S')break;
			else if(command[0]=='E')
			{
				static int v;scanf("%d",&v);
				TEAM[IDX[v]].push(v);
				if(!INQ[IDX[v]])Q.push(IDX[v]),INQ[IDX[v]]=true;
			}
			else if(command[0]=='D')
			{
				auto &team=TEAM[Q.front()];
				printf("%d\n",team.front());
				team.pop();
				if(team.empty())INQ[Q.front()]=false,Q.pop();
			}
			else assert(0);
		}
		puts("");
	}
	return 0;
}
