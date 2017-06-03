#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
int A,C,M;
LL LEVEL[800001],RELEV[800001],POW2[800001];
void Exgcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0){assert(a==1);x=1,y=0;return;}
	else
	{
		Exgcd(b,a%b,y,x);
		(y-=a/b*x);
	}
}
LL Reverse(const LL a)
{
	LL x,y;
	Exgcd(a,MOD,x,y);
	return (x%MOD+MOD)%MOD;
}
LL Cc(const int a,const int b)
{
	return LEVEL[a]*RELEV[b]%MOD*RELEV[a-b]%MOD;
}
LL Count(const int n,const int c1,const int c2,const int free)
{
	if(c1+c2>n)return 0;
	const int remain_free=free-(n-c1-c2);
	if(remain_free<0)return 0;
	return POW2[n-c1-c2]*Cc(n-1+remain_free,n-1)%MOD*LEVEL[n]%MOD*RELEV[c1]%MOD*RELEV[c2]%MOD*RELEV[n-c1-c2]%MOD;
}
LL Solve(const int n,const int dis,const int c,const int m)
{
	const int free=c-dis;
	const int cnt1=m-c+dis,cnt2=dis;
	LL ans=Count(n,cnt1,cnt2,free);
//			printf("ans=%lld\n",ans);
	(ans+=Count(n-1,cnt1,cnt2,free)*2)%=MOD;
//			printf("ans=%lld\n",ans);
	(ans+=Count(n-2,cnt1,cnt2,free))%=MOD;
//			printf("ans=%lld\n",ans);
	return ans;
}
void GenerateInputFile()
{
	freopen("in.txt","w",stdout);
	for(int a=1;a<=16;a++)
	{
		for(int b=1;b<=16;b++)
		{
			for(int c=1;c<=16;c++)if(a+b+c==15)printf("%d %d %d\n",a,b,c);
		}
	}
	exit(0);
}
int main()
{
//	GenerateInputFile();
	LEVEL[0]=RELEV[0]=POW2[0]=1;
	for(int i=1;i<=800000;i++)LEVEL[i]=LEVEL[i-1]*i%MOD,RELEV[i]=RELEV[i-1]*Reverse(i)%MOD,POW2[i]=POW2[i-1]*2%MOD;
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&A,&C,&M)==3)
	{
		if(C>M)swap(C,M);
		LL ans=0;
		for(int dis=0;dis<=C;dis++)
		{
//			printf("%d %d\n",M-C+dis,dis);
			(ans+=Solve(A+1,dis,C,M))%=MOD;
		}
		printf("%lld\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}
