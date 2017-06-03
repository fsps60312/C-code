#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
int N,M,P;
LL B;
struct Obstacle
{
	int x1,y1,x2,y2;
	LL cost;
	Obstacle(){}
	Obstacle(const int _x1,const int _y1,const int _x2,const int _y2,const LL _c):x1(_x1),y1(_y1),x2(_x2),y2(_y2),cost(_c){}
	bool operator<(const Obstacle &o)const{return x2>o.x2;}
};
bool CmpX1(const Obstacle &a,const Obstacle &b){return a.x1<b.x1;}
vector<Obstacle>OBSTACLE;
priority_queue<Obstacle>PQ;
struct Bst
{
	struct Node
	{
		Node *l,*r;
		LL mn,tag;
		Node():l(NULL),r(NULL){}
	};
	Node *root;
	Bst():root(NULL){}
	void PutDown(Node* &o)
	{
		if(o->tag==0LL)continue;
		if(o->l)o->l->mn+=o->tag,o->l->tag+=o->tag;
		if(o->r)o->r->mn+=o->tag,o->r->tag+=o->tag;
	}
	void Add(Node* &o,const int l,const int r,const LL v)
	{
		
	}
}BST;
void AddObstacle(const Obstacle &o)
{
	PQ.push(o);
}
void RemoveObstacle()
{
	PQ.pop();
}
bool SetSideLen(const int sidelen)
{
	while(!PQ.empty())PQ.pop();
	for(int bl=1,i=0;bl+sidelen-1<=M;)
	{
		while(i<P&&OBSTACLE[i].x1<=bl+sidelen-1)AddObstacle(OBSTACLE[i++]);
		while(PQ.top().x2<bl)RemoveObstacle();
		if(BST.Query()<=B)return true;
		assert(!PQ.empty());
		bl=PQ.top().x2+1;
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%lld%d",&N,&M,&B,&P)==4)
	{
		OBSTACLE.clear();
		for(int i=0,x1,y1,x2,y2;i<P;i++)
		{
			static LL cost;
			scanf("%d%d%d%d%lld",&x1,&y1,&x2,&y2,&cost);
			OBSTACLE.push_back(Obstacle(x1,y1,x2,y2,cost));
		}
		sort(OBSTACLE.begin(),OBSTACLE.end(),CmpX1);
		int l=0,r=min(N,M);
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Check(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
