#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,K,X;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&K,&X);
		static LL dp[30001],tmp[30001];
		for(int i=0;i<=X;i++)dp[i]=0;
		for(;N--;)
		{
			int p,c;
			LL b;
			scanf("%d%lld%d",&p,&b,&c);
			assert(c>=K&&p<=X);
			for(int i=0;i<=X;i++)tmp[i]=0;
			for(int i=X;i>=p*K;i--)getmax(tmp[i],dp[i-p*K]+b*K);
//			for(int i=0;i<=X;i++)printf("a[%d]=%lld\n",i,tmp[i]);
			vector<int>s;
			{
				int v=c-K;
				for(int i=1;i<=v;i*=2)s.push_back(i),v-=i;
				if(v)s.push_back(v);
			}
//			for(int i=0;i<=X;i++)printf("b[%d]=%lld\n",i,tmp[i]);
			for(const int v:s)
			{
				for(int i=X-p*v;i>=0;i--)if(tmp[i])getmax(tmp[i+p*v],tmp[i]+b*v);
			}
//			for(int i=0;i<=X;i++)printf("c[%d]=%lld\n",i,tmp[i]);
			for(int i=0;i<=X;i++)/*printf("tmp[%d]=%lld\n",i,tmp[i]),*/getmax(dp[i],tmp[i]);
		}
		for(int i=1;i<=X;i++)/*printf("dp[%d]=%lld\n",i,dp[i]),*/getmax(dp[i],dp[i-1]);
		printf("%lld\n",dp[X]);
	}
	return 0;
}
