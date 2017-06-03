#include<cstdio>
#include<set>
#include<cassert>
using namespace std;
struct Dot
{
	Dot *ch[2];
	double x,y;
	Dot(){}
	Dot(const double &_x,const double &_y):ch{NULL,NULL},x(_x),y(_y){}
};
struct CmpDotPointer{bool operator()(const Dot *a,const Dot *b)const{return (*a).x<(*b).x;}};
struct Cake
{
	set<Dot*,CmpDotPointer>dot;
	double area;
	void clear(const double _w,const double _h)
	{
		static Dot s[4];
		s[0]=Dot(0.0,0.0);
		s[1]=Dot(_w,0.0);
		s[2]=Dot(_w,_h);
		s[3]=Dot(0.0,_h);
		for(int i=0;i<4;i++)s[i].ch[1]=&s[(i+1)%4],s[(i+1)%4].ch[0]=&s[i];
		dot.clear();
		for(int i=0;i<4;i++)dot.insert(&s[i]);
		area=_w*_h;
	}
}CAKE;
int N;
double W,H;
int main()
{
	while(scanf("%d%lf%lf",&N,&W,&H)==3)
	{
		CAKE.clear(W,H);
		
	}
	return 0;
}
