#include<cstdio>
void getmin(int &a,const int b){if(b<a)a=b;}
int N,K,M,W[2001];
int BUS[2001][2001],REMAIN[2001][2001];
void Update(const int i,const int j,const int bus,const int remain)
{
	if(bus>BUS[i][j]||(bus==BUS[i][j]&&remain<=REMAIN[i][j]))return;
	BUS[i][j]=bus,REMAIN[i][j]=remain;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&K,&M)==3)
	{
		for(int i=1;i<=N;i++)scanf("%d",&W[i]);
		for(int i=0;i<=N;i++)for(int j=0;j<=N;j++)BUS[i][j]=REMAIN[i][j]=4000;
		BUS[0][0]=REMAIN[0][0]=0;
		for(int i=1;i<=N;i++)
		{
			BUS[i][0]=0;
			REMAIN[i][0]=0;
			for(int j=1;j<=i;j++)
			{
				BUS[i][j]=BUS[i-1][j];
				REMAIN[i][j]=REMAIN[i-1][j];
				if(REMAIN[i-1][j-1]>=W[i])Update(i,j,BUS[i-1][j-1],REMAIN[i-1][j-1]-W[i]);
				else if(M>=W[i])Update(i,j,BUS[i-1][j-1]+1,M-W[i]);
			}
		}
		int ans=0;
		while(ans+1<=N&&BUS[N][ans+1]<=K)ans++;
		printf("%d\n",ans);
	}
	return 0;
}
