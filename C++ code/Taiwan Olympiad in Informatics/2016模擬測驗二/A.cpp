#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const double PI=acos(-1.0),EPS=1e-7;
double Angle(const double x,const double y)
{
	if(y>=0.0&&x>0.0)return atan2(y,x);
	if(y>0.0&&x<=0.0)return 0.5*PI+atan2(-x,y);
	else if(y<=0.0&&x<0.0)return 1.0*PI+atan2(-y,-x);
	else if(y<0.0&&x>=0.0)return 1.5*PI+atan2(x,-y);
	else assert(0);
	return -1.0;
}
double OX,OY,X[500],Y[500];
int N;
double AngleChanged(const int i1,const int i2)
{
	double a=Angle(X[i1]-OX,Y[i1]-OY),b=Angle(X[i2]-OX,Y[i2]-OY);
	double pos=b-a,neg=a-b;
	if(pos<0.0)pos+=2.0*PI;
	if(neg<0.0)neg+=2.0*PI;
//	printf("pos=%.3f,neg=%.3f\n",pos/PI*180,neg/PI*180);
	assert(pos>=0.0&&neg>=0.0&&fabs(pos+neg-2.0*PI)<EPS);
	if(pos<neg)return pos;
	else return -neg;
}
int main()
{
	assert(fabs(atan2(sqrt(3.0),1.0)-PI/3.0)<EPS);
//	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf",&OX,&OY)==2)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lf%lf",&X[i],&Y[i]);
		double angle=0.0;
		for(int i=1;i<N;i++)
		{
			angle+=AngleChanged(i-1,i);
		}
		angle+=AngleChanged(N-1,0);
		if(fabs(angle-0.0)<EPS)puts("NO");
		else if(fabs(angle-2.0*PI)<EPS)puts("YES");
		else assert(0);
	}
	return 0;
}
