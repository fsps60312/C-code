#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
int T,N,F;
double PI=acos(-1.0);
vector<double> A;
bool CanFit(double pie)
{
	int f=0;
	for(int i=0;i<N;i++)
	{
		f+=(int)(A[i]/pie);
	}
	return f>F;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&F);
		A.clear();
		double sum=0;
		for(int i=0;i<N;i++)
		{
			double a;scanf("%lf",&a);
			a*=a;
			A.push_back(a);
			sum+=a;
		}
		double l=0.0,r=sum/F;
		while(r-l>=1e-4)
		{
			double mid=0.5*(l+r);
			if(CanFit(mid))l=mid;
			else r=mid;
		}
		printf("%f\n",PI*0.5*(l+r));
	}
	return 0;
}
