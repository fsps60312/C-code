#include<cstdio>
#include<cmath>
int T;
double A,B,S;
double Get(const double l,const double r)
{
	//f(S/x)=S*f(1/x)=S*ln(x)
	return S*(log(r)-log(l));
}
double Solve()
{
	if(S<=0.0)return 100.0;
	if(S>=A*B)return 0.0;
	double ans=1.0-(B*S/B+Get(S/B,A))/(A*B);
//	printf("%f %f %f\n",A,B,S);
//	printf("(%f,%f)\n",S/B,A);
	return ans*100.0;
}
int main()
{
//	printf("%.3f\n",log(10.0));
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf%lf%lf",&A,&B,&S);
		//Sum(A*B/S,A)
		//F(x)=S/x
		//Sum(F(x),x=B/S~A)
		printf("%.6f%%\n",Solve());
	}
	return 0;
}
