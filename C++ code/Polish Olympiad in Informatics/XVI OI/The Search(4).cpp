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
int BYTEEN_PAID,GRADER_A=1,GRADER_B=1,GRADER_ANSWER=500000000;
void inicjuj(int *n,int *a,int *b){*n=1000000000,*a=GRADER_A,*b=GRADER_B;BYTEEN_PAID=0;}
int pytaj(char c,int f)
{
	bool ans;
	if(c=='W')ans=(GRADER_ANSWER>f);
	else if(c=='N')ans=(GRADER_ANSWER<f);
	else assert(0);
	BYTEEN_PAID+=(ans?GRADER_A:GRADER_B);
	return ans;
}
void odpowiedz(int f)
{
	printf("your answer: %d\ncosts %d\n",f,BYTEEN_PAID);
	puts(f==GRADER_ANSWER?"AC":"WA");
	exit(0);
}
#endif
typedef long long LL;
struct Node
{
	Node *lch,*rch;
	const LL sz;
	Node(const LL _sz):lch(NULL),rch(NULL),sz(_sz){}
};
int N,M,A,B;
Node *S[2000000];
void Dfs(const LL lb,const LL rb)
{
	if(lb==rb){odpowiedz(rb);assert(0);return;}
	int l=0,r=M;
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(S[mid]->sz>=rb-lb+1)r=mid;
		else l=mid+1;
	}
	Node *o=S[r];
	if(pytaj('N',lb+o->lch->sz))Dfs(lb,lb+o->lch->sz-1);
	else Dfs(lb+o->lch->sz,rb);
}
void GetNode()
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
		if(S[cost]->sz>=N){M=cost;return;}
	}
}
int main()
{
	inicjuj(&N,&A,&B);
	GetNode();
	Dfs(1,N);
	return 0;
}
