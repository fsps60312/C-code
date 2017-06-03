#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
LL P,K;
int main()
{
	freopen("in.txt","r",stdin);
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
			printf("cnt[%d]=%lld\n",i,cnts[i]);
			LL ta=0;
			for(int j=1;j<=i;j++)if(cnts[j]&&i%j==0)
			{
				ta+=j*cnts[j];
			}
			for(int k=0;k<cnts[i];k++)ans*=ta;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
