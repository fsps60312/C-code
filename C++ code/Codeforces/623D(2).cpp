#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
int N;
double S[100];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lf",&S[i]),S[i]*=0.01;
		//1.0/s1/t1=1.0/s2/t2=1.0/s3/t3=...
		static double v[100];
		for(int i=0;i<N;i++)v[i]=1.0/S[i];
		//v1/t1=v2/t2=v3/t3=...
		for(int i=0;i<N;i++)v[i]=1.0/v[i];
		//v1*t1=v2*t2=v3*t3=...
		//t1+t2+t3+...=1.0
		//t1:t2:t3:...=1.0/v1:1.0/v2:1.0/v3:...
		double sum=0.0;
		for(int i=0;i<N;i++)sum+=1.0/v[i];
		static double t[100];
		for(int i=0;i<N;i++)t[i]=1.0/v[i]/sum;
		for(int i=1;i<N;i++)assert(fabs(v[i-1]*t[i-1]-v[i]*t[i])<1e8);
		printf("%.9f\n",1.0/S[0]/t[0]);
	}
	return 0;
}
