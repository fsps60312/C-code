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
int NXT[13970034],VAL[13970034],NSZ;
int F[1000001];
LL Solve()
{
	if(K==0)
	{
		return Pow(P,P-1);
	}
	static bool vis[1000000];
	for(int i=0;i<P;i++)vis[i]=false;
	static LL cnts[1000001];
	for(int i=1;i<=P;i++)cnts[i]=0;
	for(int i=0;i<P;i++)if(!vis[i])
	{
		int cnt=0;
		for(LL cur=i;!vis[cur];cur=cur*K%P)/*printf("cur=%lld\n",cur),*/vis[cur]=true,++cnt;
		++cnts[cnt];
//		printf("cnt[%d]=%d\n",i,cnt);
	}
	LL ans=1;
	for(int i=1;i<=P;i++)if(cnts[i])
	{
		LL ta=0;
		for(int cur=F[i];cur!=-1;cur=NXT[cur])if(cnts[VAL[cur]])
		{
			(ta+=VAL[cur]*cnts[VAL[cur]])%=MOD;
		}
		(ans*=Pow(ta,cnts[i]))%=MOD;
	}
	return ans;
}
int main()
{
	for(int i=1;i<=1000000;i++)F[i]=-1;
	NSZ=0;
	for(int i=1;i<=1000000;i++)
	{
		for(int j=1;i*j<=1000000;j++)
		{
			NXT[NSZ]=F[i*j];
			VAL[NSZ]=i;
			F[i*j]=NSZ++;
		}
	}
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld",&P,&K)==2)
	{
		printf("%lld\n",Solve());
	}
	return 0;
}
