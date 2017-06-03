#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
LL Pow(LL a,LL p)
{
	LL ans=1;
	for(;p;p>>=1,(a*=a)%=MOD)if(p&1)(ans*=a)%=MOD;
	return ans;
}
LL P,K;
vector<int>F[1000001];
int main()
{
	int ccc=0;
	for(int i=1;i<=1000000;i++)
	{
		for(int j=1;i*j<=1000000;j++)F[i*j].push_back(i),++ccc;
	}
	printf("ccc=%d\n",ccc);
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld",&P,&K)==2)
	{
		static bool vis[1000000];
		for(int i=0;i<P;i++)vis[i]=false;
		static LL cnts[1000001];
		for(int i=1;i<=P;i++)cnts[i]=0;
		for(int i=0;i<P;i++)if(!vis[i])
		{
			int cnt=0;
			for(LL cur=i;!vis[cur];cur=cur*K%P)/*printf("cur=%lld\n",cur),*/vis[cur]=true,++cnt;
			++cnts[cnt];
//			printf("cnt[%d]=%d\n",i,cnt);
		}
		LL ans=1;
		for(int i=1;i<=P;i++)if(cnts[i])
		{
			LL ta=0;
			for(const int v:F[i])if(cnts[v])
			{
				(ta+=v*cnts[v])%=MOD;
			}
			(ans*=Pow(ta,cnts[i]))%=MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
