#include"interactive/119.h"
#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
//int CCC=0,AAA=1000000000;
//void Init(int *n,int *a,int *b){*n=1000000000,*a=1,*b=10000;}
//int Ask(char c,int x)
//{
//	assert(c=='W');
//	int a=(AAA>x?1:0);
//	if(a)CCC+=1;
//	else CCC+=2;
//	return a;
//}
//void Answer(int x){printf("x=%d,cost=%d\n",x,CCC);}
struct Node
{
	Node *ch[2];
	int cost,sz;
	Node(const int _cost):ch{NULL,NULL},cost(_cost),sz(-1){}
};
struct CmpNodePointer{bool operator()(Node *a,Node *b)const{return a->cost<b->cost;};};
map<Node*,int,CmpNodePointer>NODE;
int N,A,B,PROG;
void Insert(Node* &o,const int val)
{
	auto it=NODE.find(o);
	if(it==NODE.end())NODE[o]=val;
	else o=it->first,it->second+=val;
	PROG+=val;
}
void Build(Node* &o)
{
	if(o->sz!=-1)return;
	assert((o->ch[0]==NULL)==(o->ch[1]==NULL));
	if(o->ch[0]==NULL){o->sz=1;return;}
	Build(o->ch[0]),Build(o->ch[1]);
	o->sz=o->ch[0]->sz+o->ch[1]->sz;
}
void Solve(Node* &o,const int l,const int r)
{
//	printf("(%d,%d)\n",l,r);
	if(l==r)Answer(l),assert(0&&"ended");
	assert(o->ch[0]);
	const int result=Ask('W',l+o->ch[0]->sz-1);
	if(result==1)Solve(o->ch[1],l+(o->ch[0]->sz),r);
	else assert(result==0),Solve(o->ch[0],l,r-(o->ch[1]->sz));
}
//void Print(Node* &o,int dep=0)
//{
//	if(!o)return;
//	for(int i=0;i<dep;i++)printf("  ");
//	printf("%d\n",o->cost);
//	Print(o->ch[0],dep+1);
//	Print(o->ch[1],dep+1);
//}
int main()
{
	Init(&N,&A,&B);
	if(N==1)Answer(1);
	PROG=0;
	NODE.clear();
	Node *root=new Node(0);
	Insert(root,1);
	while(PROG<N)
	{
		const auto it=NODE.begin();
		Node *o=it->first;
		const int val=it->second;
		NODE.erase(it);
		PROG-=val;
		Insert(o->ch[0]=new Node(o->cost+B),val);
		Insert(o->ch[1]=new Node(o->cost+A),val);
	}
//	Print(root);
	Build(root);
//	printf("(%d,%d)\n",root->sz,PROG);
	assert(root->sz==PROG);
	Solve(root,1,PROG);
	return 0;
}
