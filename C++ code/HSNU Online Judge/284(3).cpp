#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int N;
vector<LL>DP;
LL GetDP(const int i)
{
	if(i<(int)DP.size())return DP[i];
	DP.push_back(((i-1)*GetDP(i-2)+GetDP(i-1))%MOD);
	return DP[i];
}
int main()
{
	if(true)
	{
		int *t=new int[3]{1,1,2};
		for(int i=0;i<3;i++)DP.push_back(t[i]);
		delete[]t;
	}
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		LL a=0LL,b=0LL;
		for(int i=0,v;i<N;i++)scanf("%d",&v),(v==1?a:b)++;
		LL ans=GetDP(a);
		for(LL i=a+1LL;i<=a+b;i++)(ans*=i)%=MOD;
		printf("%lld\n",ans);
		break;
	}
	return 0;
}
