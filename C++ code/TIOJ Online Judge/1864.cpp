#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
int N,S[1000];
LL CNT[2][100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		for(int i=1;i<=S[0];i++)CNT[0][i]=0LL;
		CNT[0][S[0]]=1LL;
		int d=0;
		for(int i=1;i<N;i++,d^=1)
		{
			for(int j=1;j<=S[0];j++)CNT[d^1][j]=0LL;
			for(int j=1;j<=S[0];j++)if(CNT[d][j])
			{
				(CNT[d^1][j]+=CNT[d][j]*(S[i]-j+1))%=MOD;
				for(int k=1;k<j;k++)(CNT[d^1][k]+=CNT[d][j])%=MOD,(CNT[d^1][j-k]+=CNT[d][j])%=MOD;
			}
		}
		LL ans=0LL;
		for(int i=1;i<=S[0];i++)
		{
			(ans+=CNT[d][i]*(1+i/2)%MOD*(i/2))%=MOD;
			if(i%2==0)(ans-=CNT[d][i]*(i/2))%=MOD;
		}
		printf("%lld\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}
