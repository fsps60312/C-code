#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const double EPS=1.0+1e-8;
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
double GetValue(const int id)
{
	switch(id)
	{
		case 1:return pow(X,pow(Y,Z));
		case 2:return pow(X,pow(Z,Y));
		case 3:return pow(pow(X,Y),Z);
		case 4:return pow(pow(X,Z),Y);
		case 5:return pow(Y,pow(X,Z));
		case 6:return pow(Y,pow(Z,X));
		case 7:return pow(pow(Y,X),Z);
		case 8:return pow(pow(Y,Z),X);
		case 9:return pow(Z,pow(X,Y));
		case 10:return pow(Z,pow(Y,X));
		case 11:return pow(pow(Z,X),Y);
		case 12:return pow(pow(Z,Y),X);
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
			if(v>mx*EPS)mx=v,ans=i;
		}
		printf("%s\n",ANS[ans-1]);
	}
	return 0;
}
