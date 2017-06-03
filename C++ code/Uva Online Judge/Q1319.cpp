#include<cstdio>
#include<cmath>
int M;
double S,G,P,A,B;
double solve()
{
	double a1=sqrt(A),a0=1.0/a1;
	G=B*a1,S=0.0;
	double ans=0.0;
	for(int i=1;;i++)
	{
		if(i==M)return ans+pow(G-S,P);
		if(S+a1-a0<=G)ans+=pow(a1,P),S+=a1;
		else ans+=pow(a0,P),S-=a0;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lf%lf%lf",&M,&P,&A,&B)==4)
	{
		printf("%.0f\n",solve());
	}
	return 0;
}
