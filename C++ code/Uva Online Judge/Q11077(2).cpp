#include<cstdio>
#include<cstdlib>
unsigned long long n,k,ans[22][22];
int main()
{
	for(int i=1;i<=21;i++) ans[i][0]=1;//numbers, no need to exchange, only one condition
	for(int i=2;i<=21;i++)
	{
		for(int j=1;j<i;j++)
		{
			//ans[i][j]
			//j+1 number in wrong place
			//C(i,j+1)*(when j+1 numbers, all numbers are in wrong place)
			//ans[i][j]: i numbers, exchange j times
			ans[i][j]=ans[i-1][j]//put x in right place
				+ans[i-1][j-1]*(i-1);//put x in (i-1) wrong place
				//original exchange j-1 times, after put x in wrong place
				//-> exchange j times
		}
	}
	//freopen("in.txt","r",stdin);
	while(scanf("%llu%llu",&n,&k)==2)//n numbers, exchange k times
	{
		if(n==0&&k==0) break;
		printf("%llu\n",ans[n][k]);
	}
	return 0;
}
