#define SELF
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
void inicjuj(int &n,int &a,int &b){n=5,a=GRADER_A,b=GRADER_B;BYTEEN_PAID=0;}
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
struct Node
{
	Node *lch,*rch;
	int sz;
	Node():lch(NULL),rch(NULL),sz(0){}
};
struct NodePointerComparer{bool operator()(Node *a,Node *b)const{return a->cost<b->cost;}};
int N,A,B;
int main()
{
	inicjuj(N,A,B);
	Node *root=Node();
	root->sz=1;
	map<int,Node*>pq;
	pq.insert(root);
	area=1;
	while(area<N)
	{
		Node *o=*pq.begin();pq.erase(pq.begin());
		const int lcost=o->cost+A;
		if(pq.find(lcost)!=pq.end())o->lch=pq[lcost];
		else pq[lcost]=o->lch=new Node();
		const int rcost=o->cost+B;
		if(pq.find(rcost)!=pq.end())o->rch=pq[rcost];
		else pq[rcost]=o->rch=new Node();
	}
	return 0;
}
