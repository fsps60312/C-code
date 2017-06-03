#include<cstdio>
#include<map>
#include<cassert>
using namespace std;
typedef long long LL;
const int MOD=10007;
int N,K;
struct Pair
{
	LL v;
	int cnt;
	Pair(){}
	Pair(const LL _v,const int _c):v(_v),cnt(_c){}
	bool operator<(const Pair &p)const{return cnt!=p.cnt?cnt<p.cnt:v<p.v;}
};
map<Pair,LL>DP;
LL GetBinary()
{
	LL ans=0LL;
	char c=getchar();
	while(c!='0'&&c!='1')c=getchar();
	for(int i=0;i<N;i++)assert(c=='0'||c=='1'),(ans<<=1)|=(c-'0'),c=getchar();
	return ans;
}
LL BitCnt(LL a)
{
	a=((a&0xaaaaaaaaaaaaaaaa)>>1)+(a&0x5555555555555555);
	a=((a&0xcccccccccccccccc)>>2)+(a&0x3333333333333333);
	a=((a&0xf0f0f0f0f0f0f0f0)>>4)+(a&0x0f0f0f0f0f0f0f0f);
	a=((a&0xff00ff00ff00ff00)>>8)+(a&0x00ff00ff00ff00ff);
	a=((a&0xffff0000ffff0000)>>16)+(a&0x0000ffff0000ffff);
	a=((a&0xffffffff00000000)>>32)+(a&0x00000000ffffffff);
	return a;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	while(scanf("%d%d",&N,&K)==2&&(N||K))
	{
		DP.clear();
		DP[Pair(0LL,0)]=1;
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)for(int k=j+1;k<N;k++)
		{
			static LL v;v=(1LL<<i)+(1LL<<j)+(1LL<<k);
			map<Pair,LL>tmp;
			for(const auto &it:DP)(tmp[Pair(it.first.v^v,it.first.cnt+1)]+=it.second);//%=MOD;
			for(const auto &it:tmp)(DP[it.first]+=it.second);//%=MOD;
		}
//		for(const auto &it:DP)printf("(%lld,%d):%d\n",it.first.v,it.first.cnt,it.second);
		LL tmp[N+1][K+1];
		for(int i=0;i<=N;i++)for(int j=0;j<=K;j++)tmp[i][j]=0;
		for(const auto &it:DP)if(it.first.cnt<=K)tmp[BitCnt(it.first.v)][it.first.cnt]+=it.second;
		for(int i=0;i<=K;i++)
		{
			printf("cnt=%d\n",i);
			for(int j=0;j<=N;j++)printf(" %lld",tmp[j][i]);puts("");
		}
		continue;
		LL v=GetBinary()^GetBinary();
//		printf("v=%lld\n",v);
		static int kase=1;
		printf("Case #%d: %d\n",kase++,DP[Pair(v,K)]);
	}
	return 0;
}
