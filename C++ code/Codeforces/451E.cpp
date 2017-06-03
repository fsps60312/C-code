#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
void Exgcd(const LL &a,const LL &b,LL &x,LL &y)
{
	if(b==0LL)assert(a==1LL),x=1LL,y=0LL;
	else
	{
		Exgcd(b,a%b,y,x);//(a-a/b*b)x+by==1
		(y-=a/b*x)%=MOD;
	}
}
LL Inv(const LL &v)
{
	static LL x,y;
	Exgcd(v,MOD,x,y);
	x=(x%MOD+MOD)%MOD;
	assert(v*x%MOD==1LL);
	return x;
}
LL C(const LL &a,const LL &b)
{
	if(b<a-b)return C(a,a-b);
	LL ans=1LL;
	for(LL i=b+1LL;i<=a;i++)(ans*=i%MOD)%=MOD,(ans*=Inv(i-b))%=MOD;
	return ans;
}
int N;
LL S,F[20];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%I64d",&N,&S)==2)
	{
		for(int i=0;i<N;i++)scanf("%I64d",&F[i]);
		LL ans=0LL;
		for(int s=0;s<(1<<N);s++)
		{
			LL sum=S,cnt=0LL;
			for(int i=0;i<N;i++)
			{
				if(s&(1<<i))sum-=F[i]+1LL,cnt++;
			}
			if(sum<0LL)continue;
			const LL ta=C(sum+N-1LL,N-1LL);
			if(cnt&1LL)(ans-=ta)%=MOD;
			else (ans+=ta)%=MOD;
		}
		printf("%I64d\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}
