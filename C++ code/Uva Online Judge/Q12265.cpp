#include<cstdio>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
int T,N,M,LIMIT;
char MAP[1000][1001];
int H[1001][1000],DP[1001][1001],CNT[1999];
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<1000;i++)H[1000][i]=DP[1000][i]=DP[i][1000]=-1;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int y=0;y<N;y++)scanf("%s",MAP[y]);
		for(int x=0;x<M;x++)H[x][N]=DP[x][N]=-1;
		for(int y=N-1;y>=0;y--)
		{
			DP[M][y]=-1;
			for(int x=0;x<M;x++)
			{
				H[x][y]=MAP[y][x]=='#'?-1:H[x][y+1]+1;
				DP[x][y]=-1;
			}
		}
		LIMIT=N+M-2;
		for(int n=0,x,y,i,j,k;n<=LIMIT;n++)
		{
			CNT[n]=0;
			for(x=max(0,n-N),y=min(n,N);x<=n&&x<M;x++,y--)
			{
				for(i=x,j=H[i][y];MAP[y][i]=='.';i++)
				{
					getmin(j,H[i][y]);
					for(k=0;k<=j;k++)
					getmax(DP[i][y+k],i-x+k);
				}
			}
		}
		for(int i=N-1;i>=0;i--)
		{
			for(int j=M-1;j>=0;j--)
			{
				if(MAP[i][j]=='#')
				{
					continue;
				}
				int &dp=DP[j][i];
				CNT[dp]++;
			}
		}
		for(int i=0;i<=LIMIT;i++)
		{
			if(!CNT[i])continue;
			printf("%d x %d\n",CNT[i],4+i*2);
		}
	}
	return 0;
}
