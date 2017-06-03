#include"interactive/120.h"
#include<cstdio>
#include<algorithm>
using namespace std;
int N,A,B,C;
struct Node
{
	Node *l,*r;
	int v;
	Node(){}
	Node(const int _v):,v(_v),l(NULL),r(NULL){}
}*ROOT=NULL;
vector<int>NOW;
int CNT;
void Build(Node* &o,int id)
{
	if(id*2+1<=N)
	{
		while(NOW.size()<3)NOW.push_back(CNT++);
		int v=Mid3(NOW[0],NOW[1],NOW[2]);
		for(int i=0;i<3;i++)if(v==NOW[i])
		{
			o=new Node(NOW[i]);
			swap(NOW[i],NOW[2]);
			NOW.pop_back();
			break;
		}
		Build(o->l,id*2),Build(o->r,id*2+1);
	}
	else if(id*2<=N)
	{
		while(NOW.size()<2)NOW.push_back(CNT++);
		int sz=NOW.size()-1;
		o=new Node(NOW[sz--]),NOW.pop_back();
		o->l=new Node(NOW[sz--]),NOW.pop_back();
	}
	else
	{
		if(NOW.empty())NOW.push_back(CNT++);
		int sz=NOW.size()-1;
		o=new Node(NOW[sz--]),NOW.pop_back();
	}
}
int main()
{
	N=GetN();
	NOW.clear();
	CNT=1;
	Build(1);
	return 0;
}
