#include<cstdio>
#include<cstdlib>
#include<cmath>
typedef long long LL;
const LL MOD=100000007;
LL S;
/*LL output(LL a)
{
	a%=MOD;
	return a*a*2%MOD;
}
bool isans(LL a)
{
	//exist integer solution:(-7a+sqrt(49 a^2 + 24S))/12
	LL b=49*a*a+24*S;
	LL c=sqrt(b);
	if(c*c!=b) return false;
	return (c-7*a)%12==0;
}*/
LL cal(LL r)
{
	//a==(S-6r^2)/7r
	LL a=S-6*r*r,b=7*r;
	return a%b==0?a/b:-1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//long long kase=0;
	while(scanf("%lld",&S)==1&&S)
	{
		//r thick, a inside
		//missing: a*a*2
		//S==r*r*6+a*r*7
		//==r*(6r+7a)
		//6 r^2 + 7a r - S == 0
		//a==(S-6r^2)/7r
		//r==(-7a+sqrt(49 a^2 + 24S))/12
		//(12+7a)^2==49a^2+24S==(144+168a+49a^2)
		//if(kase) printf("\n");
		LL b=0;
		for(LL r=1;6*r*r<S;r++)
		{
			LL i=cal(r);
			if(i!=-1)
			{
				i%=MOD;
				printf("Possible Missing Soldiers = %lld\n",i*i*2%MOD);
				b++;
			}
		}
		if(b==0) printf("No Solution Possible\n");
		printf("\n");
		//kase++;
	}
	return 0;
}
