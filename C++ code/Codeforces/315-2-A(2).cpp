#include<cstdio>
const double EPS=1e-9;
double T,S,Q;
int main()
{
	while(scanf("%lf%lf%lf",&T,&S,&Q)==3)
	{
		int ans=1;
		double now=0.0;
		for(;;)
		{
			//now+t*Q==S+t*(Q-1)
			//t==S-now
			const double t=S-now;
			now+=t*Q,S+=t*(Q-1.0);
			if(S+EPS>T)break;
			ans++,now=0.0;
		}
		printf("%d\n",ans);
//		break;
	}
	return 0;
}
