#include<cstdio>
int T,N,A[50];
bool DP[49+50000][51];//steps,1
bool getDP(int step,int cnt1)
{
	if(step<0||cnt1<0)return false;
	if(step==1)cnt1=0;
	bool &dp=DP[step][cnt1];
	if(cnt1==0)return dp=step&1;
	if(step==1&&cnt1==1)return dp=false;
	if(getDP(step-2,cnt1-1))return dp=true;
	if(getDP(step-1,cnt1-2))return dp=true;
	if(getDP(step-1,cnt1))return dp=true;
	return dp=false;
}
int main()
{
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&N);
		int c1=0,step=N-1;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&A[i]);
			step+=A[i];
			if(A[i]==1)c1++;
		}
		for(int i=0;i<=step;i++)for(int j=0;j<=c1;j++)DP[i][j]=-1;
		printf("Case #%d: %s\n",kase++,getDP(step,c1)?"Alice":"Bob");
	}
	return 0;
}
