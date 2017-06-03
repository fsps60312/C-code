#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
typedef long double LD;
const LD EPS=1.0+1e-8;
double X,Y,Z;
char ANS[12][8]=
{
	"x^y^z",
	"x^z^y",
	"(x^y)^z",
	"(x^z)^y",
	"y^x^z",
	"y^z^x",
	"(y^x)^z",
	"(y^z)^x",
	"z^x^y",
	"z^y^x",
	"(z^x)^y",
	"(z^y)^x"
};
LD GetValue(const int id)
{
	switch(id)
	{
		case 1:return log(X)*pow(Y,Z);
		case 2:return log(X)*pow(Z,Y);
		case 3:return Z*Y*log(X);
		case 4:return Y*Z*log(X);
		case 5:return log(Y)*pow(X,Z);
		case 6:return log(Y)*pow(Z,X);
		case 7:return Z*X*log(Y);
		case 8:return X*Z*log(Y);
		case 9:return log(Z)*pow(X,Y);
		case 10:return log(Z)*pow(Y,X);
		case 11:return Y*X*log(Z);
		case 12:return X*Y*log(Z);
		default:assert(0);return -1.0;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf%lf",&X,&Y,&Z)==3)
	{
		double mx=GetValue(1);
		int ans=1;
		for(int i=2;i<=12;i++)
		{
			const double &v=GetValue(i);
			if(v>mx+EPS)mx=v,ans=i;
		}
		printf("%s\n",ANS[ans-1]);
	}
	return 0;
}
