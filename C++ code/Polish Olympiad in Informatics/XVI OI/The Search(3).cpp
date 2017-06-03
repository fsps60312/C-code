//#define SELF
#ifndef SELF
#include "poslib.h"
#endif
#include<cstdio>
#include<cassert>
#include<queue>
#include<utility>
using namespace std;
#ifdef SELF
int BYTEEN_PAID,GRADER_A=1,GRADER_B=2,GRADER_ANSWER=3;
void inicjuj(int *n,int *a,int *b){*n=5,*a=GRADER_A,*b=GRADER_B;BYTEEN_PAID=0;}
int pytaj(char c,int f)
{
	if(c=='W')return GRADER_ANSWER>f;
	else if(c=='N')return GRADER_ANSWER<f;
	else assert(0);
	return -1;
}
void odpowiedz(int f)
{
	printf("your answer: %d\n",f);
	puts(f==GRADER_ANSWER?"AC":"WA");
}
#endif
typedef long long LL;
struct Node
{
	Node *lch,*rch;
	const LL sz;
	Node(const LL _sz):lch(NULL),rch(NULL),sz(_sz){}
};
int N,A,B;
void Dfs(Node *o,const LL l,const LL r)
{
	assert(o->sz>=r-l+1);
	if(l==r){odpowiedz(r);assert(0);return;}
	const LL mid=l+o->lch->sz;
	assert(mid>l&&mid<=r);
	if(pytaj('N',mid))Dfs(o->lch,l,mid-1);
	else Dfs(o->rch,mid,r);
}
Node *S[2000000];
Node *GetNode()
{
	for(int cost=0;;cost++)
	{
		assert(cost<2000000);
		if(cost>=max(A,B))
		{
			S[cost]=new Node(S[cost-A]->sz+S[cost-B]->sz);
			S[cost]->lch=S[cost-A];
			S[cost]->rch=S[cost-B];
		}
		else S[cost]=new Node(1);
		if(S[cost]->sz>=N)return S[cost];
	}
}
int main()
{
	inicjuj(&N,&A,&B);
	Node *root=GetNode();
	Dfs(root,1,N);
	return 0;
}
