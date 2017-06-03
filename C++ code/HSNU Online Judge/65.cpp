#include<cstdio>
const int INF=2147483647;
int N,M,Q;
int DIST[100][100];
void getmin(int &a,const int &b){if(b<a)a=b;}
void Update(const int &k)
{
	for(int i=0;i<N;i++)
	{
		if(DIST[i][k]==INF)continue;
		for(int j=0;j<N;j++)
		{
			if(DIST[k][j]==INF)continue;
			getmin(DIST[i][j],DIST[i][k]+DIST[k][j]);
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&Q);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=INF;
	for(int i=0;i<N;i++)DIST[i][i]=0;
	for(int i=0;i<M;i++)
	{
		static int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		a--,b--;
		getmin(DIST[a][b],c);
		getmin(DIST[b][a],c);
	}
	for(int k=0;k<N;k++)
	{
		for(int i=0;i<N;i++)
		{
			if(DIST[i][k]==INF)continue;
			for(int j=0;j<N;j++)
			{
				if(DIST[k][j]==INF)continue;
				getmin(DIST[i][j],DIST[i][k]+DIST[k][j]);
			}
		}
	}
	while(Q--)
	{
		static int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		a--,b--;
		if(c>=DIST[a][b])puts("0");
		else
		{
			printf("(%d,%d)",DIST[a][b],c);
			puts("1");
			DIST[a][b]=DIST[b][a]=c;
			Update(a);
			Update(b);
		}
	}
	return 0;
}
