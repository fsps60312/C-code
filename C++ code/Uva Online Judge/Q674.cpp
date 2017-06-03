#include<cstdio>
int DP[7490];
int main()
{
	for(int i=0;i<=7489;i++)DP[i]=0;
	DP[0]=1;
	for(int i=0;i+1<=7489;i++)DP[i+1]+=DP[i];
	for(int i=0;i+5<=7489;i++)DP[i+5]+=DP[i];
	for(int i=0;i+10<=7489;i++)DP[i+10]+=DP[i];
	for(int i=0;i+25<=7489;i++)DP[i+25]+=DP[i];
	for(int i=0;i+50<=7489;i++)DP[i+50]+=DP[i];
	static int n;
	while(scanf("%d",&n)==1)printf("%d\n",DP[n]);
	return 0;
}
