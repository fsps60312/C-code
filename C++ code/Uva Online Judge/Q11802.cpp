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
LL BASE[501],POWER[501];
LL CntZeros(LL n,const LL &b)
{
	LL ans=0LL;
	while(n>1)ans+=(n/=b);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=500;i++)BASE[i]=-1LL;
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
	for(int i=0;i<(int)P.size();i++)
	{
		for(LL v=P[i],cnt=1LL;v<=500LL;v*=P[i],cnt++)BASE[v]=P[i],POWER[v]=cnt;
	}
//	for(const LL &v:P)printf("%lld\n",v);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lld%lld",&N,&K);
		LL ans=0LL;
		for(LL b=2LL;;b++)if(BASE[b]!=-1LL)
		{
			printf("b=%lld\n",b);
			if(true)
			{
				const LL &zeros=CntZeros(N,BASE[b])/POWER[b];
				if(zeros<K)break;
				if(zeros>K)continue;
			}
			puts("pass");
			LL ta=1LL;
			for(int i=0;P[i]<BASE[b];i++)
			{
				LL cnt=1LL,now=P[i];
				while(CntZeros(N,now)>=K)cnt++,now*=P[i];
				(ta*=cnt)%=MOD;
			}
			printf("ta=%lld\n",ta);
			(ans+=ta)%=MOD;
		}
		static int kase=1;
		printf("Case %d: %lld\n",kase++,ans);
	}
	return 0;
}
