#include<cstdio>
#include<cstdlib>
long long m,n,ans1,ans2,digit[12];
long long zero(long long a)
{
	if(a==0) return 1;
	long long ans=0;
	while(a)
	{
		if(a%10==0) ans++;
		a/=10;
	}
	return ans;
}
long long zeros(long long a)
{
	long long ans=a/10+1;
	for(int i=2;a/digit[i];i++)//digit[2]==100
	{
		ans+=a/digit[i]*digit[i-1];
		if(a/digit[i-1]%10==0)
		{
			ans+=a%digit[i]+1;
			//ans-=digit[i];
		}
		else
		{
			ans+=digit[i-1];
		}
		ans-=digit[i-1];
	}
	return ans;
}//200:32==20+11
int main()
{
	//printf("%lld\n",zeros(200));
	//freopen("in.txt","r",stdin);
	digit[0]=1;
	for(int i=1;i<12;i++) digit[i]=digit[i-1]*10;
	while(scanf("%lld%lld",&m,&n)==2&&m>=0)
	{
		//printf(" %lld %lld\n",m,n);
		ans1=zeros(m);
		ans2=zeros(n);
		//printf("%lld %lld\n",ans1,ans2);
		printf("%lld\n",ans2-ans1+zero(m));
	}
	return 0;
}
