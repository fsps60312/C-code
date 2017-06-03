#include<cstdio>
#include<cmath>
double L,F;
//f(v)=v/(L+v^2/(2F))=2Fv/(2FL+v^2)
//f'(v)=(2Fv(2v)-2F(2FL+v^2))/(2FL+v^2)^2=0
//2Fv(2v)-2F(2FL+v^2)=0
//2v^2-2FL-v^2=v^2-2FL=0
//v=sqrt(2FL)
//f(v)=2Fsqrt(2FL)/(2FL+2FL)=sqrt(2FL)/2L
int main()
{
	while(scanf("%lf%lf",&L,&F)==2&&!(L==0.0&&F==0.0))
	{
		F=sqrt(2.0*F*L);
		printf("%.8lf %.8lf\n",F,1800.0*F/L);
	}
}
