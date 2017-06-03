#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int T;
double A[3],L;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf%lf%lf%lf",&A[0],&A[1],&A[2],&L);
		sort(A,A+3);
		if(A[1]-A[0]>=L)A[0]+=L;
		else if(A[2]-A[1]+A[2]-A[0]>=L)A[0]=A[1]=0.5*(A[0]+A[1]+L);
		else A[0]=A[1]=A[2]=(A[0]+A[1]+A[2]+L)/3.0;
		double s=(A[0]+A[1]+A[2])/2.0;
//		printf("%.2f %.2f %.2f\n",A[0],A[1],A[2]);
		printf("%.10f\n",sqrt(s*(s-A[0])*(s-A[1])*(s-A[2])));
	}
	return 0;
}
