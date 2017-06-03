#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
void Exgcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0){assert(a==1),x=1,y=0;}
	else
	{
		Exgcd(b,a%b,y,x);//by+(a-a/b*b)x=1,ax+b(y-a/b*x)=1
		(y-=a/b*x)%=MOD;
	}
}
LL Inv(const LL a)
{
	LL x,y;
	Exgcd(a,MOD,x,y);
	return x>=0?x:x+MOD;
}
LL LEVEL[100001],RELEV[100001];
void Initialize()
{
	LEVEL[0]=1;
	for(int i=1;i<=100000;i++)LEVEL[i]=LEVEL[i-1]*i%MOD;
	for(int i=0;i<=100000;i++)RELEV[i]=Inv(LEVEL[i]);
}
LL C(const int a,const int b)
{
	if(b>a)return 0;
	return LEVEL[a]*RELEV[b]%MOD*RELEV[a-b]%MOD;
}
int N,K;
int CNT[1000001];
LL ANS[1000001];
int main()
{
	freopen("data.txt","r",stdin);
	Initialize();
	int testcount;scanf("%d",&testcount);
	assert(1<=testcount&&testcount<=20);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		assert(2<=N&&N<=100000);
		assert(2<=K&&K<=N);
		for(int i=0;i<=1000000;i++)CNT[i]=0;
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			assert(1<=v&&v<=1000000);
			++CNT[v];
		}
		LL ans=0;
		for(int i=1000000;i>=1;i--)
		{
			int cnt=0;
			for(int j=1;i*j<=1000000;j++)cnt+=CNT[i*j];
			ANS[i]=C(cnt,K);
			for(int j=2;i*j<=1000000;j++)(ANS[i]-=ANS[i*j])%=MOD;
			(ans+=ANS[i]*i)%=MOD;
		}
		printf("%lld\n",ans>=0?ans:ans+MOD);
	}
	return 0;
}
