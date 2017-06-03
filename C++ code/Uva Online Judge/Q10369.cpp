#include<cstdio>
const double EPS=1e-5;
int T,S,P;
double X[500],Y[500];
int DJ[500];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
double Dis()
int Group(double d)
{
	for(int i=0;i<P;i++)DJ[i]=i;
	for(int i=0;i<P;i++)
	{
		for(int j=i+1;j<P;j++)
		{
			if(Dis(i,j)<)
		}
	}
}
int main()
{
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&S,&P);
			for(int i=0;i<P;i++)
			{
				scanf("%lf%lf",&X[i],&Y[i]);
			}
			double l=0.0,r=20000.0,mid;
			while(r-l<EPS)
			{
				mid=0.5*(l+r);
				if(Group(mid)<=S)r=mid;
				else l=mid;
			}
			printf("%.2f\n",0.25*(l+r));
		}
	}
	return 0;
}
