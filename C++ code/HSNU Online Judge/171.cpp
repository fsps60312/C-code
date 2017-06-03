#include<cstdio>
typedef long long LL;
const LL SPAN=100000000LL;
struct Big
{
	LL s[4];
	void Initialize()
	{
		for(int i=0;i<4;i++)s[i]=0;
		char str[32];scanf("%s",str);
		int n=-1;while(str[++n]);n--;
		for(int i=0;i<=n;i++)(s[(n-i)/8]*=10)+=(str[i]-'0');
	}
	LL DivSq(const LL a)
	{
		LL backup[4];
		for(int i=0;i<4;i++)backup[i]=s[i];
		for(int cnt=0;cnt<2;cnt++)
		{
			LL now=0LL;
			for(int i=3;i>=0;i--)
			{
				now=now*SPAN+s[i];
				s[i]=now/a;
				now%=a;
			}
		}
		LL ans=0LL;
		for(int i=3;i>=0;i--)ans=ans*SPAN+s[i],s[i]=backup[i];
		return ans;
	}
}BIG;
int main()
{
	BIG.Initialize();
	LL l=1LL,r=10000000000LL;
	while(l<r)
	{
		const LL mid=(l+r+1LL)>>1;
		if(BIG.DivSq(mid)<mid)r=mid-1LL;
		else l=mid;
	}
	printf("%lld\n",r);
	return 0;
}
