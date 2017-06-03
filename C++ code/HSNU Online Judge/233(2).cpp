#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int &b){if(b>a)a=b;}
int M,N,K,MX[4][1502][1502],GRID[1501][1501],SUM[1501][1501],SQ[1501][1501],HORI[3][1501],VERT[3][1501],DP[1501];
int Sum(const int &r1,const int &c1,const int &r2,const int &c2){return SUM[r2][c2]-SUM[r2][c1-1]-SUM[r1-1][c2]+SUM[r1-1][c1-1];}
int max(const int &a,const int &b,const int &c){return max(a,max(b,c));}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&M,&N,&K)==3)
	{
		for(int i=1;i<=M;i++)for(int j=1;j<=N;j++)scanf("%d",&GRID[i][j]);
		SUM[0][0]=0;
		for(int i=1;i<=M;i++)SUM[i][0]=0;
		for(int i=1;i<=N;i++)SUM[0][i]=0;
		for(int i=1;i<=M;i++)for(int j=1;j<=N;j++)SUM[i][j]=SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1]+GRID[i][j];
		M-=K-1,N-=K-1;
		for(int r=1;r<=M;r++)for(int c=1;c<=N;c++)SQ[r][c]=Sum(r,c,r+K-1,c+K-1);
		for(int j=0;j<4;j++)for(int i=0;i<=M+1;i++)MX[j][i][0]=MX[j][i][N+1]=0;
		for(int j=0;j<4;j++)for(int i=0;i<=N+1;i++)MX[j][0][i]=MX[j][M+1][i]=0;
		//0:upleft, 1:upright, 2:downright, 3:downleft
		for(int r=1;r<=M;r++)for(int c=1;c<=N;c++)MX[0][r][c]=max(MX[0][r-1][c],MX[0][r][c-1],SQ[r][c]);
		for(int r=1;r<=M;r++)for(int c=N;c>=1;c--)MX[1][r][c]=max(MX[1][r-1][c],MX[1][r][c+1],SQ[r][c]);
		for(int r=M;r>=1;r--)for(int c=N;c>=1;c--)MX[2][r][c]=max(MX[2][r+1][c],MX[2][r][c+1],SQ[r][c]);
		for(int r=M;r>=1;r--)for(int c=1;c<=N;c++)MX[3][r][c]=max(MX[3][r+1][c],MX[3][r][c-1],SQ[r][c]);
		int ans=0;
		for(int r=K+1;r<=M;r++)for(int c=K+1;c<=N;c++)
		{
			ans=max(ans,MX[0][r-K][c-K]+MX[1][r-K][c]  +MX[2][r][1]  );
			ans=max(ans,MX[1][r-K][c]  +MX[2][r][c]    +MX[3][1][c-K]);
			ans=max(ans,MX[2][r][c]    +MX[3][r][c-K]  +MX[0][r-K][N]);
			ans=max(ans,MX[3][r][c-K]  +MX[0][r-K][c-K]+MX[1][M][c]  );
		}
//		printf("ans=%d\n",ans);ans=0;
		for(int r=1;r<=M;r++){VERT[0][r]=0;for(int c=1;c<=N;c++)getmax(VERT[0][r],SQ[r][c]);}
		for(int c=1;c<=N;c++){HORI[0][c]=0;for(int r=1;r<=M;r++)getmax(HORI[0][c],SQ[r][c]);}
		DP[0]=0;
		for(int cnt=1;cnt<3;cnt++)
		{
			for(int r=1;r<=M;r++)DP[r]=max(DP[r-1],VERT[cnt-1][r]),VERT[cnt][r]=-1;
			for(int r=M;r-K>=1;r--)
			{
				if(DP[r-K]==-1)continue;
				getmax(VERT[cnt][r],DP[r-K]+VERT[0][r]);
			}
			for(int c=1;c<=N;c++)DP[c]=max(DP[c-1],HORI[cnt-1][c]),HORI[cnt][c]=-1;
			for(int c=N;c-K>=1;c--)
			{
				if(DP[c-K]==-1)continue;
				getmax(HORI[cnt][c],DP[c-K]+HORI[0][c]);
			}
		}
		for(int r=1;r<=M;r++)getmax(ans,VERT[2][r]);
		for(int c=1;c<=N;c++)getmax(ans,HORI[2][c]);
		printf("%d\n",ans);
		break;
	}
	return 0;
}
