#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define abs(x) (x<0?-x:x)
void getmax(int &a,int b){if(b>a)a=b;}
void getmin(int &a,int b){if(b<a)a=b;}
int T,W,H,N,UP,DOWN,LEFT,RIGHT;
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};
bool AtRange(int v,int l,int r){return v>=l&&v<=r;}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
struct Fraction
{
	int up,down;bool in;
	Fraction():up(0),down(1){}
	Fraction(int u,int d,bool i):up(u),down(d){carry();}
	bool operator<(Fraction a)const{return up*a.down<down*a.up;}
	bool operator>(Fraction a)const{return up*a.down>down*a.up;}
	bool operator>=(Fraction a)const{return up*a.down>=down*a.up;}
	void operator/=(int a){down*=a;carry();}
	void set(int a){up=a,down=1;}
	void set(Fraction a){up=a.up,down=a.down;}
	//Fraction operator-(Fraction a){return Fraction(up*a.down+down*a.up,down*a.down);}
	void carry()
	{
		if(!up){down=1;return;}
		if(down<0)up=-up,down=-down;
		int a=gcd(abs(up),down);
		up/=a,down/=a;
	}
	double value(){return (double)up/down;}
}IT,OT;
struct Meteor
{
	Point p,v;
	void canf()
	{
		scanf("%d%d%d%d",&p.x,&p.y,&v.x,&v.y);
	}
	void GetInterval()
	{
		IT.set(0),OT.set(0);
		Fraction inx,outx,iny,outy;
		if(v.x!=0)
		{
			inx.set((v.x>0?0:W)-p.x);
			outx.set((v.x>0?W:0)-p.x);
			inx/=v.x;
			outx/=v.x;
		}
		else if(AtRange(p.x,1,W-1))inx.set(-1000000),outx.set(1000000);
		else return;
		if(v.y!=0)
		{
			iny.set((v.y>0?0:H)-p.y);
			outy.set((v.y>0?H:0)-p.y);
			iny/=v.y;
			outy/=v.y;
		}
		else if(AtRange(p.y,1,H-1))iny.set(-1000000),outy.set(1000000);
		else return;
		IT.set(max(inx,iny)),OT.set(min(outx,outy));
		//printf("s(%d,%d)p(%d,%d)v(%d,%d)in(%d/%d,%d/%d)out(%d/%d,%d/%d)\n",W,H,p.x,p.y,v.x,v.y,inx.up,inx.down,outx.up,outx.down,iny.up,iny.down,outy.up,outy.down);
	}
}METEOR[100000];
int solve()
{
	vector<Fraction> t;
	for(int i=0;i<N;i++)
	{
		METEOR[i].GetInterval();
		//printf("(%d/%d,%d/%d)\n",IT.up,IT.down,OT.up,OT.down);
		if(IT>=OT)continue;
		//printf("(%.3f,%.3f)\n",IT.value(),OT.value());
		t.push_back(IT),t.push_back(OT);
	}
	int ans=0,ta=0;
	Fraction now;
	sort(t.begin(),t.end());
	for(int i=0;i<t.size();i++)
	{
		if(t[i]>now)
		{
			getmax(ans,ta);
			now=t[i];
		}
		if(t[i].in)ta++;
		else ta--;
	}
	return ans;
}
int main()
{
	IT.in=true;
	OT.in=false;
	//freopen("in.txt","r",stdin);
	//printf("%d%d",(int)1.5,(int)-1.5);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&W,&H,&N);
		UP=H,RIGHT=W,LEFT=DOWN=0;
		for(int i=0;i<N;i++)METEOR[i].canf();
		printf("%d\n",solve());
	}
	return 0;
}
