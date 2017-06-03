#include<cstdio>
#include<cstdlib>
#define LL long long
LL T,n,S[100001],st1[100001],st2[100001],Max;
LL lowbit(LL a){return a&(-a);}
void add1(LL a,LL b)
{
	while(a<Max)
	{
		st1[a]+=b;
		a+=lowbit(a);
	}
}
LL sum1(LL a)
{
	LL ans=0;
	while(a)
	{
		ans+=st1[a];
		a-=lowbit(a);
	}
	return ans;
}
void add2(LL a,LL b)
{
	while(a<Max)
	{
		st2[a]+=b;
		a+=lowbit(a);
	}
}
LL sum2(LL a)
{
	LL ans=0;
	while(a)
	{
		ans+=st2[a];
		a-=lowbit(a);
	}
	return ans;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		n++;
		Max=0;
		for(LL i=1;i<n;i++)
		{
			scanf("%lld",&S[i]);
			if(S[i]>Max) Max=S[i];
		}
		Max++;
		for(LL i=1;i<Max;i++) st1[i]=st2[i]=0;
		LL n1[n],n2[n];
		for(LL i=1;i<n;i++)
		{
			n1[i]=sum1(S[i]),n2[n-i]=sum2(S[n-i]);
			add1(S[i],1),add2(S[n-i],1);
		}
		//4 1 3 4 2
		//for(int i=1;i<n;i++) printf(" %d %d,",n1[i],n2[i]);
		LL ans=0;
		for(LL i=1;i<n;i++) ans+=n1[i]*(n-i-1-n2[i])+(i-n1[i]-1)*n2[i];
		printf("%lld\n",ans);
	}
	return 0;
}
