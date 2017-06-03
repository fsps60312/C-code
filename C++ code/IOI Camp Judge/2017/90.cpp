#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const double EPS=1e-9;
double F(const int n,const double x);
double Integrate(const int n,const double l,const double r)
{
	const double mid=(l+r)/2,mv=F(n,mid);
	const double symp=(F(n,l)+4*F(n,mid)+F(n,r))/6;
	if(fabs(symp-mv)<EPS)return symp;
	else return Integrate(n,l,mid)+Integrate(n,mid,r);
}
double F(const int n,const double x)
{
	if(n==1)return 0.0<=x&&x<=1.0?1.0:0.0;
	int nl,nr
	if(n&1)
}
int N,A,B;
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		
	}
	return 0;
}
