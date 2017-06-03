#include<cstdio>
int T,N,A[50],DP[51][51];//N,
bool solve()
{
	int cnt1=0;
	int sum=0;
	for(int i=0;i<N;i++)
	{
		sum+=A[i];
		if(A[i]=1)cnt1++;
	}
	if(cnt1==0)return sum&1;
	if(cnt1==1)
	{
		if(sum&1)return 1;//take 1
		return 1;//merge 1 1
	}
	if(cnt1==2)
	{
		if(sum&1)return 0;
		else return 1;//merge 2 1
	}
	if(cnt1==3)
	{
		if(sum&1)return 1;//merge 1 1
		else return 1;//take 1
	}
	if(cnt1==4)
	{
		if(sum&1)return 1;//merge 2 1
		else return 0;
	}
	if(cnt1==5)
	{
		if(sum&1)return 1;//take 1
		else return 1;//merge 1 1
	}
	if(cnt1==6)
	{
		if(sum&1)return 0;
	}
}
int main()
{
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		printf("Case #%d: %s\n",kase++,solve()?"Alice":"Bob");
	}
	return 0;
}
