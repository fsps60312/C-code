#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9;
unsigned int Rand()
{
	static unsigned int seed=20160219;
	seed*=0xdefaced,seed+=134454;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2];
	const int val;
	unsigned int sz;
	bool flipped;
	Node(const int _val):ch{NULL,NULL},val(_val),sz(1),flipped(false){}
	static unsigned int Sz(Node *o){return o?o->sz:0;}
	void Maintain()
	{
		assert(!flipped);
		sz=Sz(ch[0])+1+Sz(ch[1]);
	}
	void Flip(){flipped^=true,swap(ch[0],ch[1]);}
	void PutDown()
	{
		if(!flipped)return;
		for(int d=0;d<2;d++)if(ch[d])ch[d]->Flip();
		flipped=false;
	}
};
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(Rand()%(a->sz+b->sz)<a->sz)
	{
		a->PutDown();
		a->ch[1]=Merge(a->ch[1],b);
		a->Maintain();
		return a;
	}
	else
	{
		b->PutDown();
		b->ch[0]=Merge(a,b->ch[0]);
		b->Maintain();
		return b;
	}
}
void Split(Node *o,Node* &a,Node* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=(int)Node::Sz(o->ch[0]))
	{
		(b=o)->PutDown();
		Split(b->ch[0],a,b->ch[0],loc);
		b->Maintain();
	}
	else
	{
		(a=o)->PutDown();
		Split(a->ch[1],a->ch[1],b,loc-Node::Sz(o->ch[0])-1);
		a->Maintain();
	}
}
typedef long long LL;
void Extract(Node *o,vector<double>&output)
{
	if(!o)return;
	o->PutDown();
	Extract(o->ch[0],output);
	output.push_back(o->val);
	Extract(o->ch[1],output);
}
struct Point
{
	double x,y;
	Point():x(),y(){}
	Point(const double &_x,const double &_y):x(_x),y(_y){}
	bool operator<(const Point &p)const{return x!=p.x?x<p.x:y<p.y;}
	bool operator==(const Point &p)const{return x==p.x&&y==p.y;}
//	void Print()const{printf("(%.4f,%.4f)",x,y);}
};
double Sq(const double &x){return x*x;}
double Dist(const Point &a,const Point &b){return sqrt(Sq(a.x-b.x)+Sq(a.y-b.y));}
Point MidPoint(const Point &a,const Point &b){return Point(0.5*(a.x+b.x),0.5*(a.y+b.y));}
Point Solve(const double &a,const double &b,const double &c,const double &A,const double &B,const double &C)
{
	//ax+by+c=0
	//Ax+By+C=0
	//Aax+Aby+Ac=0
	//Aax+Bay+Ca=0
	//(Ab-Ba)y+(Ac-Ca)=0
	//y=(Ca-Ac)/(Ab-Ba)
	//Bax+Bby+Bc=0
	//Abx+Bby+Cb=0
	//(Ba-Ab)x+(Bc-Cb)=0
	//x=(Cb-Bc)/(Ba-Ab)
//	printf("(%.4f,%.4f,%.4f)(%.4f,%.4f,%.4f)\n",a,b,c,A,B,C);
	return Point((C*b-B*c)/(B*a-A*b),(C*a-A*c)/(A*b-B*a));
}
struct Cycle
{
	Point o;
	double r;
	Cycle(const Point &_o):o(_o),r(0.0){}
	Cycle(const Point &a,const Point &b):o(MidPoint(a,b)),r(0.5*Dist(a,b)){}
	Cycle(const Point &a,const Point &b,const Point &c)
	{
//		printf("a=");a.Print();printf("b=");b.Print();printf("c=");c.Print();puts("");
		if((a.x-b.x)*(b.y-c.y)==(b.x-c.x)*(a.y-b.y))
		{
			o=MidPoint(a,c),r=0.5*Dist(a,c);
		}
		else
		{
			//((a.y-b.y)*t1+0.5*(a.x+b.x),(b.x-a.x)*t1+0.5*(a.y+b.y))
			//((c.y-b.y)*t2+0.5*(c.x+b.x),(b.x-c.x)*t2+0.5*(c.y+b.y))
			//(a.y-b.y)*t1-(c.y-b.y)*t2+0.5*(a.x-c.x)=0
			//(b.x-a.x)*t1-(b.x-c.x)*t2+0.5*(a.y-c.y)=0
			const Point &ans=Solve(a.y-b.y,-(c.y-b.y),0.5*(a.x-c.x),b.x-a.x,-(b.x-c.x),0.5*(a.y-c.y));
//			printf("ans=(%.4f,%.4f)\n",ans.x,ans.y);
			o=Point((a.y-b.y)*ans.x+0.5*(a.x+b.x),(b.x-a.x)*ans.x+0.5*(a.y+b.y));
			r=Dist(o,a);
		}
	}
//	void Print()const{printf("(%.4f,%.4f,r=%.4f)\n",o.x,o.y,r);}
};
Cycle Solve3(const vector<Point>&ps,const int j,const int i)
{
	Cycle cycle=Cycle(ps[j],ps[i]);
	for(int k=0;k<j;k++)if(Dist(cycle.o,ps[k])>cycle.r)
	{
		vector<Point>tmp;
		tmp.push_back(ps[k]),tmp.push_back(ps[j]),tmp.push_back(ps[i]);
		sort(tmp.begin(),tmp.end());
		cycle=Cycle(tmp[0],tmp[1],tmp[2]);
	}
//	cycle.Print();
	return cycle;
}
Cycle Solve2(const vector<Point>&ps,const int i)
{
	Cycle cycle=Cycle(ps[0],ps[i]);
	for(int j=1;j<i;j++)if(Dist(cycle.o,ps[j])>cycle.r)cycle=Solve3(ps,j,i);
	return cycle;
}
Cycle Solve1(const vector<Point>&ps)
{
	const int n=ps.size();assert(n);
	Cycle cycle=Cycle(ps[0]);
	for(int i=1;i<n;i++)if(Dist(cycle.o,ps[i])>cycle.r)cycle=Solve2(ps,i);
	return cycle;
}
Node *S[2];
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	int querycount;
	scanf("%d%d",&N,&querycount);
	S[0]=S[1]=NULL;
	for(int d=0;d<2;d++)for(int i=0,v;i<N;i++)scanf("%d",&v),S[d]=Merge(S[d],new Node(v));
	for(int type;querycount--;)
	{
		scanf("%d",&type);
		switch(type)
		{
			case 1:
			{
				int id,l,r;scanf("%d%d%d",&id,&l,&r),l--;
				Node *a,*b,*c;
				Split(S[id],b,c,r);
				Split(b,a,b,l);
				b->Flip();
				S[id]=Merge(a,Merge(b,c));
			}break;
			case 2:
			{
				int id,l1,r1,l2,r2;scanf("%d%d%d%d%d",&id,&l1,&r1,&l2,&r2),l1--,l2--;
				Node *a,*b,*c,*d,*e;
				Split(S[id],d,e,r2);
				Split(d,c,d,l2);
				Split(c,b,c,r1);
				Split(b,a,b,l1);
				S[id]=Merge(Merge(a,d),Merge(c,Merge(b,e)));
			}break;
			case 3:
			{
				int l,r;scanf("%d%d",&l,&r),l--;
				Node *a0,*b0,*c0,*a1,*b1,*c1;
				Split(S[0],b0,c0,r);
				Split(b0,a0,b0,l);
				Split(S[1],b1,c1,r);
				Split(b1,a1,b1,l);
				S[0]=Merge(a0,Merge(b1,c0));
				S[1]=Merge(a1,Merge(b0,c1));
			}break;
			case 4:
			{
				int l,r;scanf("%d%d",&l,&r),l--;
				Node *a0,*b0,*c0,*a1,*b1,*c1;
				Split(S[0],b0,c0,r);
				Split(b0,a0,b0,l);
				Split(S[1],b1,c1,r);
				Split(b1,a1,b1,l);
				vector<double>xs,ys;
				Extract(b0,xs),Extract(b1,ys);
				S[0]=Merge(a0,Merge(b0,c0));
				S[1]=Merge(a1,Merge(b1,c1));
				assert(xs.size()==ys.size());
				vector<Point>ps;
				for(int i=0;i<(int)xs.size();i++)ps.push_back(Point(xs[i],ys[i]));
				sort(ps.begin(),ps.end()),ps.resize(unique(ps.begin(),ps.end())-ps.begin());
				random_shuffle(ps.begin(),ps.end());//for fear of degenerating of time complexity
//				for(const Point &p:ps)printf("(%.0f,%.0f)",p.x,p.y);puts("");
				printf("%.2f\n",Solve1(ps).r);
			}break;
		}
		assert((int)S[0]->sz==N&&(int)S[1]->sz==N);
	}
	return 0;
}
