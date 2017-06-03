#include<cstdio>
#include<cassert>
using namespace std;
double A,B,P;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lf%lf%lf",&A,&B,&P);
//		0*Q+1*P*Q+2*P*P*Q+...
//		sum(k*P^k*Q)=Q*sum(k*P^k)
//		 s=1*P+2*P*P+3*P*P*P+...
//		Ps=    1*P*P+2*P*P*P+...
//		(1-P)s=P+P*P+P*P*P+...
//		P(1-P)s= P*P+P*P*P+...
//		(1-P)(1-P)s=P
//		s=P/(1-P)/(1-P)
		const double average_waiting_time_2=2.0*A*P/(1.0-P);
//		s=0*P+1*Q*P+2*Q*Q*P
//		sum(k*Q^k*P)=P*sum(k*Q^k)
		const double average_waiting_time_1=B*(1.0-P)/P;
		printf("%.9f\n",average_waiting_time_1+average_waiting_time_2);
	}
	return 0;
}
