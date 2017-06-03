#include<cstdio>
#include<cmath>
int T,A,K;
double B;
int Pow(int a,int b)
{
	a%=1000;
	int ans=1;
	while(b)
	{
		if(b&1)ans*=a,ans%=1000;
		a*=a,a%=1000;
		b>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&A,&K);
		B=K*log10(A);
		B-=floor(B);
		B+=2.0;
		printf("%d...%03d\n",(int)pow(10.0,B),Pow(A,K));
	}
	return 0;
}
