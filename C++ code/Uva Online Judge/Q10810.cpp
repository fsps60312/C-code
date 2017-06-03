#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Node
{
	Node *ch[2];
	int v,sz;
	Node(int v):v(v),sz(1),ch{NULL,NULL}{}
}*ROOT;
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Node* &o,int cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[0])<Sz(o->ch[1]))Rotate(o,1);
}
void Insert(Node* &o,const int &v)
{
	if(!o){o=new Node(v);return;}
	Insert(o->ch[v<o->v?0:1],v);
	Maintain(o);
	Rotate(o);
}
LL Query(Node* &o,const int &v)
{
	if(!o)return 0;
	if(v<=o->v)return Query(o->ch[0],v)+1+Sz(o->ch[1]);
	else if(v>o->v)return Query(o->ch[1],v);
//	else return Query(o->ch[])
}
int N;
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		ROOT=NULL;
		LL ans=0LL;
		for(int i=0;i<N;i++)
		{
			static int v;
			scanf("%d",&v);
			ans+=Query(ROOT,v+1);
			Insert(ROOT,v);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
