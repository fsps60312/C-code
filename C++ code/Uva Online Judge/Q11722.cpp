#include<cstdio>
#include<cstdlib>
double t1,t2,s1,s2,w;
int T;
double sqr(double a)
{
	return a*a;
}
double keystone(double a,double b)
{
	if(a<=b) return a*a/2;
	else return (a+(a-b))*b/2;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%lf%lf%lf%lf%lf",&t1,&t2,&s1,&s2,&w);
		double h=s2-s1;
		double ans=w*2*h;
		if(t2<s2+w) ans-=keystone(s2+w-t2,h);
		if(t2<s2-w) ans+=keystone(s2-w-t2,h);
		if(t1>s1-w) ans-=keystone(t1-(s1-w),h);
		if(t1>s1+w) ans+=keystone(t1-(s1+w),h);
		printf("Case #%d: %.8lf\n",kase,ans/h/(t2-t1));
	}
	return 0;
}
