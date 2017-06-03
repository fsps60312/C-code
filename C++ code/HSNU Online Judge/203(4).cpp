#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int N,DEQ[100001];
LL L,H[100001],SUM[100001],DP[100001];
multiset<LL>S;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lld",&N,&L)==2)
	{
		S.clear();
//		SUM[0]=0LL;
		for(int i=1;i<=N;i++)
		{
			static LL w;
			scanf("%lld%lld",&H[i],&w);
			SUM[i]=SUM[i-1]+w;
		}
		int l=0,r=-1;
		DEQ[++r]=0;
		H[0]=1e18;
		DP[0]=0LL;
		for(int i=1;i<=N;i++)
		{
			while(r-l+1>=2&&H[i]>=H[DEQ[r]])//q1: why >= instead of >
			{
				S.erase(S.find(DP[DEQ[r-1]]+H[DEQ[r]]));
				r--;
			}
//			if(H[i]<H[DEQ[r]])
//			{
				S.insert(DP[DEQ[r]]+H[i]);
				DEQ[++r]=i;
//			}
			while(SUM[i]-SUM[DEQ[l]]>L)
			{
				S.erase(S.find(DP[DEQ[l]]+H[DEQ[l+1]]));
				if(++DEQ[l]==DEQ[l+1])l++;//because of this so q1
				else S.insert(DP[DEQ[l]]+H[DEQ[l+1]]);
			}
//			for(LL j:S)printf(" %lld",j);puts("");
			DP[i]=*S.begin();
		}
		printf("%lld\n",DP[N]);
	}
	return 0;
}
