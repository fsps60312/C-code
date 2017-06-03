#include<cstdio>
#include<cassert>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
const double EPS=1e-8;
struct Point
{
	double x,y;
	Point(){}
	Point(const double _x,const double _y):x(_x),y(_y){}
	bool operator==(const Point &p)const{return x==p.x&&y==p.y;}
};
Point MidPoint(const Point &a,const Point &b){return Point(0.5*(a.x+b.x),0.5*(a.y+b.y));}
double Sq(const double v){return v*v;}
double Dist(const Point &a,const Point &b){return sqrt(Sq(a.x-b.x)+Sq(a.y-b.y));}
Point Excenter(const Point &a,const Point &b,const Point &c)
{
	if(a==b)return MidPoint(a,c);
	if(a==c)return MidPoint(a,b);
	if(b==c)return MidPoint(a,b);
	const Point ab=MidPoint(a,b),bc=MidPoint(b,c);
	const double ax=a.y-b.y,ay=b.x-a.x,cx=b.y-c.y,cy=c.x-b.x;
	//ab.x+t*ax==bc.x+T*cx, ab.y+t*ay==bc.y+T*cy
	//ab.x-bc.x+t*ax==T*cx, ab.y-bc.y+t*ay==T*cy
	//(ab.x-bc.x+t*ax)/cx==(ab.y-bc.y+t*ay)/cy
	//t=((ab.y-bc.y)/cy-(ab.x-bc.x)/cx)/((ax/cx)-(ay/cy))
	const double t=((ab.y-bc.y)*cx-(ab.x-bc.x)*cy)/((ax*cy)-(ay*cx));
	return Point(ab.x+t*ax,ab.y+t*ay);
}
struct Cycle
{
	Point o;
	double r;
	Cycle(){}
	Cycle(const Point &_o,const double _r):o(_o),r(_r){}
	Cycle(const Point &a,const Point &b):o(MidPoint(a,b)),r(Dist(a,b)/2.0){}
	Cycle(const Point &a,const Point &b,const Point &c):o(Excenter(a,b,c)),r((Dist(o,a)+Dist(o,b)+Dist(o,c))/3.0){}
	bool Contains(const Point &p)const{return Dist(o,p)<=r+EPS;}//EPS is crutial
};
unsigned int Rand()
{
	unsigned int seed=20160410;
	seed=seed*0xdefaced+132741;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2];
	unsigned int sz;
	Point p;
	Node(const Point &_p):sz(1),p(_p){ch[0]=ch[1]=NULL;}
};
unsigned int Sz(Node *o){return o?o->sz:0;}
void Maintain(Node *o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(Rand()%(a->sz+b->sz)<a->sz)
	{
		a->ch[1]=Merge(a->ch[1],b);
		Maintain(a);
		return a;
	}
	else
	{
		b->ch[0]=Merge(a,b->ch[0]);
		Maintain(b);
		return b;
	}
}
void Split(Node* o,Node* &a,Node* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=(int)Sz(o->ch[0]))
	{
		b=o;
		Split(o->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(o->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		Maintain(a);
	}
}
void Delete(Node* &o)
{
	if(!o)return;
	Delete(o->ch[0]),Delete(o->ch[1]);
	delete o;o=NULL;
}
const Point &Query(Node *o,const int loc)
{
	if(loc==(int)Sz(o->ch[0]))return o->p;
	if(loc<(int)Sz(o->ch[0]))return Query(o->ch[0],loc);
	else return Query(o->ch[1],loc-Sz(o->ch[0])-1);
}
struct Vector
{
	Node *S;
	vector<Node**>ORI;
	vector<int>LOCS;
	Vector():S(NULL){}
//	Vector(Node *o):S(o){ORI.push_back(NULL),LOCS.push_back(0);}
	void PushBack(Node* &o)
	{
		ORI.push_back(&o),LOCS.push_back(Sz(S));
		S=Merge(S,o);
	}
//	void PushBack(Vector &v)
//	{
//		for(int i=0;i<(int)v.LOCS.size();i++)ORI.push_back(v.ORI[i]),LOCS.push_back(v.LOCS[i]+Sz(S));
//		S=Merge(S,v.S);
//	}
	void PushBack(const Point &p)
	{
		ORI.push_back(NULL),LOCS.push_back(Sz(S));
		S=Merge(S,new Node(p));
	}
	void PushBack(const vector<Point>&ps)
	{
		for(int i=0;i<(int)ps.size();i++)PushBack(ps[i]);
	}
	void Recover()
	{
		while(!LOCS.empty())
		{
			static Node *tmp;
			Split(S,S,ORI.back()?*ORI.back():tmp,LOCS.back());
			ORI.pop_back(),LOCS.pop_back();
		}
	}
//	void Clear()
//	{
//		Delete(S);
//		ORI.clear(),LOCS.clear();
//	}
	Point operator[](const int id)const{return Query(S,id);}
	int size()const{return Sz(S);}
};
Cycle MinCycle(const Vector &ps,const int j,const int k)
{
	Cycle ans=Cycle(ps[j],ps[k]);
	for(int i=0;i<k;i++)if(!ans.Contains(ps[i]))ans=Cycle(ps[i],ps[j],ps[k]);
	return ans;
}
Cycle MinCycle(const Vector &ps,const int j)
{
	Cycle ans=Cycle(ps[0],ps[j]);
	for(int i=1;i<j;i++)if(!ans.Contains(ps[i]))ans=MinCycle(ps,j,i);
	return ans;
}
Cycle MinCycle(const Vector &ps,Cycle ans,const int start)
{
	for(int i=start;i<(int)ps.size();i++)if(!ans.Contains(ps[i]))ans=MinCycle(ps,i);
	return ans;
}
Point P[100000];
int MOD;
Node *PS[317];
Cycle CYC[317][317];
Cycle MinCycle(const int l,const int r)
{
	const int li=(l+MOD-1)/MOD,ri=(r+1)/MOD-1;
	Vector ps=Vector();
	Cycle ans;
	if(li<=ri)
	{
//		printf("MOD=%d,(%d,%d),(%d,%d)\n",MOD,l,r,li,ri);
		for(int i=li;i<=ri;i++)ps.PushBack(PS[i]);
		assert(MOD*(li-1)+1<=l&&l<=MOD*li);
		assert(MOD*(ri+1)-1<=r&&r<=MOD*(ri+2)-2);
		vector<Point>vps;
		for(int i=l;i<MOD*li;i++)vps.push_back(P[i]);
		for(int i=MOD*(ri+1);i<=r;i++)vps.push_back(P[i]);
		random_shuffle(vps.begin(),vps.end());
		ps.PushBack(vps);
		ans=MinCycle(ps,CYC[li][ri],MOD*(ri-li+1));
	}
	else
	{
		vector<Point>vps;
		for(int i=l;i<=r;i++)vps.push_back(P[i]);
		random_shuffle(vps.begin(),vps.end());
		ps.PushBack(vps);
		ans=MinCycle(ps,Cycle(P[l],0.0),1);
	}
	ps.Recover();
	return ans;
}
int N,M;
void BuildCYC()
{
	MOD=max(1,(int)sqrt(N));
	static vector<int>idx[317];
	const int m=(N-1)/MOD;
	for(int i=0;i<m;i++)idx[i].clear();
	for(int i=0;i<N;i++)idx[i/MOD].push_back(i);
	for(int i=0;i<m;i++)
	{
		random_shuffle(idx[i].begin(),idx[i].end());
		Delete(PS[i]);
		for(int j=0;j<(int)idx[i].size();j++)PS[i]=Merge(PS[i],new Node(P[idx[i][j]]));
	}
	for(int i=0;i<m;i++)
	{
		Vector ps=Vector();
		ps.PushBack(PS[i]);
		CYC[i][i]=MinCycle(ps,Cycle(ps[0],0.0),1);
		ps.Recover();
	}
	for(int gap=1;gap<m;gap++)
	{
		for(int i=0;i+gap<m;i++)
		{
			Vector ps=Vector();
			for(int j=i;j<=i+gap;j++)ps.PushBack(PS[j]);
			CYC[i][i+gap]=MinCycle(ps,CYC[i][i+gap-1],gap*MOD);
			ps.Recover();
		}
	}
}
vector<Point>ANS;
bool Solve(const double radius)
{
	ANS.clear();
	for(int i=0;i<N;)
	{
		if((int)ANS.size()>=M)return false;
		int l=i,r=N-1;
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(MinCycle(i,mid).r<=radius)l=mid;
			else r=mid-1;
		}
		ANS.push_back(MinCycle(i,r).o);
		i=r+1;
	}
	return true;
}
int main()
{
	for(int i=0;i<317;i++)PS[i]=NULL;
	srand(7122);
//	freopen("in.txt","r",stdin);
//	freopen("wyk10a.in","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)scanf("%lf%lf",&P[i].x,&P[i].y);
	BuildCYC();
	double l=0.0,r=2000000.0;
	for(;r-l>EPS;)
	{
		const double mid=0.5*(l+r);
//		if(mid==l||mid==r)break;
//		printf("(%.9f,%.9f)\n",l,r);
		if(Solve(mid))r=mid;
		else l=mid;
	}
	printf("%.9f\n",r);
	assert(Solve(r));
	printf("%d\n",(int)ANS.size());
	for(int i=0;i<(int)ANS.size();i++)printf("%.9f %.9f\n",ANS[i].x,ANS[i].y);
	return 0;
}
