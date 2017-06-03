#include "lib1692.h"
#include<cstdio>
#include<cassert> 
#include<vector>
#include<set>
#include<stack>
using namespace std;
//void Init(){}
//void GetVE(int &V,int &E){V=5,E=4;}
//void Get(int &a,int &b)
//{
//	static int tick=0;
//	static int as[4]={1,1,3,1},bs[4]={2,2,5,4};
//	a=as[tick],b=bs[tick];
//	tick++;
//}
///////////////////////////////////////////////////////////////
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
set<int>ET[1000];
void DeleteEdge(const int ei)
{
	const Edge &e=EDGE[ei];
	ET[e.a].erase(ei);
	ET[e.b].erase(ei);
}
int N,M;
struct Node
{
	const int val;
	Node *next;
	Node(const int _val):val(_val),next(NULL){}
};
Node *IN_PATH[1000],*OUT_PATH[1000];
void Dfs(Node *o,const int u)
{
	if(!ET[u].empty())
	{
		const int ei=*ET[u].begin();
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		o->next=new Node(ei);
		DeleteEdge(ei);
		Dfs(o->next,nxt);
	}
	IN_PATH[u]=o,OUT_PATH[u]=o->next;
}
int main()
{
	Init();
	GetVE(N,M);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,a,b;i<M;i++)
	{
		Get(a,b),a--,b--;
		EDGE.push_back(Edge(a,b));
		ET[a].insert(i),ET[b].insert(i);
	}
	for(int i=0;i<N;i++)IN_PATH[i]=OUT_PATH[i]=NULL;
	vector<Node*>paths;
	for(int i=0;i<N;i++)if((int)ET[i].size()&1)
	{
		Node *start=new Node(i);
		Dfs(start,i);
		paths.push_back(start);
	}
	for(int i=0;i<N;i++)if(!ET[i].empty())
	{
		Node *in_path=IN_PATH[i],*out_path=OUT_PATH[i];
		Node *start=new Node(i);
		Dfs(start,i);
		assert(ET[i].empty());
		if(in_path==NULL)
		{
			paths.push_back(start);
		}
		else
		{
			in_path->next=start->next;
			Node *cur=start->next;
			delete start;
			while(cur->next)cur=cur->next;
			cur->next=out_path;
		}
	}
	for(Node *start:paths)
	{
		Node *cur=start->next;
		int u=start->val;
//		printf("start from %d\n",u+1);
		ReportVst(u+1);
		for(;cur;cur=cur->next)
		{
//			printf(" %d",cur->val+1);
			ReportE(cur->val+1);
			const Edge &e=EDGE[cur->val];
			assert((u==e.a)!=(u==e.b));
			u=(u==e.a?e.b:e.a);
		}
//		printf("\nend at %d\n",u+1);
		ReportVed(u+1);
	}
	Final();
	return 0;
}
