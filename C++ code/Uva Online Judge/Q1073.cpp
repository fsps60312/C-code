#include<cstdio>
#define LL long long
int N;
int ANS[498];
LL solve()
{
	if(N<4||N%2)return 0;
	return ANS[(N-4)/2];
}
int main()
{
	ANS[0]=1;
	for(int i=1;i<498;i++)
	{
		ANS[i]=ANS[i-1]*(3+i);
	}
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		printf("Case %d: %lld\n",kase++,solve());
	}
	return 0;
}
