#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
unsigned int Rand()
{
	static unsigned int seed=20160217;
	seed*=0xdefaced,seed+=140734;
	return seed+=seed>>20;
}
bool DEFAULT_CONSTRUCTOR_ENABLED=true;
struct Node
{
	int ch[2],parent,sz;
	int id,w,mxid;
	bool flipped;
	Node(){assert(DEFAULT_CONSTRUCTOR_ENABLED);}
	Node(const int _id,const int _w):ch{-1,-1},parent(-1),sz(1),id(_id),w(_w),mxid(_id),flipped(false){}
}S[100000+300000];
int TREE_SZ[100000+300000],TREE_ID[100000+300000];
void Flip(const int o){swap(S[o].ch[0],S[o].ch[1]);S[o].flipped^=true;}
void PutDown(const int o)
{
	if(S[o].flipped)
	{
		for(int d=0;d<2;d++)if(S[o].ch[d]!=-1)Flip(S[o].ch[d]);
		S[o].flipped=false;
	}
}
int Sz(const int o){return o!=-1?S[o].sz:0;}
int Mxw(const int o){return o!=-1?S[S[o].mxid].w:-INF;}
void Maintain(const int o)
{
	S[o].sz=Sz(S[o].ch[0])+1+Sz(S[o].ch[1]);
	int &mxid=S[o].mxid=S[o].id;
	for(int d=0;d<2;d++)if(Mxw(S[o].ch[d])>mxid)mxid=S[S[o].ch[d]].mxid;
}
void Rotate(int o,const int cu)
{
	PutDown(o);
	const int u=o,p=S[o].parent;
	PutDown(o=S[o].ch[cu]);
	if(p!=-1)
	{
		for(int d=0;d<2;d++)if(S[p].ch[d]==u){S[p].ch[d]=o;break;}
	}
	else
	{
		TREE_SZ[o]=TREE_SZ[u];
		TREE_ID[o]=TREE_ID[u];
	}
	S[o].parent=S[u].parent;
	S[u].ch[cu]=S[o].ch[cu^1];
	if(S[o].ch[cu^1]!=-1)S[S[o].ch[cu^1]].parent=u;
	S[o].ch[cu^1]=u;
	S[u].parent=o;
	Maintain(u),Maintain(o);
}
void Rotate(int o)
{
	if(Sz(o)==1)return;
	if((int)(Rand()%(Sz(o)-1))<Sz(Sz(S[o].ch[0])))Rotate(o,0);
	else Rotate(o,1);
}
int ParentDirection(const int o)
{
	const int p=S[o].parent;
	if(p==-1)return -1;
	for(int d=0;d<2;d++)if(S[p].ch[d]==o)return d;
	return -1;
}
bool RotateUp(int o)
{
	const int pd=ParentDirection(o);
	if(pd==-1)return false;
	Rotate(S[o].parent,pd);
	//imbalanced
	return true;
}
void FlipUpstream(int o)
{
	const int pd=ParentDirection(o);
	if(pd!=-1)FlipUpstream(S[o].parent);
	PutDown(o);
}
void MaintainUpstream(int o)
{
	const int pd=ParentDirection(o);
	Maintain(o);
	if(pd!=-1)MaintainUpstream(S[o].parent);
}
int Splay(int o)
{
	FlipUpstream(o);
	while(RotateUp(o));
	return o;
}
int Access(int o)
{
	while(S[o=Splay(o)].parent!=-1)
	{
		FlipUpstream(S[o].parent); 
		S[S[o].parent].ch[1]=o;
		MaintainUpstream(S[o].parent);
	}
	return o;
}
void SetRoot(int o){Flip(Access(o));}
void ConnectTree(int a,int b)
{
	assert(TREE_ID[Access(a)]!=TREE_ID[Access(b)]);
	SetRoot(a);
	TREE_SZ[Access(b)]+=TREE_SZ[Access(a)];
	S[a].parent=b;
}
struct Edge
{
	int a,b,l;
	Edge(){}
	Edge(const int _a,const int _b,const int _l):a(_a),b(_b),l(_l){}
};
vector<Edge>EDGE;
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	DEFAULT_CONSTRUCTOR_ENABLED=false;
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)S[i]=Node(i,-INF),TREE_SZ[i]=1,TREE_ID[i]=i;
		EDGE.clear();
		for(int i=0,a,b,l;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&l),a--,b--;
			S[N+i]=Node(N+i,l);
			
		}
	}
	return 0;
}
