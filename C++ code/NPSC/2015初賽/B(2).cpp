#include<cstdio>
#include<map>
using namespace std;
int N,M;
char S[501][501];
int ASUM[501][501],CSUM[501][501];
int Asum(int r1,int r2,int c1,int c2){return ASUM[r2][c2]-ASUM[r1-1][c2]-ASUM[r2][c1-1]+ASUM[r1-1][c1-1];}
int Csum(int r1,int r2,int c1,int c2){return CSUM[r2][c2]-CSUM[r1-1][c2]-CSUM[r2][c1-1]+CSUM[r1-1][c1-1];}
void getmax(int &a,const int b){if(b>a)a=b;}
int VERSION[250001],VALUE[250001],VNUM;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
		{
			char &c=S[i][j];
			do
			{
				scanf("%c",&c);
			}while(c<'A'||c>'C');
		}
		for(int i=0;i<=500;i++)ASUM[i][0]=ASUM[0][i]=0,CSUM[i][0]=CSUM[0][i]=0;
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
		{
			ASUM[i][j]=ASUM[i-1][j]+ASUM[i][j-1]-ASUM[i-1][j-1]+(S[i][j]=='A'?1:0);
			CSUM[i][j]=CSUM[i-1][j]+CSUM[i][j-1]-CSUM[i-1][j-1]+(S[i][j]=='C'?1:0);
		}
		int ans=0;
		for(int i=0;i<=N*M*2;i++)VERSION[i]=0;
		VNUM=0;
		for(int up=1;up<=N;up++)
		{
			for(int down=up;down<=N;down++)
			{
				VNUM++;
				for(int i=1;i<=M;i++)
				{
					const int dif=(Asum(up,down,1,i)-Csum(up,down,1,i))+N*M;
					if(VERSION[dif]!=VNUM)VERSION[dif]=VNUM,VALUE[dif]=i;
					else getmax(ans,(down-up+1)*(i-VALUE[dif]));
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
