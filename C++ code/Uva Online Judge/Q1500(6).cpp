#include<cstdio>
int T,N,A[50],DP[49+50000+1][51];
int getDP(int s,int c1)
{
	if(s==1)s--,c1++;
	int &dp=DP[s][c1];
	if(dp!=-1)return dp;
	if(s>=1&&!getDP(s-1,c1))return dp=true;//m s+s or t s
	if(c1>=1&&!getDP(s,c1-1))return dp=true;//t c
	if(s>=1&&c1>=1&&!getDP(s+1,c1-1))return dp=true;//m s+c
	if(c1>=2)
	{
		if(s>=1&&!getDP(s+3,c1-2))return dp=true;
		else if(s==0&&!getDP(2,c1-2))return dp=true;//m c+c
	}
	return dp=false;
}
int main()
{
	for(int i=0;i<=50;i++)for(int j=0;j<=50049;j++)DP[j][i]=-1;
	DP[0][0]=false;
//	int a,b,c;while(scanf("%d%d%d",&a,&b,&c)==3)printf("%d\n",getDP(a,b,c));
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&N);
		int sum=0,c1=0;
		for(int i=0;i<N;i++)
		{
			int &v=A[i];
			scanf("%d",&v);
			if(v==1)c1++;
			else sum+=v+1;
		}
		if(sum)sum--;
		printf("Case #%d: %s\n",kase++,getDP(sum,c1)?"Alice":"Bob");
	}
	return 0;
}
