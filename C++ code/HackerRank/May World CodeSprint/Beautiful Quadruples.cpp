#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
int S[4];
LL CNT[6001],TOTAL;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<4;i++)scanf("%d",&S[i]);
	sort(S,S+4);
	for(int i=0;i<=6000;i++)CNT[i]=0LL;
	TOTAL=0LL;
	for(int i=1;i<=S[2];i++)for(int j=i;j<=S[3];j++)++CNT[i^j],++TOTAL;
	LL ans=0LL;
	for(int b=1;b<=S[1];b++)
	{
		for(int a=1;a<=b&&a<=S[0];a++)
		{
			ans+=TOTAL;
			ans-=CNT[a^b];
		}
		for(int j=b;j<=S[3];j++)--CNT[b^j],--TOTAL;
	}
	printf("%lld\n",ans);
	return 0;
}
