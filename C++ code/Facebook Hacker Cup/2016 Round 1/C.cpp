#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
LL A,B,C[100000],SUM;
int N;
double Solve(const LL bl,const LL br)
{
	assert(0LL<=bl&&bl<br&&br<=SUM);
	LL now=0LL;
	double ans=0.0;
	for(int i=0;i<N&&now<br;now+=C[i++])
	{
		if(now+C[i]<=bl)continue;
		const LL l=max(now,bl)-now,r=min(now+C[i],br)-now;
		assert(0LL<=l&&l<=r);
//		printf("(%lld,%lld)\n",l,r);
		ans+=(l+r)*(r-l);
	}
//	printf("(%lld,%lld),ans=%lld\n",bl,br,ans);
	assert(ans>0.0);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(3,"%d%lld%lld",&N,&A,&B);
		SUM=0LL;
		for(int i=0;i<N;i++)scanf(1,"%lld",&C[i]),SUM+=C[i];
		double ans=0.0;
		if(true)
		{
			const LL repeat=B/SUM-(A+SUM-1LL)/SUM;
//			printf("(%lld,%lld)sum=%lld,repeat=%lld\n",A,B,SUM,repeat);
			assert(repeat>=-1LL);
			for(int i=0;i<N;i++)ans+=(double)repeat*(double)(0LL+C[i])*(double)C[i];
		}
		if(A%SUM!=0LL)
		{
			const LL bound=A/SUM*SUM+SUM;
			assert(bound-SUM<A&&A<bound);
			ans+=Solve(SUM-(bound-A),SUM);
		}
		if(B%SUM!=0LL)
		{
			const LL bound=B/SUM*SUM;
			assert(bound<B&&B<bound+SUM);
			ans+=Solve(0,B-bound);
		}
		static int kase=1;
		printf("Case #%d: %.9f\n",kase++,0.5*ans/(double)(B-A));
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
