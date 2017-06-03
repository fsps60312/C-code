#include<cstdio>
#define min(x,y) (x<y?x:y)
int N;
double Pl,Pr,DP[1001][1001];
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%lf%lf",&Pl,&Pr);
		//1+(Pl+Pr)*s0=s0
		//s0=1/(1-Pl-Pr)
		//1+min(Pl,Pr)*(s0+se)=se
		//1+min(Pl,Pr)*s0=se*(1-min(Pl,Pr))
		//1+Pl*(s0+si)+Pr*(s0+si)=si
		//si*(1-Pl-Pr)=1+Pl*s0+Pr*s0
		int n=N;
		double s0=1.0/(1.0-Pl-Pr);
		double ans=s0*(N/2);
		n-=N/2;
		if(N%2)
		{
			ans+=(1.0+Pl*s0)/(1.0-Pl);
			ans+=(1.0+Pr*s0)/(1.0-Pr);
			n-=2;
		}
		else
		{
			double mn=min(Pl,Pr);
			ans+=(1.0+mn*s0)/(1.0-mn);
			n--;
		}
		ans+=n*(1.0+(Pl+Pr)*s0)/(1.0-Pl-Pr);
		printf("%.2f\n",ans);
	}
	return 0;
}
