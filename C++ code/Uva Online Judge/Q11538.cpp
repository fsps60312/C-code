#include<cstdio>
#include<cstdlib>
long long a,b,ans;
int main()
{
	while(scanf("%lld%lld",&a,&b)==2)
	{
		if(a==b&&b==0) break;
		ans=b*a*(a-1)+a*b*(b-1);//rows & columns
		if(a<b)
		{
			long long c=a;
			a=b;
			b=c;
		}
		//a*(a-1)+...+4*3+3*2+2*1
		//(a-1)^2+...+3^2+2^2+1^1+(a-1)+...+3+2+1
		//x*(x+1)*(2x+1)/6+x*(x+1)/2
		//1:2
		//2:8
		ans+=((b-1)*b*(2*b-1)/3+(b-1)*b)*2;
		ans+=(b-1)*b*(a-b-1)*2;
		printf("%lld\n",ans);
	}
	return 0;
}
