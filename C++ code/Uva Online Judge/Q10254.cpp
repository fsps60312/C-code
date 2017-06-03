#include<cstdio>
typedef long long LL;
const LL INF=9223372036854775807LL;
LL N;
LL F4[10001],F3[10001];
int main()
{
	F3[0]=F4[0]=0;
	F3[1]=F4[1]=1;
	for(int i=2;i<=10000;i++)F3[i]=F3[i-1]*2LL+1LL;
	for(int i=2;i<=100;i++)
	{
		F4[i]=INF;
		int k=-1;
		for(int j=1;j<i;j++)if(F3[i-j]+2LL*F4[j]<F4[i])k=j,F4[i]=F3[i-j]+2LL*F4[j];
		printf("F4[%d]=%lld,k=%d\n",i,F4[i],k);
	}
	return 0;
}
