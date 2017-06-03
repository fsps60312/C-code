#include<cstdio>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
int T,N,M,LIMIT;
char MAP[1000][1001];
int H[1000][1001],DP[1000][1000],CNT[1999],JY[1000][1001],JX[1001][1000];
int findJY(int x,int y)
{
	int &jy=JY[x][y];//return dj;
	if(jy==y)return y;
	return jy=findJY(x,jy);
}
int findJX(int x,int y)
{
	int &jx=JX[x][y];//return jx;
	if(jx==x)return x;
	return jx=findJX(jx,y);
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int y=0;y<N;y++)scanf("%s",MAP[y]);
		for(int x=0;x<M;x++)H[x][N]=-1,JY[x][N]=N;
		for(int y=N-1;y>=0;y--)
		{
			JX[M][y]=M;
			for(int x=M-1;x>=0;x--)
			{
				if(MAP[y][x]=='#')H[x][y]=-1;
				else H[x][y]=H[x][y+1]+1;
				DP[x][y]=-1;
				JY[x][y]=y;
				JX[x][y]=x;
			}
		}
		LIMIT=N+M-2;
		for(int n=0,x,y,i,j,k;n<=LIMIT;n++)
		{
			CNT[n]=0;
			for(x=max(0,n-(N-1)),y=min(n,N-1);x<=n&&x<M;x++,y--)
			{
				//if(DP[x][y]>=0)continue;
				//printf("%d %d\n",x,y);
				for(i=findJX(x,y),j=2147483647;MAP[y][i]=='.';)
				{
					getmin(j,H[i][y]);
					for(k=findJY(i,y);k<=y+j;k=findJY(i,k))DP[i][k]=i-x+k-y,JY[i][k]=k+1;//if(DP[i][k]<0)
					if(H[i][y]==j)JX[i][y]=++i;
					else i++;
				}
			}
//printf("%d\n",n);
//for(int i=0;i<N;i++)
//{
//	for(int j=0;j<M;j++)printf("%c",'0'+DP[j][i]);
//	printf("\n");
//}
		}
		for(int i=N-1;i>=0;i--)
		{
			for(int j=M-1;j>=0;j--)
			{
				if(MAP[i][j]=='#')continue;
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
