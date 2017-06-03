#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
typedef __int128 Big;
Big Gcd(Big a,Big b)
{
	if(b==Big(0))return a;
	return Gcd(b,a%b);
}
struct Fraction
{
	Big UPON,DOWN;
	Fraction(){}
	Fraction(const Big _UPON,const Big _DOWN):UPON(_UPON),DOWN(_DOWN)
	{
		Big g=Gcd(UPON,DOWN);
		UPON=UPON/g,DOWN=DOWN/g;
	}
};
Fraction operator*(const Fraction &a,const Fraction &b){return Fraction(a.UPON*b.UPON,a.DOWN*b.DOWN);}
Fraction operator+(const Fraction &a,const Fraction &b)
{
	Big c=a.UPON*b.DOWN,d=b.UPON*a.DOWN;
	return Fraction(c+d,a.DOWN*b.DOWN);
}
int N,S[5];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		int SUM=0;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),SUM+=S[i];
		Fraction ans=Fraction(0,1);
		for(int color=0;color<N;color++)
		{
			static Fraction dp[251][51];
			for(int i=0;i<=SUM;i++)for(int j=0;j<=S[color];j++)dp[i][j]=Fraction(0,1);
			dp[SUM][S[color]]=Fraction(1,1);
			for(int i=SUM;i>=1;i--)
			{
				for(int remain=1;remain<=S[color];remain++)
				{
					const Fraction &d=dp[i][remain];
					if(i==remain)ans=ans+Fraction(SUM-remain,1)*d;
					else
					{
						dp[i-1][remain]=dp[i-1][remain]+d*Fraction(i-remain,i);
						dp[i-1][remain-1]=dp[i-1][remain-1]+d*Fraction(remain,i);
					}
				}
			}
		}
		printf("%lld %lld\n",(long long)ans.DOWN,(long long)ans.UPON);
	}
	return 0;
}
