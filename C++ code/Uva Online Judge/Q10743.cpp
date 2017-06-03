#include<cstdio>
int T,N;
int GetDP(int sum,int lastlen)
{
	sum-=lastlen;
	if(sum==0)return 1;
	int ans=0;
	for(int i=1;i<=sum;i++)ans+=GetDP(sum,i)*(lastlen+i-1);
	return ans;
}
int main()
{
	for(int i=1;i<=10;i++)
	{
		printf("sum=%d\n",i);
		for(int j=1;j<=i;j++)printf("%5d",GetDP(i,j));puts("");
	}
//	scanf("%d",&T);
//	while(T--)
	for(N=1;N<=20;N++)
	{
//		scanf("%d",&N);
		int ans=0;
		for(int i=1;i<=N;i++)ans+=GetDP(N,i);
		printf("%d\n",ans);
	}
	return 0;
}
