#include<cstdio>
#include<cstdlib>
int B,P,M;
int pow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
			ans%=M;
		}
		b>>=1;
		a*=a;
		a%=M;
	}
	return ans;
}
int main()
{
	while(scanf("%d%d%d",&B,&P,&M)==3)
	{
		B%=M;
		printf("%d\n",pow(B,P));
	}
}
