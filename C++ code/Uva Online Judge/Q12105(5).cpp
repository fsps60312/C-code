#include<cstdio>
const int INF=2147483647;
const int MATCHES[10]={6,2,5,5,4,5,6,3,7,6};
int N,M;
int DP[101][3000];//match use to make n-first i-digit number mod j
bool getmin(int &a,int b){if(b<a){a=b;return true;}return false;}
void termin(){int a[10];for(int i=0;;i--)a[i]=100;}
int mod(int a){return (a%M+M)%M;}
int POW_MOD[101];
void dfs_print(int d,int m,int fa)
{
	if(d==1)
	{
		printf("%d",m);
		return;
	}
	for(int n=9;n>=0;n--)
	{
		int tm=mod(m-n*POW_MOD[d]);
		if(DP[d-1][tm]<=N-MATCHES[n])
		{
			N-=MATCHES[n];
			if(!fa||n)printf("%d",n);
			dfs_print(d-1,tm,fa&&!n?-1:0);
			return;
		}
	}
	termin();
}
int main()
{
	freopen("in.txt","r",stdin); 
	freopen("out.txt","w",stdout);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d",&M);
		POW_MOD[1]=1%M;
		for(int i=2;i<=N;i++)POW_MOD[i]=mod(POW_MOD[i-1]*10);
		for(int i=1;i<=N;i++)
		{
			for(int j=0;j<M;j++)
			{
				DP[i][j]=N+1;
			}
		}
		for(int i=9;i>=0;i--)
		{
			getmin(DP[1][mod(i)],MATCHES[i]);
		}
		bool changed=true;
		for(int d=1;changed;d++)
		{
			changed=false;
			for(int m=0;m<M;m++)
			{
				int &dp=DP[d][m];
				if(dp==N+1)continue;
				for(int i=9;i>=0;i--)
				{
					if(getmin(DP[d+1][mod(m*10+i)],dp+MATCHES[i]))
					{
						changed=true;
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
			if(DP[d][0]<=N)
			{
				dfs_print(d,0,-1);
				printf("\n");
				//if(VERIFY!=N)termin();
				break;
			}
		}
	}
	return 0;
} 
