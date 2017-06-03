#include<cstdio>
const double INF=1e9;
int T,A,K;
double B;
double Dpow(double a,int b)
{
	double ans=1.0;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
			if(ans>INF)ans/=INF;
		}
		a*=a;
		if(a>INF)a/=INF;
		b>>=1;
	}
	return ans*1000.0;
}
int Ipow(int a,int b)
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
		B=A;
		static char tmp[1000000];
		sprintf(tmp,"%.9lf",Dpow(B,K));
		tmp[3]='\0';
		printf("%s...%03d\n",tmp,Ipow(A,K));
	}
	return 0;
}
