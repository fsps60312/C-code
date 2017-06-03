#include<cstdio>
#define LL long long
const LL MOD=1000000003LL;
int N,K,V[51];
void getmax(int &a,int b){if(b>a)a=b;}
LL DP[51][51];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2&&(N||K))
	{
		for(int i=1;i<=N;i++)scanf("%d",V+i);
		LL ans=0LL;
		bool reach0=false;
		for(int digit=30,d=1<<30;digit>=0;digit--,d>>=1)
		{
			for(int i=0;i<=N;i++)for(int j=0;j<=N;j++)DP[i][j]=0LL;
			DP[0][0]=1LL;
			int cnt=0;
			for(int i=1;i<=N;i++)
			{
				if(d&V[i])
				{
					cnt++;
					for(int j=0;j<=cnt;j++)//use 1
					{
						DP[i][j]+=DP[i-1][j]*(V[i]-d+1);
						DP[i][j]%=MOD;
					}
					DP[i][1]+=DP[i-1][0];
					DP[i][1]%=MOD;
					for(int j=2;j<=cnt;j++)//use 0
					{
						DP[i][j]+=DP[i-1][j-1]*d;
						DP[i][j]%=MOD;
					}
					V[i]-=d;
				}
				else
				{
					for(int j=1;j<=cnt;j++)
					{
						DP[i][j]+=DP[i-1][j-1]*(V[i]+1);
						DP[i][j]%=MOD;
					}
				}
			}
			bool differ=(cnt&1)^((K&d)>>digit);
			for(int i=differ?1:2;i<=cnt;i+=2)
			{
				ans+=DP[N][i];
				ans%=MOD;
			}
			if(differ)break;
			if(digit==0)reach0=true;
		}
		if(reach0)ans++;//no need to adjust
		printf("%lld\n",ans);
	}
	return 0;
}
