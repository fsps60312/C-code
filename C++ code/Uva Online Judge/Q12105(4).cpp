#include<cstdio>
const int INF=2147483647;
const int MATCHES[10]={6,2,5,5,4,5,6,3,7,6};
int N,M;
int DP[10][101][3000];//match use to make n-first i-digit number mod j
bool getmin(int &a,int b){if(b<a){a=b;return true;}return false;}
void termin(){int a[10];for(int i=0;;i--)a[i]=100;}
int mod(int a){return (a%M+M)%M;}
int POW_MOD[101];
void dfs_print(int n,int d,int m)
{
	if(d==0)return;
	printf("%d",n);
	N-=MATCHES[n];
	m=mod(m-n*POW_MOD[d]);
	for(int i=9;i>=0;i--)
	{
		if(DP[i][d-1][m]<=N)
		{
			dfs_print(i,d-1,m);
			return;
		}
	}
	termin();
}
int main()
{
//	freopen("in.txt","r",stdin); 
//	freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d",&M);
		POW_MOD[1]=1%M;
		for(int i=2;i<=N;i++)POW_MOD[i]=mod(POW_MOD[i-1]*10);
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
		for(int i=9;i>=0;i--)
		{
			getmin(DP[i][1][mod(i)],MATCHES[i]);
		}
		bool changed=true;
		for(int d=1;changed;d++)
		{
			changed=false;
			for(int n=9;n>=0;n--)
			{
				for(int m=0;m<M;m++)
				{
					int &dp=DP[n][d][m];
					if(dp==N+1)continue;
					for(int i=9;i>=0;i--)
					{
						if(getmin(DP[i][d+1][mod(i*POW_MOD[d+1]+m)],dp+MATCHES[i]))
						{
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
				if(DP[n][d][0]<=N)
				{
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
