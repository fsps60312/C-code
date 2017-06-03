#include<cstdio>
const int INF=2147483647;
const int MATCHES[10]={6,2,5,5,4,5,6,3,7,6};
int N,M;
int DP[10][101][3000];//match use to make n-first i-digit number mod j
bool getmin(int &a,int b){if(b<a){a=b;return true;}return false;}
void termin(){int a[10];for(int i=0;;i--)a[i]=100;}
int get_max_num(int d,int m,int n)
{
	int ans;
	for(ans=9;ans>=0;ans--)
	{
		if(DP[ans][d][m]==n)return ans;
	}
	return ans;
}
int get_max_num(int d,int m)
{
	int n;
	for(n=9;n>=0;n--)
	{
		if(DP[n][d][m]<=N)return n;
	}
	return n;
}
int get_maxd()
{
	int d;
	for(d=N/2;d>=1;d--)
	{
		if(get_max_num(d,0)!=-1)return d;
	}
	return d;
}
int main()
{
	//freopen("in.txt","r",stdin); 
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
			getmin(DP[i][1][i%M],MATCHES[i]);
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
						if(getmin(DP[n][d+1][(m*10+i)%M],dp+MATCHES[i]))changed=true;
					}
				}
			}
		}
		printf("Case %d: ",kase++);
		int d=get_maxd(),m=0;
		if(d==0)printf("-1\n");
		else
		{
			for(;d>=1;d--)
			{
				int n=get_max_num(d,m,N);
				if(n==-1)termin();
				printf("%d",n);
				N-=MATCHES[n];
				m-=n;
				m=(m%M+M)%M;
			}
			printf("\n");
		}
	}
	return 0;
} 
