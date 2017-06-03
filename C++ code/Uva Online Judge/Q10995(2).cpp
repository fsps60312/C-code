#include<cstdio>
struct Time
{
	double h,m,s;
	bool scan()
	{
		scanf("%lf",&h);
		if(h<0.0)return false;
		scanf(":%lf:%lf",&m,&s);
		return true;
	}
	double Value(){return h*3600.0+m*60.0+s;}
//	double operator-(const Time &t)const{return Value()-t.Value();}
}T[5];
int main()
{
//	freopen("in.txt","r",stdin);
	while(T[0].scan())
	{
		for(int i=1;i<5;i++)T[i].scan();
		//0==xc+vc*(t1-s)
		//0==xm+vm*(t2-s)
		//0==xd+vd*(t3-s)
		//xd+vd*(t4-s)==xc+vc*(t4-s)
		//xd+vd*(t5-s)==xm+vm*(t5-s)
		//xc+vc*(t6-s)==xm+vm*(t6-s)
		//vc*(t6-t1)==vm*(t6-t2)
		//vc*(t1-t4)==vd*(t3-t4)
		//vd*(t5-t3)==vm*(t5-t2)
		//
		//vm*(t6-t2)==vc*(t6-t1)
		//vc*(t1-t4)==vd*(t3-t4)
		//vd*(t5-t3)==vm*(t5-t2)
		//(t6-t2)(t1-t4)(t5-t3)==(t6-t1)(t3-t4)(t5-t2)
		//t6((t1-t4)(t5-t3)-(t3-t4)(t5-t2))==t2(t1-t4)(t5-t3)-t1(t3-t4)(t5-t2)
		double t1=T[0].Value(),t2=T[1].Value(),t3=T[2].Value(),t4=T[3].Value(),t5=T[4].Value();
		double t6=(t2*(t1-t4)*(t5-t3)-t1*(t3-t4)*(t5-t2))/((t1-t4)*(t5-t3)-(t3-t4)*(t5-t2));
		int ans=t6+0.5;
		printf("%02d:%02d:%02d\n",ans/3600,ans%3600/60,ans%60);
	}
	return 0;
}
