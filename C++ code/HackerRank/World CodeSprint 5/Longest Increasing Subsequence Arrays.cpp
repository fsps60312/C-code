#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
int N,M;
LL Pow(LL a,LL p)
{
	LL ans=1;
	for(;p;p>>=1,(a*=a)%=MOD)if(p&1)(ans*=a)%=MOD;
	return ans;
}
LL LEVEL[500001],REVLV[500001],PN0[500001],PN1[500001];
LL C(const LL a,const LL b)
{
	return LEVEL[a]*REVLV[b]%MOD*REVLV[a-b]%MOD;
}
int main()
{
//	freopen("in.txt","r",stdin);
	LEVEL[0]=1,REVLV[0]=1;
	for(int i=1;i<=500000;i++)LEVEL[i]=LEVEL[i-1]*i%MOD,REVLV[i]=Pow(LEVEL[i],MOD-2);
//	for(int i=0;i<=500000;i++)
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&M,&N);
		LL ans=0;
		for(int loc=N;loc<=M;loc++)
		{
//			printf("%lld*%lld*C(%d,%d)=%lld\n",Pow(N-1,loc-N),Pow(N,M-loc),loc,N,C(loc,N));
			(ans+=Pow(N-1,loc-N)*Pow(N,M-loc)%MOD*C(loc-1,N-1))%=MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
