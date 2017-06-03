#include<cstdio>
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
typedef long long LL;
LL T,N,A,B,C,CNT,SUM;
LL getSUM(LL a,LL b,LL c)
{
	LL ans=1LL;
	LL NOW=a+1LL;
	for(LL i=1LL;i<=b;i++,NOW++)
	{
		ans*=NOW;
		ans/=i;
	}
	for(LL i=1LL;i<=c;i++,NOW++)
	{
		ans*=NOW;
		ans/=i;
	}
//	LL i=1LL;
//	if(a)ans/=i++;
//	if(b)ans/=i++;
//	if(c)ans/=i++;
//	printf("%lld %lld %lld => %lld\n",a,b,c,ans);
	return ans;
}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&A,&B,&C);
		N=A+B+C;
		SUM=getSUM(A,B,C);
//		CNT=1LL;
		for(LL i=1LL,u;i<N;i++)
		{
			u=N/gcd(N,i);
			if(A%u||B%u||C%u)continue;
			SUM+=getSUM(A/u,B/u,C/u);
		}
		CNT=N;
		if(N&1LL)
		{
			LL sum;
			if((A&B&C&1LL))sum=0LL;
			else sum=getSUM(A>>1,B>>1,C>>1);
			SUM+=N*sum;
		}
		else
		{
			LL sum;
			if((A|B|C)&1LL)sum=0LL;
			else sum=getSUM(A>>1,B>>1,C>>1);
			SUM+=(N>>1)*sum;
			if((A|B|C)&1LL)sum=getSUM(A>>1,B>>1,C>>1)<<1;
			else sum=getSUM(A>>1,B>>1,C>>1);
			SUM+=(N>>1)*sum;
		}
		CNT+=N;
//		printf("%lld %lld\n",SUM,CNT);
		if(SUM%CNT)termin();
		printf("%lld\n",SUM/CNT);
	}
	return 0;
}
