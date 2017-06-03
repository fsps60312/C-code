#include<cstdio>
#include<queue>
using namespace std;
const int INF=2147483647;
int DIST[2000001];
bool INQ[2000001];
int A,B;
int main()
{
	while(scanf("%d%d",&A,&B)==2)
	{
		for(int i=0;i<=2000000;i++)DIST[i]=INF,INQ[i]=false;
		queue<int>q;
		DIST[A]=0,q.push(A),INQ[A]=true;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			INQ[u]=false;
			int *nxt=new int[6]{u+1,u+2,u-1,u-2,u*2,u/2};
			int *cost=new int[6]{DIST[u]+2,DIST[u]+3,DIST[u]+2,DIST[u]+3,DIST[u]+3,DIST[u]+3};
			for(int i=0;i<6;i++)if(nxt[i]>=0&&nxt[i]<=2000000&&cost[i]<DIST[nxt[i]])
			{
				DIST[nxt[i]]=cost[i];
				if(!INQ[nxt[i]])q.push(nxt[i]),INQ[nxt[i]]=true;
			}
			delete[]cost;
			delete[]nxt;
		}
		printf("%d\n",DIST[B]);
	}
	return 0;
}
