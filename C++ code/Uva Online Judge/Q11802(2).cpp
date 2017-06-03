#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL N,K;
vector<LL>P;
int main()
{
//	freopen("in.txt","r",stdin);
	P.push_back(2LL),P.push_back(3LL);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2LL;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j]!=0LL;j++);
		}while(P[i]%P[j]==0LL);
		if(P[i]>=500LL)break;
	}
//	printf("%d\n",(int)P.size());
//	for(const LL &v:P)printf("%lld\n",v);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lld%lld",&N,&K);
		LL ans1=1LL,ans2=1LL;
		for(int i=0;;i++)
		{
			assert(i<(int)P.size());
			LL power=0LL;
			{LL n=N;while(n)(power+=(n/=P[i]));}
			const LL &up=power/K,&down=power/(K+1LL);
			if(up==0LL)break;
			(ans1*=(up+1LL))%=MOD;
			(ans2*=(down+1LL))%=MOD;
		}
		static int kase=1;
		printf("Case %d: %lld\n",kase++,(ans1-ans2+MOD)%MOD);
	}
	return 0;
}
