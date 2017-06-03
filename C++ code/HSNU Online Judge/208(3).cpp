#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int R,C;
int GetLoc()
{
	static char c[2];
	static int r;
	if(scanf("%s%d",c,&r)!=2)return -1;
	r--;
	return r*C+(c[0]-'A');
}
int KING;
vector<int>KNIGHT;
void Bfs(const int source,int *dist)
{
	for(int i=0;i<R*C;i++)dist[i]=INF;
	queue<int>q;
	q.push(source);dist[source]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		static int d[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
		for(int i=0;i<8;i++)
		{
			const int r=u/C+d[i][0],c=u%C+d[i][1];
			if(r>=R||r<0||c>=C||c<0)continue;
			if(dist[u]+1<dist[r*C+c])
			{
				dist[r*C+c]=dist[u]+1;
				q.push(r*C+c);
			}
		}
	}
}
int DIST[780][780];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&R,&C);
	for(int i=0;i<R*C;i++)Bfs(i,DIST[i]);
	KING=GetLoc();
	static int tmp;
	while((tmp=GetLoc())!=-1)KNIGHT.push_back(tmp);
//	printf("knight.sz: %d\n",KNIGHT.size());
	int ans=INF;
	for(int dest=0;dest<R*C;dest++)
	{
		bool valid=true;
		int sum=0;
		for(const int u:KNIGHT)
		{
			if(DIST[u][dest]==INF){valid=false;break;}
			sum+=DIST[u][dest];
		}
//		printf("sum=%d\n",sum);
		if(!valid)continue;
		if(DIST[KING][dest]!=INF)for(const int u:KNIGHT)if(DIST[u][KING]!=INF)getmin(ans,sum-DIST[u][dest]+DIST[u][KING]+DIST[KING][dest]);
		static int d[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
		for(int i=0;i<8;i++)
		{
			const int r=KING/C+d[i][0],c=KING%C+d[i][1];
			if(r>=R||r<0||c>=C||c<0||DIST[r*C+c][dest]==INF)continue;
			for(const int u:KNIGHT)if(DIST[u][r*C+c]!=INF)getmin(ans,1+sum-DIST[u][dest]+DIST[u][r*C+c]+DIST[r*C+c][dest]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
