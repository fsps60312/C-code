#include<cstdio>
#include<cmath>
#define sq(x) ((x)*(x))
int T;
double D,V,U,L,R;
double solve()
{
	if(U<V)return -1.0;
	L=D/U;
	R=D/sqrt(sq(U)-sq(V));
	return R-L;
}
int main()
{
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%lf%lf%lf",&D,&V,&U);
		printf("Case %d: ",kase++);
		double ans=solve();
		if(ans<0.0)printf("can't determine\n");
		else printf("%.3f\n",ans);
	}
}
