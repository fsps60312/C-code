#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int R,C,DIST[780][780],COST[780],RIDE[780][780],KING;
bool VIS[780];
vector<int>V;
void Bfs(const int &s,int *dist)
{
	for(int i=0;i<R*C;i++)dist[i]=INF,VIS[i]=false;
	queue<int>q;
	dist[s]=0;
	VIS[s]=true;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		static int d[8][2]={{2,1},{1,2},{2,-1},{1,-2},{-2,1},{-1,2},{-2,-1},{-1,-2}};
		for(int i=0;i<8;i++)
		{
			int x=u%C+d[i][0],y=u/C+d[i][1];
			if(x>=C||x<0||y>=R||y<0)continue;
			if(VIS[y*C+x])continue;
			VIS[y*C+x]=true;
			dist[y*C+x]=dist[u]+1;
			q.push(y*C+x);
		}
	}
}
int GetID()
{
	static char r[2],c[2];
	if(scanf("%s%s",c,r)!=2)return -1;
	return (r[0]-'1')*C+(c[0]-'A');
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&R,&C);
	for(int i=0;i<R*C;i++)VIS[i]=false;
	for(int s=0;s<R*C;s++)Bfs(s,DIST[s]);
	KING=GetID();
	int tmp;
	while((tmp=GetID())!=-1)
	{
		V.push_back(tmp);
		printf("%c%c\n",'A'+tmp%C,'1'+tmp/C);
		for(int i=0;i<R*C;i++)
		{
			printf("%d,",DIST[tmp][i]);
			if(i%C==C-1)puts("");
		}
	}
	for(int i=0;i<R*C;i++)COST[i]=0,RIDE[i]=INF;
	for(int i=0;i<V.size();i++)
	{
		for(int t=0;t<R*C;t++)
		{
			RIDE[t]=min(RIDE[t],DIST[V[i]][t]);
			if(COST[t]==INF)continue;
			if(DIST[V[i]][t]==INF)COST[t]=INF;
			else COST[t]+=DIST[V[i]][t];
		}
	}
	int ans=INF;
	for(int t=0;t<R*C;t++)
	{
		int ta=INF;
		for(int m=0;m<R*C;m++)
		{
			if(DIST[m][t]==INF||RIDE[m]==INF)continue;
			ta=min(ta,RIDE[m]+DIST[m][t]+max(abs(KING%C-m%C,KING/C-m/C)));
		}
		ans=min(ans,COST[t]+ta);
	}
	for(int t=0;t<R*C;t++)if(SetT(t)==ans)printf("%c%c\n",'A'+t%C,'1'+t/C);
	printf("%d\n",ans);
	return 0;
}
