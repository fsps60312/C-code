#include<cstdio>
struct Time
{
	int h,m,s;
	bool scan()
	{
		scanf("%d",&h);
		if(h==-1)return false;
		scanf(":%d:%d",&m,&s);
		return true;
	}
	int Value(){return h*3600+m*60+s;}
	int operator-(const Time &t)const{return Value()-t.Value();}
}T[5];
int main()
{
	freopen("in.txt","r",stdin);
	while(T[0].scan())
	{
		for(int i=1;i<5;i++)T[i].scan();
		//xa+va*t1==xc+vc*t1
		//xa+va*t2==xm+vm*t2
		//xa+va*t3==xd+vd*t3
		//xd+vd*t4==xc+vc*t4
		//xd+vd*t5==xm+vm*t5
		//xc+vc*t6==xm+vm*t6
		//xa-xc==t1(vc-va)
		//xa-xm==t2(vm-va)
		//xa-xd==t3(vd-va)
		//xd-xc==t4(vc-vd)
		//xd-xm==t5(vm-vd)
		//xc-xm==t6(vm-vc)
		//
		//xc-xa==t1(va-vc)
		//xa-xd==t3(vd-va)
		//xd-xc==t4(vc-vd)
		//t1(va-vc)+t3(vd-va)+t4(vc-vd)==0
		//
		//xa-xd==t3(vd-va)
		//xd-xc==t4(vc-vd)
		//xc-xm==t6(vm-vc)
		//t2(vm-va)-t3(vd-va)-t4(vc-vd)==t6(vm-vc)
	}
	return 0;
}
