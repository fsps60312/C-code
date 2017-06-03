#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct Node
{
	Node *ch[2];
	int tag;
	Node():ch{NULL,NULL},tag(0){}
	Node(Node *o):ch{o->ch[0],o->ch[1]},tag(o->tag){}
	void PutDown(const int depth)
	{
		if(!tag)return;
		for(int d=0;d<2;d++)if(ch[d])
		{
			ch[d]=new Node(ch[d]);
			ch[d]->tag^=tag;
		}
		if(tag&(1<<depth))swap(ch[0],ch[1]);
		tag=0;
	}
};
void Insert(Node* &o,const int )
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&K);
	Node *root=NULL;
	for(int i=0,v;i<N;i++)
	{
		scanf("%d",&v);
		
	}
	return 0;
}
