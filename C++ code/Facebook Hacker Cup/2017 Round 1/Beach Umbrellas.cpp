#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
void Exgcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0)
	{
		assert(a==1);
		x=1,y=0;
	}
	else
	{
		Exgcd(b,a%b,y,x);
		(y-=a/b*x)%=MOD;
	}
}
LL Inv(const LL a)
{
	LL x,y;
	Exgcd(a,MOD,x,y);
	return x>=0?x:x+MOD;
}
int N,M,R[2000];
LL SUM;
LL LEVEL[2000+1],RELEV[2000+1];
//LL C(const int a,const int b)
//{
//	if(b==N-1)
//	{
//		
//	}
//	assert(0);return -1;
//}
int CNT[2001];
LL Solve1()
{
	LL mul=1;
	for(int i=0;i<N-1;i++)(mul*=M+2000-SUM+N-1-i)%=MOD;
	LL ans=0;
	for(int i=2000;i>=1&&M+i-SUM+N-1>=0;i--)
	{
//		if(CNT[i])printf("1: %d->%d\n",i,CNT[i]);
		(ans+=2*CNT[i]*(mul%MOD)/*C(M+i-SUM+N-1,N-1)*/)%=MOD;
		if(M+i-SUM+N-1==0)break;
		(mul*=Inv(M+i-SUM+N-1))%=MOD;
		(mul*=M+i-SUM)%=MOD;
	}
	return ans;
}
LL Solve2()
{
	LL mul=1;
	for(int i=0;i<N-2;i++)(mul*=M+4000-SUM+N-2-i)%=MOD;
	LL ans=0;
	for(int i=4000;i>=2&&M+i-SUM+N-2>=0;i--)
	{
		for(int j=1;j<i;j++)if(j<=2000&&i-j<=2000)
		{
//			if(CNT[j]*CNT[i-j]-min(CNT[j],CNT[i-j]))printf("2: (%d,%d)->%d\n",i,j,CNT[j]*CNT[i-j]-min(CNT[j],CNT[i-j]));
			(ans+=(CNT[j]*CNT[i-j]-min(CNT[j],CNT[i-j]))*(mul%MOD)/*C(M+i-SUM+N-2,N-2)*/)%=MOD;
		}
		if(M+i-SUM+N-2==0)break;
		(mul*=Inv(M+i-SUM+N-2))%=MOD;
		(mul*=M+i-SUM)%=MOD;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	LEVEL[0]=1;
	for(int i=1;i<=2000;i++)LEVEL[i]=LEVEL[i-1]*i%MOD;
	for(int i=0;i<=2000;i++)RELEV[i]=Inv(LEVEL[i]);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		M--;
		SUM=0;
		for(int i=0;i<N;i++)scanf("%d",&R[i]),SUM+=R[i]*2;
		sort(R,R+N);
		for(int i=1;i<=2000;i++)CNT[i]=(int)((R+N)-lower_bound(R,R+N,i));
		LL ans=0;
		if(SUM<=M)
		{
			LL mul=1;
			for(int i=1;i<=N;i++)(mul*=M-SUM+i)%=MOD;
			(ans+=mul)%=MOD;
		}
		(ans+=Solve1())%=MOD;
//		printf("Solve1=%lld\n",Solve1());
		if(N>=2)(ans+=Solve2())%=MOD;
		static int kase=0;
		if(N==1)ans=M+1;
		printf("Case #%d: %lld\n",++kase,ans);
	}
	return 0;
}
