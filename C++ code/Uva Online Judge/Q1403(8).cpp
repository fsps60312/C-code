#include<cstdio>
#include<stack>
#include<cmath>
#include<cassert>
using namespace std;
const double EPS=1e-9,PI=acos(-1.0);
char EQUATION[1000000];
int RBRACK[1000000];
bool Digit(const char c){return c>='0'&&c<='9';}
struct Node
{
	Node *ch[2];
	char o;
	double val;
	Node(){}
	Node(int l,int r):ch{NULL,NULL}
	{
		while(EQUATION[l]=='('&&RBRACK[l]==r)l++,r--;
		assert(EQUATION[l]!='('||RBRACK[l]<r);
		//check for illegal charactors
		switch(EQUATION[l])
		{
			case'+':
			case'-':
			case'*':
			case'/':assert(0);
			case')':assert(0);
		}
		switch(EQUATION[r])
		{
			case'+':
			case'-':
			case'*':
			case'/':assert(0);
			case'(':assert(0);
		}
		int result=0,loc=-1;
		for(int i=RBRACK[l]+1;i<=r;i=RBRACK[i+1]+1)
		{
			switch(EQUATION[i])
			{
				case'(':
				case')':printf("EQUATION[%d]=%c\n",i,EQUATION[i]),assert(0);break;
				case'+':
				case'-':
					if(result<2)result=2,loc=i;
					break;
				case'*':
				case'/':
					if(result<1)result=1,loc=i;
					break;
			}
		}
		if(result==0)ReadNumber(l,r);
		else
		{
			o=EQUATION[loc];
			ch[0]=new Node(l,loc-1);
			ch[1]=new Node(loc+1,r);
		}
	}
	void ReadNumber(const int l,const int r)
	{
		if(EQUATION[l]=='x')assert(l==r),o='x';
		else
		{
			o='d';
			val=0.0;
			int dotloc;
			for(dotloc=l;dotloc<=r&&EQUATION[dotloc]!='.';dotloc++);
			for(int i=l;i<dotloc;i++)
			{
				assert(Digit(EQUATION[i]));
				val=val*10.0+(EQUATION[i]-'0');
			}
			double tmp=0.1;
			for(int i=dotloc+1;i<=r;i++,tmp*=0.1)
			{
				assert(Digit(EQUATION[i]));
				val+=tmp*(EQUATION[i]-'0');
			}
		}
	}
	double GetValue(const double &x)const
	{
		switch(o)
		{
			case'x':return x;
			case'd':return val;
			case'+':return ch[0]->GetValue(x)+ch[1]->GetValue(x);
			case'-':return ch[0]->GetValue(x)-ch[1]->GetValue(x);
			case'*':return ch[0]->GetValue(x)*ch[1]->GetValue(x);
			case'/':return ch[0]->GetValue(x)/ch[1]->GetValue(x);
			default:assert(0);
		}
		return 0.0;
	}
}*NR,*NT;
double H,B;
double Square(const Node *e,const double &x)
{
	const double v=e->GetValue(x);
	return v*v;
}
double Approximate(const Node *e,const double &l,const double &r)//Simpson's rule
{
	const double mid=0.5*(l+r);
	return (r-l)*(Square(e,l)+4.0*Square(e,mid)+Square(e,r))/6.0;
}
double ApproximateTorque(const Node *e,const double &o,const double &l,const double &r)//Simpson's rule
{
	const double mid=0.5*(l+r);
	return (r-l)*(Square(e,l)*(o-l)+4.0*Square(e,mid)*(o-mid)+Square(e,r)*(o-r))/6.0;
}
double Integrate(const Node *e,const double &l,const double &r,const int cnt=0)
{
	double mid=0.5*(l+r);
	double s=Approximate(e,l,r),s1=Approximate(e,l,mid),s2=Approximate(e,mid,r);
	int nxtc=cnt;
	if(fabs(s1+s2-s)<EPS){if(nxtc++>2)return s1+s2;}
	else nxtc=0;
	return Integrate(e,l,mid,nxtc)+Integrate(e,mid,r,nxtc);
}
double IntegrateTorque(const Node *e,const double &o,const double &l,const double &r,const int cnt=0)//weight point <=> torque==0
{
	double mid=0.5*(l+r);
	double s=ApproximateTorque(e,o,l,r),s1=ApproximateTorque(e,o,l,mid),s2=ApproximateTorque(e,o,mid,r);
	int nxtc=cnt;
	if(fabs(s1+s2-s)<EPS){if(nxtc++>2)return s1+s2;}
	else nxtc=0;
	return IntegrateTorque(e,o,l,mid,nxtc)+IntegrateTorque(e,o,mid,r,nxtc);
}
double CUPC,CUPW;
void GetCUPC()//Get height of Cup's weight point
{
	double l=0.0,r=H;
	while(r-l>EPS)
	{
		const double mid=0.5*(l+r);
		double v=IntegrateTorque(NR,mid,0.0,H)-IntegrateTorque(NT,mid,B,H);
		if(v<0.0)l=mid;
		else r=mid;
	}
	assert(l<=r);
	CUPC=0.5*(l+r);
}
void MeasureWater(const double &h,double &w,double &c)//w is weight of water, c is height of weight point
{
	w=Integrate(NT,B,h);
	double l=B,r=h;
	while(r-l>EPS)
	{
		const double mid=0.5*(l+r);
		if(IntegrateTorque(NT,mid,B,h)<0.0)l=mid;
		else r=mid;
	}
	assert(l<=r);
	c=0.5*(l+r);
}
double GetWP(const double &h)//Get Weight Point
{
	static double w,c;
	MeasureWater(h,w,c);
	return (CUPW*CUPC+w*c)/(CUPW+w);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%lf%lf",&H,&B)==2);
		if(H==0.0&&B==0.0)break;
		assert(0.0<B&&B<H&&H<=100.0);
		for(int type=0;type<=1;type++)
		{
			scanf("%s",EQUATION);
			static int len;
			stack<int>stk;
			//find corresponding right brack for each left brack
			RBRACK[0]=-1;
			for(len=0;EQUATION[len];len++,RBRACK[len]=len-1)
			{
				switch(EQUATION[len])
				{
					case'(':stk.push(len);break;
					case')':RBRACK[stk.top()]=len;stk.pop();break;
				}
			}
			assert(stk.empty());
			Node *node=new Node(0,len-1);
			if(type==0)NR=node;
			else
			{
				NT=new Node();
				NT->o='-';
				NT->ch[0]=NR;
				NT->ch[1]=node;
			}
		}
		CUPW=Integrate(NR,0.0,H)-Integrate(NT,B,H);
		GetCUPC();
		CUPW*=2.5;
		double l=B,r=H;
		//the function of height of weight point must be decreasing, then increasing
		//so do this to find the lowest value
		while(r-l>EPS)
		{
			double lm=(2.0*l+r)/3.0,rm=(l+2.0*r)/3.0;
			double lmwp=GetWP(lm),rmwp=GetWP(rm);
			if(lmwp<rmwp)r=rm;
			else l=lm;
		}
		assert(l<=r);
		printf("Pour %.3f litres / %.3f cm of water.\n",0.001*PI*Integrate(NT,B,0.5*(l+r)),0.5*(l+r)-B);
	}
	return 0;
}
