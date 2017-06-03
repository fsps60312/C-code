#include<cstdio>
const int INF=2147483647;
const int MATCHES[10]={6,2,5,5,4,5,6,3,7,6};
int N,M;
int DP[10][101][3000];//match use to make n-first i-digit number mod j
struct Pre
{
	int a,b,c;
}PRE[10][101][3000];
bool getmin(int &a,int b){if(b<a){a=b;return true;}return false;}
void termin(){int a[10];for(int i=0;;i--)a[i]=100;}
int mod(int a){return (a%M+M)%M;}
int VERIFY;
void dfs_print(int n,int d,int m)
{
	if(d==0)return;
	Pre &p=PRE[n][d][m];
	dfs_print(p.a,d-1,p.b);
	VERIFY+=MATCHES[p.c];
	printf("%d",p.c);
}
int main()
{
	freopen("in.txt","r",stdin); 
	freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d",&M);
		for(int n=0;n<=9;n++)
		{
			for(int i=1;i<=N;i++)
			{
				for(int j=0;j<M;j++)
				{
					DP[n][i][j]=N+1;
				}
			}
		}
		for(int i=0;i<=9;i++)
		{
			if(getmin(DP[i][1][i%M],MATCHES[i]))
			{
				PRE[i][1][i%M]=(Pre){-1,-1,i};
			}
		}
		for(int n=1;n<=9;n++)
		{
			bool changed=true;
			for(int d=1;changed;d++)
			{
				changed=false;
				for(int m=0;m<M;m++)
				{
					int &dp=DP[n][d][m];
					if(dp==N+1)continue;
					for(int i=0;i<=9;i++)
					{
						if(getmin(DP[n][d+1][(m*10+i)%M],dp+MATCHES[i]))
						{
							PRE[n][d+1][(m*10+i)%M]=(Pre){n,m,i};
							changed=true;
						}
					}
				}
			}
		}
		printf("Case %d: ",kase++);
		for(int d=N;;d--)
		{
			if(d==0)
			{
				printf("-1\n");
				break;
			}
			for(int n=9;n>=0;n--)
			{
				if(DP[n][d][0]!=N+1)
				{
					VERIFY=0;
					dfs_print(n,d,0);
					printf("\n");
					//if(VERIFY!=N)termin();
					goto index1;
				}
			}
		}
		index1:;
	}
	return 0;
} 
