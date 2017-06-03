#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
LL Pow(LL a,LL p)
{
	LL ans=1;
	for(;p;p>>=1,(a*=a)%=MOD)if(p&1)(ans*=a)%=MOD;
	return ans;
}
LL ASUM[1000000],X[1000000],Y[1000000];
int N,PRE[1000000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lld%lld",&X[i],&Y[i]);
		for(int i=0;i<N;i++)X[i+N]=X[i],Y[i+N]=Y[i];
		reverse(X,X+N*2),reverse(Y,Y+N*2);
		ASUM[0]=0;
		for(int i=1;i<N*2;i++)ASUM[i]=X[i-1]*Y[i]-X[i]*Y[i-1];
		for(int i=1;i<N*2;i++)ASUM[i]+=ASUM[i-1];
		const LL total_area=ASUM[N];
		const LL ans=0;
		for(int i=N,j=2;i<N*2;i++)
		{
			while(((ASUM[i]-ASUM[j])+(X[i]*Y[j]-X[j]*Y[i]))*2>total_area)++j;
			PRE[i]=j;
			(ans+=((j+N)-(i+2)+1)*(/*SUM[i+2]~SUM[j+N]*/-SUM[i])+(XSUM[j+N]-XSUM[i+1])*Y[i]-X[i]*(YSUM[j+N]-YSUM[i+1]))%=MOD;
			(ans-=((i-2)-j+1)*(SUM[i]/*-SUM[j]~SUM[i-2]*/))%=MOD;
		}
		LL ans=0;
		for(int i=0;i<N;i++)for(int j=i+2;j<=i+N-2;j++)
		{
			assert((ASUM[j]-ASUM[i])+(X[j]*Y[i]-X[i]*Y[j])>0);
			(ans+=abs(abs((ASUM[j]-ASUM[i])+(X[j]*Y[i]-X[i]*Y[j]))-abs((ASUM[i+N]-ASUM[j])+(X[i+N]*Y[j]-X[j]*Y[i+N]))));
		}
		ans%=MOD;
		printf("%lld\n",(ans*Pow(2LL,MOD-2)%MOD+MOD)%MOD);
	}
	return 0;
}
