#include<cstdio>
#include<cmath>
const double PI=acos(-1.0),EPS=1e-9;
double K,Hb,Db,Hn,Dn,H,Rb,Rn,V,Hm;
double abs(double a){return a>=0.0?a:-a;}
double sq(double a){return a*a;}
double FVM(double x){return PI*sq(Rb+x/Hm*(Rn-Rb));}
double getVM(double l,double r){return (r-l)/6.0*(FVM(l)+FVM(r)+4.0*FVM(0.5*(l+r)));}
double inteVM(double l,double r)
{
	double s0=getVM(l,r);
	double mid=0.5*(l+r),s1=getVM(l,mid)+getVM(mid,r);
//	printf("(%.3f,%.3f):%.3f:%.3f\n",l,r,s0,s1);
	if(abs(s1-s0)<EPS)return s1;
	return inteVM(l,mid)+inteVM(mid,r);
}
double initV(double k)
{
    if(k<=Hb)return PI*Rb*Rb*k;
	double ans=PI*Rb*Rb*Hb;
    k-=Hb;
//    printf("a%.3f,k=%.3f\n",ans,k);
    if(Hm==0.0){}
    else if(k<=Hm)return ans+inteVM(0.0,k);
    else ans+=inteVM(0.0,Hm);
//    printf("b%.3f,k=%.3f\n",ans,k);
    k-=Hm;
    return ans+PI*Rn*Rn*k;
}
double Bow(double r,double h)
{
	if(h<=0)return 0.0;
	double angle=acos((r-h)/r);
	return r*r*angle-(r-h)*sqrt(r*r-(r-h)*(r-h));
}
double FM(double x,double h){double dr=h/Hm*(Rb-Rn);return Bow(Rb-dr,h-dr);}
double getM(double l,double r,double h){return (r-l)/6.0*(FM(l,h)+FM(r,h)+4.0*FM(0.5*(l+r),h));}
double inteM(double l,double r,double h)
{
	double s0=getM(l,r,h);
	double mid=0.5*(l+r),s1=getM(l,mid,h)+getM(mid,r,h);
	if(abs(s1-s0)<EPS)return s1;
	return inteM(l,mid,h)+inteM(mid,r,h);
}
double inteV(double h)
{
	if(h>Rb)return 2.0*inteV(Rb)-inteV(Db-h);
	double ans=Bow(Rb,h)*Hb+Bow(Rn,h-(Rb-Rn))*Hn;
	if(Hm==0.0){}
	else if(h>=Rb-Rn)ans+=inteM(0,Hm,h);
	else ans+=inteM(0,Hm*h/(Rb-Rn),h);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
    while(scanf("%lf%lf%lf%lf%lf%lf",&K,&Hb,&Db,&Hn,&Dn,&H)==6&&(K!=0.0||Hb!=0.0||Db!=0.0||Hn!=0.0||Dn!=0.0||H!=0.0))
    {
        Rb=0.5*Db,Rn=0.5*Dn,Hm=H-Hb-Hn;
        V=initV(K);
        double l=0.0,r=Db,mid;
        while(r-l>EPS)
        {
        	mid=0.5*(l+r);
//        	printf("%.3lf %.3lf:%.3lf\n",mid,inteV(mid),V);
        	if(inteV(mid)>V)r=mid;
        	else l=mid;
		}
		printf("V%.2lf==",initV(H));
		printf("H%.2lf\n",inteV(Db));
		printf("%.2lf\n",l);
    }
    return 0;
}
