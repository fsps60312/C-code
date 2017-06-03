#include<cstdio>
#include<cassert>
#include<set>
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
}DJ;
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
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if((int)Rand()%(Sz(a)+Sz(b))<Sz(a))
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
void Split(Node *o,Node* &a,Node* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=Sz(o->ch[0]))
	{
		b=o;
		Split(b->ch[0],a,b->ch[0],loc);
		Maintain(b); 
	}
	else
	{
		a=o;
		Split(a->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		Maintain(a);
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
		int top;
		Link(const int _v):ROOT(new Node(_v)),top(-1){}
		int size(){return Sz(ROOT);}
		void clear(){Dispose(ROOT);}
};
struct LinkPointerComparer{bool operator()(Link *a,Link *b)const{return a->size()>b->size();};};
Link LINK[100000];
Node *NODE[100000];
int N,M;
set<Link*,LinkPointerComparer>LIGHT[100000];
void OpenPathToRoot(const int source)
{
	for(int u=source;LINK[u]->top!=-1;u=LINK[LINK[u]->top])
	{
		const int top=LINK[u]->top;
		Split(LINK[top],NODE[top],LINK[]);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<100000;i++)LINK[i]=NULL;
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)if(LINK[i])LINK[i].clear(),LINK[i]=Link(i),NODE[i]=LINK[i].ROOT;
		for(int i=0;i<N;i++)LIGHT[i].clear();
		DJ.clear(N);
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			if(DJ[a]!=DJ[b])
			{
				assert(0);
			}
			else
			{
				assert(0);
			}
		}
	}
	return 0;
}
