#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
char S[1000001];
pair<LL,int>DPabToBa[1000001];
pair<LL,int>GetAbToBa(const int a)
{
	auto &dp=DPabToBa[a];
	if(dp.first!=-1)return dp;
	//bbbaaaaaab
	//bbbaaaaabba
	const auto &b1=GetAbToBa(a-1);
	//bbbaaaaaba
	const auto &b2=GetAbToBa(b1.second);
	return dp=make_pair((1+b1.first+b2.first)%MOD,b2.second+1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=1000000;i++)DPabToBa[i].first=-1;
	DPabToBa[0]=make_pair(0LL,0);
	while(scanf("%s",S)==1)
	{
		LL ans=0;
		int leftA=0;
		for(int i=0;S[i];i++)
		{
			if(S[i]=='a')leftA++;
			else
			{
				assert(S[i]=='b');
				const auto p=GetAbToBa(leftA);
				(ans+=p.first)%=MOD;
				leftA=p.second;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
