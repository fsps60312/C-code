#include<cstdio>
#define AtRange(v,l,r) (v>=l&&v<=r)
#define abs(x) (x>=0?x:-(x))
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
char LINE[1000000];
int T;
void getlr(int i,int &l,int &r)
{
	for(l=i;LINE[l]==' ';l++);
	if(!LINE[l]){l=-1;return;}
	for(r=l;LINE[r]&&LINE[r]!=' ';r++);
	r--;
}
struct Fraction
{
	int up,down;
	int gcd(int a,int b){return b?gcd(b,a%b):a;}
	Fraction(int u,int d):up(u),down(d)
	{
		if(d)
		{
			int g=gcd(abs(u),abs(d));
			up/=g,down/=g;
			if(down<0)up*=-1,down*=-1;
		}
	}
	void putline()
	{
		if(!down)printf("don't know\n");
		else if(down!=1)printf("%d/%d\n",up,down);
		else printf("%d\n",up);
	}
	bool operator==(Fraction a)const{return up==a.up&&down==a.down;}
};
struct Equation
{//x+y=c
	int x,y,c;
	void handle(char v,int &left,int &pos)
	{
		switch(v)
		{
			case'=':left=-1,pos=1;break;
			case'+':pos=1;break;
			case'-':pos=-1;break;
			case'x':x+=left*pos;break;
			case'y':y+=left*pos;break;
			default:c+=(v-'0')*left*pos;break;
		}
	}
	void handlexyc(char v,int coe,int &left,int &pos)
	{
		switch(v)
		{
			case'x':x+=coe*left*pos;break;
			case'y':y+=coe*left*pos;break;
			default:c+=(v-'0')*left*pos;break;
		}
	}
	void init()
	{
		x=y=c=0;
		int i=0,l,r,left=1,pos=1;
		getlr(i,l,r);
		while(l>=0)
		{
			if(l==r)handle(LINE[l],left,pos);
			else
			{
				if(LINE[l]=='-')pos*=-1,l++;
				if(l==r)handlexyc(LINE[l],1,left,pos);
				else
				{
					int coe=0;
					while(AtRange(LINE[l],'0','9'))coe*=10,coe+=LINE[l++]-'0';
					if(l==r)handlexyc(LINE[l],coe,left,pos);
					else if(l<r)termin();
				}
			}
			getlr(i=r+1,l,r);
		}
	}
}E1,E2;
Fraction getx(Equation e)
{
	if(e.y)return Fraction(0,0);
	if(e.x)return Fraction(-e.c,e.x);
	return Fraction(e.c,0);
}
Fraction getx()
{
	Fraction f1=getx(E1);if(f1.up&&!f1.down)return f1;
	Fraction f2=getx(E2);if(f2.up&&!f2.down)return f2;
	if(f1.down&&f2.down)return f1==f2?f1:Fraction(0,0);
	else if(f1.down||f2.down)return f1.down?f1:f2;
	int x=E1.x*E2.y-E2.x*E1.y,c=-(E1.c*E2.y-E2.c*E1.y);
	return Fraction(c,x);
}
Fraction gety(Equation e)
{
	if(e.x)return Fraction(0,0);
	if(e.y)return Fraction(-e.c,e.y);
	return Fraction(e.c,0);
}
Fraction gety()
{
	Fraction f1=gety(E1);if(f1.up&&!f1.down)return f1;
	Fraction f2=gety(E2);if(f2.up&&!f2.down)return f2;
	if(f1.down&&f2.down)return f1==f2?f1:Fraction(0,0);
	else if(f1.down||f2.down)return f1.down?f1:f2;
	int y=E1.y*E2.x-E2.y*E1.x,c=-(E1.c*E2.x-E2.c*E1.x);
	return Fraction(c,y);
}
int main()
{
	freopen("in.txt","r",stdin);
	gets(LINE);sscanf(LINE,"%d",&T);
	while(T--)
	{
		gets(LINE);E1.init();
		gets(LINE);E2.init();
//		printf("%d %d %d\n",E1.x,E1.y,E1.c);
//		printf("%d %d %d\n",E2.x,E2.y,E2.c);
		getx().putline();
		gety().putline();
		if(T)
		{
			gets(LINE);
			puts("");
		}
	}
}
