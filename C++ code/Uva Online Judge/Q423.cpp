#include<cstdio>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;
int N,MAT[101][101],VIS[101];//,INQUE[101];
struct Pair
{
	int x,y;
	bool operator<(Pair a)const{return x>a.x;}
};
int solve()
{
	for(int i=1;i<=N;i++)VIS[i]=0;//INQUE[i]=0;
	priority_queue<Pair> pq;
	pq.push((Pair){0,1});
	int ans=0;
	while(!pq.empty())
	{
		Pair u=pq.top();pq.pop();
		//INQUE[u.y]=0;
		if(VIS[u.y])continue;
		//printf("u=%d,%d\n",u.x,u.y);
		VIS[u.y]=1;
		if((++ans)==N)return u.x;
		for(int i=1;i<=N;i++)
		{
			if(u.y==i||MAT[u.y][i]==-1/*||INQUE[i]*/)continue;
			pq.push((Pair){u.x+MAT[u.y][i],i});
			//printf("push %d to %d\t(%d,%d)\n",u.y,i,MAT[5][4],MAT[4][5]);
			//INQUE[i]=1;
		}
	}
	return -1;
}
int main()
{
	char tstr[100];
	while(scanf("%d",&N)==1)
	{
		for(int p1=2;p1<=N;p1++)
		{
			for(int p2=1;p2<p1;p2++)
			{
				scanf("%s",tstr);
				int tc;
				if(sscanf(tstr,"%d",&tc)==1)
				{
					//printf("tc==%d\n",tc);
					MAT[p1][p2]=MAT[p2][p1]=tc;
				}
				else MAT[p1][p2]=MAT[p2][p1]=-1;
			}
		}
		printf("%d\n",solve());
	}
	return 0;
}
