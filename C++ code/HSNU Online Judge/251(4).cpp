#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Obstacle
{
	int x1,y1,x2,y2;
	LL cost;
	Obstacle(){}
	Obstacle(const int _x1,const int _y1,const int _x2,const int _y2,const LL _c):x1(_x1),y1(_y1),x2(_x2),y2(_y2),cost(_c){}
	bool operator<(const Obstacle &o)const{return x2>o.x2;}
};
vector<Obstacle>OBSTACLE;
int N,M,P;
LL B;
struct Line
{
	int x,y1,y2;
	LL cost;
	Line(){}
	Line(const int _x,const int _y1,const int _y2,const LL _c):x(_x),y1(_y1),y2(_y2),cost(_c){}
	bool operator<(const Line &l)const{return x<l.x;}
};
struct Seg
{
	struct Node
	{
		Node *l,*r;
		LL mn,tag;
		Node(const LL v):l(NULL),r(NULL),mn(v),tag(0LL){}
	};
	Node *root=NULL;
	void Delete(Node* &o)
	{
		if(!o)return;
		Delete(o->l),Delete(o->r);
		delete o;
		o=NULL;
	}
	void clear(){Delete(root);root=new Node(0LL);}
	void Maintain(Node* &o)
	{
		assert(o->tag==0LL);
		assert(o->l&&o->r);
		o->mn=min(o->l->mn,o->r->mn);
	}
	void PutDown(Node* &o)
	{
		const LL tag=o->tag;
		if(o->l&&o->r)
		{
			o->l->mn+=tag,o->l->tag+=tag;
			o->r->mn+=tag,o->r->tag+=tag;
		}
		else if(!o->l&&!o->r)
		{
			o->l=new Node(o->mn);
			o->r=new Node(o->mn);
		}
		else assert(0);
		o->tag=0LL; 
	}
	void Add(Node* &o,const int l,const int r,const int bl,const int br,const LL v)
	{
		assert(o);
		if(l>br||r<bl)return;
		if(bl<=l&&r<=br){o->mn+=v,o->tag+=v;assert(o->mn>=0LL);return;}
		PutDown(o);
		const int mid=(l+r)/2;
		Add(o->l,l,mid,bl,br,v);
		Add(o->r,mid+1,r,bl,br,v);
		Maintain(o);
	}
	void Add(const Line &l){Add(root,1,M,l.y1,l.y2,l.cost);}
	LL Query(Node* &o,const int l,const int r,const int bl,const int br)
	{
		assert(o);
		if(l>br||r<bl)return INF;
		if(bl<=l&&r<=br)return o->mn;
		if(!o->l&&!o->r)return o->mn;
		assert(o->l&&o->r);
		PutDown(o);
		const int mid=(l+r)/2;
		return min(Query(o->l,l,mid,bl,br),Query(o->r,mid+1,r,bl,br));
	}
	LL Query(const int sidelen){return Query(root,1,M,1,M-sidelen+1);}
}SEG;
bool Check(const int sidelen)
{
	if(sidelen==0)return true;
	vector<Line>leftside,rightside;
	for(const auto &o:OBSTACLE)
	{
		const int y1=o.y1-sidelen+1;
		leftside.push_back(Line(o.x1-sidelen+1,y1,o.y2,o.cost));
		rightside.push_back(Line(o.x2,y1,o.y2,-o.cost));
	}
	sort(leftside.begin(),leftside.end());
	sort(rightside.begin(),rightside.end());
//	puts("left:");
//	for(auto u:leftside)printf("%d(%d,%d):%lld\n",u.x,u.y1,u.y2,u.cost);
//	puts("right:");
//	for(auto u:rightside)printf("%d(%d,%d):%lld\n",u.x,u.y1,u.y2,u.cost);
	SEG.clear();
	for(int bl=1,l=0,r=0;bl+sidelen-1<=N;)
	{
		while(l<leftside.size()&&leftside[l].x<=bl)SEG.Add(leftside[l++]);
		while(r<rightside.size()&&rightside[r].x<bl)SEG.Add(rightside[r++]);
//		printf("bl=%d,SEG.Query()=%d\n",bl,SEG.Query(sidelen));
		if(SEG.Query(sidelen)<=B)
		{
			return true;
		}
		assert(r<rightside.size());
		bl=rightside[r].x+1;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%lld%d",&N,&M,&B,&P)==4)
	{
		OBSTACLE.clear();
		for(int i=0,x1,y1,x2,y2;i<P;i++)
		{
			static LL cost;
			scanf("%d%d%d%d%lld",&x1,&y1,&x2,&y2,&cost);
			OBSTACLE.push_back(Obstacle(x1,y1,x2,y2,cost));
		}
		int l=0,r=min(N,M);
		while(l<r)
		{
			const int mid=(l+r+1)/2;
//			printf("mid=%d\n",mid);
			if(Check(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
