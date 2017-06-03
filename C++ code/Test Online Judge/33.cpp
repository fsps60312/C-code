#include<cstdio>
typedef long long LL;
LL F[31];
int main()
{
	F[0]=F[1]=1LL;
	for(int i=2;i<=30;i++)F[i]=F[i-2]+F[i-1];
	for(int i=0;i<=30;i++)printf("%lld\n",F[i]);
	return 0;
}
