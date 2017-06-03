#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct Node
{
	int ch[2],parent,sz;
	bool flipped;
	Node():ch{-1,-1},parent(-1),sz(1),flipped(false){}
}S[100000];
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
void Maintain(const int o){S[o].sz=Sz(S[o].ch[0])+1+Sz(S[o].ch[1]);}
void Rotate(int o,const int cu)
{
	PutDown(o);
	const int u=o,p=S[o].parent;
	PutDown(o=S[o].ch[cu]);
	if(p!=-1)for(int d=0;d<2;d++)if(S[p].ch[d]==u){S[p].ch[d]=o;break;}
	S[o].parent=S[u].parent;
	S[u].ch[cu]=S[o].ch[cu^1];
	if(S[o].ch[cu^1]!=-1)S[S[o].ch[cu^1]].parent=u;
	S[o].ch[cu^1]=u;
	S[u].parent=o;
	Maintain(u),Maintain(o);
}
void Rotate(int o)
{
	for(int d=0;d<2;d++)if(Sz(S[o].ch[d])-Sz(S[o].ch[d^1])>1)Rotate(o,d);
}
bool RotateUp(int &o)
{
	const int p=S[o].parent;
	if(p==-1)return false;
	for(int d=0;d<2;d++)if(S[p].ch[d]==o)
	{
		Rotate(o=p,d);
		return true;
	}
	return false;
}
int Splay(int o)
{
	vector<int>stk;
	stk.push_back(o);
	for(;;)
	{
		const int p=S[o].parent;
		if(p==-1)break;
		else if(S[p].ch[0]!=o&&S[p].ch[1]!=o)break;
		else stk.push_back(o=p);
	}
	for(int i=(int)stk.size()-1;i>=0;i--)PutDown(stk[i]);
	o=stk[0];
	for(int i=0;i+1<(int)stk.size();i++)assert(RotateUp(o));
	assert(o==stk[(int)stk.size()-1]);
	return o;
}
int Access(int o)
{
	while(S[o=Splay(o)].parent!=-1)
	{
		PutDown(S[o].parent); 
		S[S[o].parent].ch[1]=o;
	}
	while(o->ch[0]!=-1)PutDown()RotateUp()
	return o;
}
struct DjSet
{
	int parent[100000],sz[100000],odd_cnt;
	void clear(const int n){for(int i=0;i<n;i++)parent[i]=i,sz[i]=1;odd_cnt=n;}
	int find(const int i){return parent[i]==i?i:(parent[i]=find(parent[i]));}
	bool merge(int a,int b)
	{
		if((a=find(a))==(b=find(b)))return false;
		if(sz[a]>sz[b])swap(a,b);
		parent[a]=b;
		odd_cnt-=(sz[a]&1)+(sz[b]&1);
		sz[b]+=sz[a],sz[a]=0;
		odd_cnt+=(sz[b]&1);
		return true;
	}
}DJ;
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
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)S[i]=Node();
		EDGE.clear();
		for(int i=0,a,b,l;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&l),a--,b--;
			EDGE.push_back(Edge(a,b,l));
		}
		DJ.clear(N);
	}
	return 0;
}
