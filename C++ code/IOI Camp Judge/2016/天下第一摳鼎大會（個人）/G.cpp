#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
int N,K;
LL S[10000],SUM0[10001],SUM1[10001];
LL Score(const int l,const int r)
{
	return SUM1[l]-SUM1[r+1]-(LL)(r-l+1LL)*SUM0[r+1];
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		SUM0[N]=SUM1[N]=0LL;
		for(int i=N-1;i>=0;i--)SUM0[i]=S[i]+SUM0[i+1],SUM1[i]=SUM0[i]+SUM1[i+1];
//		for(int i=0;i<N;i++)printf("%lld ",SUM0[i]);puts("");
//		for(int i=0;i<N;i++)printf("%lld ",SUM1[i]);puts("");
//		for(int i=0;i<N;i++)for(int j=i;j<N;j++)printf("(%d,%d)=%lld\n",i,j,Score(i,j));
	}
	return 0;
}
