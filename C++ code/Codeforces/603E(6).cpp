#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
unsigned int Rand()
{
	static unsigned int seed=20160217;
	seed*=0xdefaced,seed+=153151;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2],*parent,*max_node;
	const int id,v;
	int w,sz;
	bool flipped;
	Node(const int _id,const int _v,const int _w):ch{NULL,NULL},parent(),max_node(this),id(_id),v(_v),w(_w),sz(_w),flipped(false){}
	void Flip()
	{
		flipped^=true;
		swap(ch[0],ch[1]);
	}
	void PutDown()
	{
		if(flipped)
		{
			for(int d=0;d<2;d++)if(ch[d])ch[d]->Flip();
			flipped^=true;
		}
	}
};
int Sz(Node *o){return o?o->sz:0;}
Node *MaxNode(Node *o){return o?o->max_node:NULL;}
Node *Max(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	return (a->v)>(b->v)?a:b;
}
void Maintain(Node *o)
{
	assert(!o->flipped);
	o->sz=Sz(o->ch[0])+(o->w)+Sz(o->ch[1]);
	o->max_node=Max(o,Max(MaxNode(o->ch[0]),MaxNode(o->ch[1])));
}
Node* &GetMe(Node *o)
{
	static Node *nill;
	if(o->parent)
	{
		for(int d=0;d<2;d++)if(o->parent->ch[d]==o)return o->parent->ch[d];
	}
	return nill=NULL;
}
void Rotate(Node *o,const int cu)
{
	Node *u=o;o=o->ch[cu];
	assert(o->parent==u);
	GetMe(u)=o;
	o->parent=u->parent;
	u->PutDown(),o->PutDown();
	u->ch[cu]=o->ch[cu^1];
	if(o->ch[cu^1])o->ch[cu^1]->parent=u;
	o->ch[cu^1]=u;
	u->parent=o;
	Maintain(u),Maintain(o);
}
void Balance(Node *o)
{
	if(!o)return;
	if(Sz(o->ch[0])-Sz(o->ch[1])>1)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>1)Rotate(o,1);
}
void PutDownParents(Node *o)
{
	if(GetMe(o))PutDownParents(o->parent);
	o->PutDown();
}
void RotateUp(Node *o)
{
	Node *p=o->parent;
	for(int d=0;d<2;d++)if(p->ch[d]==o)
	{
		Rotate(p,d);
		Balance(o->ch[0]),Balance(o->ch[1]);//懶的分case直接讓它自動平衡 
		return;
	}
	assert(0);
}
void MaintainParents(Node *o)
{
	Maintain(o);
	if(GetMe(o))MaintainParents(o->parent);
}
Node *Splay(Node *o)
{
	PutDownParents(o);
	MaintainParents(o);
	while(GetMe(o))RotateUp(o);
	return o;
}
Node *Access(Node *o)
{
	Node *right;
	for(right=NULL;o;o=o->parent)
	{
		Splay(o);
		o->w-=Sz(right);
		o->w+=Sz(o->ch[1]);
		o->ch[1]=right;
		Maintain(right=o);
	}
	return right;
}
void SetRoot(Node *o){Access(o)->Flip();}
int ODD_CNT;
bool IsConnected(Node *a,Node *b)
{
	Access(a),Splay(a);
	Access(b),Splay(b);
	return a->parent;
}
void Link(Node *a,Node *b)
{
//	printf("Link %d %d\n",a->id,b->id);
	assert(!IsConnected(a,b));
	const int asz=Access(a)->sz,bsz=Access(b)->sz;
	ODD_CNT-=(asz&1)+(bsz&1);
	SetRoot(a);
	Splay(a)->parent=b;
	b->w+=Sz(a);
	const int sz=Access(b)->sz;
	assert(sz==asz+bsz);
	ODD_CNT+=(sz&1);
}
void Cut(Node *a,Node *b)
{
//	printf("Cut %d %d\n",a->id,b->id);
	assert(IsConnected(a,b));
	const int sz=Access(a)->sz;
	ODD_CNT-=(sz&1);
	SetRoot(a);
	Access(b);
	Splay(b);
	assert(b->ch[0]==a);
	b->ch[0]->parent=NULL;
	b->ch[0]=NULL;
	MaintainParents(b);
	const int asz=Access(a)->sz,bsz=Access(b)->sz;
	assert(sz==asz+bsz);
	ODD_CNT+=(asz&1)+(bsz&1);
}
Node *S[100000],*ES[300000];
struct Edge
{
	int a,b,l;
}EDGE[300000];
struct CmpEdgeIdx{bool operator()(const int a,const int b)const
{
	if((ES[a]->v)!=(ES[b]->v))return (ES[a]->v)>(ES[b]->v);
	return a<b;
}};
set<int,CmpEdgeIdx>EDGE_IN_GRAPH;
Node *PathMax(Node *a,Node *b)
{
	SetRoot(a);
	return Access(b)->max_node;
}
void AddEdge(const int ei)
{
	const Edge &e=EDGE[ei];
//	printf("Add %d (%d,%d,%d)\n",ei,e.a,e.b,e.l);
	Link(S[e.a],ES[ei]);
	Link(S[e.b],ES[ei]);
	EDGE_IN_GRAPH.insert(ei);
}
void DeleteEdge(const int ei)
{
	const Edge &e=EDGE[ei];
//	printf("Delete %d (%d,%d,%d)\n",ei,e.a,e.b,e.l);
	Cut(S[e.a],ES[ei]);
	Cut(S[e.b],ES[ei]);
	auto it=EDGE_IN_GRAPH.find(ei);
	assert(it!=EDGE_IN_GRAPH.end());
	EDGE_IN_GRAPH.erase(it);
}
void NewEdge(const int ei)
{
	const Edge &e=EDGE[ei];
	if(IsConnected(S[e.a],S[e.b]))
	{
		Node *max_node=PathMax(S[e.a],S[e.b]);
//		printf("%d %d\n",max_node->id,max_node->v);
		assert((max_node->id)>=0);
		if((max_node->v)<=e.l)return;
		DeleteEdge(max_node->id);
	}
	AddEdge(ei);
}
void DeleteEdges()
{
	const int pre_odd_cnt=ODD_CNT;
	while(!EDGE_IN_GRAPH.empty())
	{
		const int ei=*EDGE_IN_GRAPH.begin();
		DeleteEdge(ei);
		assert(ODD_CNT>=pre_odd_cnt);
		if(ODD_CNT>pre_odd_cnt){AddEdge(ei);assert(ODD_CNT==pre_odd_cnt);break;}
	}
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)S[i]=new Node(-i-1,-1,1);
		ODD_CNT=N;
		EDGE_IN_GRAPH.clear();
		for(int i=0;i<M;i++)
		{
			int &a=EDGE[i].a,&b=EDGE[i].b,&l=EDGE[i].l;
			scanf("%d%d%d",&a,&b,&l),a--,b--;
			ES[i]=new Node(i,l,0);
			NewEdge(i);
			if(ODD_CNT==0)DeleteEdges();
			assert(ODD_CNT>=0);
			if(ODD_CNT==0)printf("%d\n",EDGE[*EDGE_IN_GRAPH.begin()].l);
			else puts("-1");
		}
	}
	return 0;
}
