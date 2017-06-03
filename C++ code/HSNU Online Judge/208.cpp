#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int R,C,DIST[781][780],VIS[780],COST[780],KASE=0,KING;
bool HASV[780];
vector<int>V;
int Bfs(const int &s,int *dist)
{
	for(int i=0;i<R*C;i++)dist[i]=INF;
	KASE++;
	queue<int>q;
	dist[s]=0;
	VIS[s]=KASE;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(HASV[u])return dist[u];
		static int d[8][2]={{2,1},{1,2},{2,-1},{1,-2},{-2,1},{-1,2},{-2,-1},{-1,-2}};
		for(int i=0;i<8;i++)
		{
			int x=u%C+d[i][0],y=u/C+d[i][1];
			if(x>=C||x<0||y>=R||y<0)continue;
			if(VIS[y*C+x]==KASE)continue;
			VIS[y*C+x]=KASE;
			dist[y*C+x]=dist[u]+1;
			q.push(y*C+x);
		}
	}
	return INF;
}
int GetID()
{
	static char r[2],c[2];
	if(scanf("%s%s",c,r)!=2)return -1;
	return (r[0]-'1')*C+(c[0]-'A');
}
int SetT(const int &t)
{
	int ans=0;
	for(int i=0;i<V.size();i++)
	{
		if(DIST[V[i]][t]==INF)return INF;
		ans+=DIST[V[i]][t];
	}
	int a=INF;
	for(int i=0;i<R*C;i++)if(COST[i]!=INF&&DIST[i][t]!=INF)a=min(a,COST[i]+DIST[i][t]+max(abs(KING%C-i%C),abs(KING/C-i/C)));
	return ans+a;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&R,&C);
	for(int i=0;i<R*C;i++)VIS[i]=0,HASV[i]=false;
	for(int s=0;s<R*C;s++)Bfs(s,DIST[s]);
	KING=GetID();
	int tmp;
	while((tmp=GetID())!=-1)
	{
		V.push_back(tmp);
		HASV[tmp]=true;
		printf("%c%c\n",'A'+tmp%C,'1'+tmp/C);
		for(int i=0;i<R*C;i++)
		{
			printf("%d,",DIST[tmp][i]);
			if(i%C==C-1)puts("");
		}
	}
	for(int s=0;s<R*C;s++)COST[s]=Bfs(s,DIST[780]);
	int ans=INF;
	for(int t=0;t<R*C;t++)
	{
		ans=min(ans,SetT(t));
	}
	for(int t=0;t<R*C;t++)if(SetT(t)==ans)printf("%c%c\n",'A'+t%C,'1'+t/C);
	printf("%d\n",ans);
	return 0;
}
