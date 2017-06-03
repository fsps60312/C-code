#include<cstdio>
#include<cassert>
using namespace std;
long long ANS[26];
int main()
{
//	freopen("in.txt","r",stdin);
	ANS[0]=1,ANS[1]=1,ANS[2]=2,ANS[3]=7;
	for(int i=4;i<=25;i++)
	{
		ANS[i]=0;
		ANS[i]+=ANS[i-1];
		ANS[i]+=ANS[i-2];
		ANS[i]+=ANS[i-3]*4;
		ANS[i]+=ANS[i-4]*2;
	}
	int N;
	while(scanf("%d",&N)==1)
	{
		printf("%lld\n",ANS[N]);
	}
	return 0;
}
