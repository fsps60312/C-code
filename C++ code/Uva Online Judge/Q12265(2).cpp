#include<cstdio>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
int T,N,M,LIMIT;
char MAP[1000][1001];
int H[1000][1001],W[1001][1000],DP[1001][1001],CNT[1999];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int y=0;y<N;y++)
		{
			DP[M][y]=W[M][y]=-1;
			scanf("%s",MAP[y]);
		}
		for(int x=0;x<M;x++)H[x][N]=DP[x][N]=-1;
		for(int y=N-1;y>=0;y--)
		{
			for(int x=M-1;x>=0;x--)
			{
				if(MAP[y][x]=='#')H[x][y]=W[x][y]=-1;
				else H[x][y]=H[x][y+1]+1,W[x][y]=W[x+1][y]+1;
				DP[x][y]=-1;
			}
		}
		LIMIT=N+M-2;
		for(int n=0,x,y,i,j;n<=LIMIT;n++)
		{
			CNT[n]=0;
			for(x=max(0,n-N),y=min(n,N);x<=n&&x<M;x++,y--)
			{
				for(i=x,j=H[i][y];MAP[y][i]=='.';i++)
				{
if(i==M)return 0;
					getmin(j,H[i][y]);
					getmax(DP[i][y+j],i-x+j);
				}
			}
		}
		for(int i=N-1;i>=0;i--)
		{
			for(int j=M-1;j>=0;j--)
			{
				if(MAP[i][j]=='#')continue;
				int &dp=DP[j][i],&w=W[j][i],&h=H[j][i];
				getmax(dp,DP[j+w][i]-w);
				getmax(dp,DP[j][i+h]-h);
if(dp<0)return 0;
				CNT[dp]++;
			}
		}
//		for(int i=0;i<N;i++)
//		{
//			for(int j=0;j<M;j++)
//			{
//				printf("%c",'0'+W[j][i]);
//			}printf("\n");
//		}
		for(int i=0;i<=LIMIT;i++)
		{
			if(!CNT[i])continue;
			printf("%d x %d\n",CNT[i],4+i*2);
		}
	}
	return 0;
}
