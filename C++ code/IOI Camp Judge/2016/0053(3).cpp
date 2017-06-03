#include<cstdio>
#include<cassert>
#include<set>
#include<map>
#include<vector>
using namespace std;
unsigned int Rand()
{
	static unsigned int seed=20160203;
	seed*=0xdefaced;
	seed+=92225;
	return seed+=seed>>20;
}
struct Djset
{
	int data[100000];
	void clear(const int n){for(int i=0;i<n;i++)data[i]=i;}
	int find(const int a){return data[a]==a?a:(data[a]=find(data[a]));}
	bool Merge(int a,int b){if((a=find(a))==(b=find(b)))return false;data[a]=b;return true;}
	int operator[](const int idx){return find(idx);}
}COMP,ID;
struct Node
{
	Node *ch[2],*fa;
	const int v;
	int sz;
	Node(const int _v):ch{NULL,NULL},fa(NULL),v(_v),sz(1){}
};
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->fa=NULL;
	for(int i=0;i<2;i++)if(o->ch[i])o->ch[i]->fa=o;
}
void Rotate(Node* &o,const int cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu^1]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
map<Node*,Link*>TOL;
void Splay(Node* &o)
{
	if(!o->fa)return;
	while(o->fa)
	{
		if(!o->fa->fa)
		{
			const auto it=TOL.find(o->fa);
			assert(it!=TOL.end());
			TOL[o]=it->second;
			TOL.erase(it);
		}
		for(int d=0;d<2;d++)if(o->fa->ch[d]==o){Rotate(o->fa,d);break;}
	}
}
void Dispose(Node* &o)
{
	if(!o)return;
	for(int i=0;i<2;i++)Dispose(o->ch[i]);
	delete o;o=NULL;
}
class Link
{
	private:
	public:
		Node *ROOT;
		Node *top;
		Link(const int _v):ROOT(new Node(_v)),top(NULL){}
		int size(){return Sz(ROOT);}
		void clear(){Dispose(ROOT);}
};
Link *LINK[100000];
Node *NODE[100000];
int N,M;
void Access(const int u)
{
	Node *cur=NODE[u];
	Splay(cur);
	Link *link=TOL[cur];
	
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<100000;i++)LINK[i]=NULL;
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		TOL.clear();
		for(int i=0;i<N;i++)
		{
			if(LINK[i]){LINK[i]->clear();delete LINK[i];}
			LINK[i]=new Link(i);
			NODE[i]=LINK[i]->ROOT;
			TOL[NODE[i]]=LINK[i];
		}
		COMP.clear(N),ID.clear(N);
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			if(DJ[a]!=DJ[b])
			{
			}
			else
			{
			}
		}
	}
	return 0;
}
