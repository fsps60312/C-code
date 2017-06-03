#include<cstdio>
struct Node
{
	Node *ch[2];
	int sz,v;
	Node(const int _v):v(_v),sz(1),ch{NULL,NULL}{}
};
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Node* &o,const int cu)
{
	Node *u=o->ch[cu];
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])-Sz(o->ch[1])>1)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>1)Rotate(o,1);
}
void Insert(Node* &o,const int v)
{
	if(!o){o=new Node(v);return;}
	Insert(o->ch[v<o->v?0:1],v);
	Maintain(o);
	Rotate(o);
}
Node *ST[400000];
int S[100000];
void Build(const int id,const int l,const int r)
{
	ST[id]=NULL;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
int N,M;
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
	}
	return 0;
}
