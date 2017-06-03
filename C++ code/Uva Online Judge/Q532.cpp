#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
int L,R,C,START,EXIT;
char S[27000];
int DIST[27000];
int Solve()
{
	for(int i=0;i<L*R*C;i++)DIST[i]=-1;
	queue<int>q;
	DIST[START]=0,q.push(START);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		assert(DIST[u]!=-1);
		if(u==EXIT)return DIST[u];
		const int nowl=u/(R*C),nowr=u%(R*C)/C,nowc=u%C;
//		printf("(%d,%d,%d):%d\n",nowl,nowr,nowc,DIST[u]);
		static int d[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
		for(int i=0;i<6;i++)
		{
			const int nxtl=nowl+d[i][0],nxtr=nowr+d[i][1],nxtc=nowc+d[i][2];
			int nxtu=-1;
			if(nxtl<0||nxtl>=L||nxtr<0||nxtr>=R||nxtc<0||nxtc>=C||S[nxtu=nxtl*R*C+nxtr*C+nxtc]=='#')continue;
			assert(nxtu!=-1);
			if(DIST[nxtu]!=-1)continue;
			DIST[nxtu]=DIST[u]+1;
			q.push(nxtu);
		}
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		scanf("%d%d%d",&L,&R,&C);
		if(!(L|R|C))break;
		START=EXIT=-1;
		for(int i=0;i<L*R*C;i++)
		{
			char &c=S[i];
			bool found=false;
			while(!found)
			{
				found=true;
				c=getchar();
				switch(c)
				{
					case'#':
					case'.':break;
					case'S':START=i;break;
					case'E':EXIT =i;break;
					default:found=false;break;
				}
			}
		}
		assert(START!=-1&&EXIT!=-1);
		const int ans=Solve();
		if(ans==-1)puts("Trapped!");
		else printf("Escaped in %d minute(s).\n",ans);
	}
	return 0;
}
