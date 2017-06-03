#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
vector<LL>P;
LL N;
int main()
{
	P.push_back(2LL),P.push_back(3LL);
	for(LL i=2LL,j;;i++)
	{
		P.push_back(P[i-1LL]);
		do
		{
			P[i]+=2LL;
			for(j=0LL;P[j]*P[j]<=P[i]&&P[i]%P[j]!=0LL;j++);
		}while(P[i]%P[j]==0LL);
		if(P[i]>=65536LL)break;
	}
	while(scanf("%lld",&N)==1&&N)
	{
		printf("%lld = ",N);
		if(N<0LL){printf("-1 x ");N*=-1LL;}
		assert(N!=-1LL);
		vector<int>ans;
		for(LL i=0LL;P[i]*P[i]<=N;i++)
		{
			while(N%P[i]==0LL)
			{
				ans.push_back(P[i]);
				N/=P[i];
			}
		}
		if(N>1LL)ans.push_back(N);
		printf("%lld",ans[0]);
		for(LL i=1LL;i<ans.size();i++)printf(" x %lld",ans[i]);puts("");
	}
	return 0;
}
