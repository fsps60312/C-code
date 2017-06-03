#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef long long LL;
struct Node
{
	Node *parent;
	map<char,Node*>trans;
	int max_len;
	LL sz;
	bool Contains(const char c){return trans.find(c)!=trans.end();}
}*ROOT,*LAST,BUFFER[180001],*NEW;
Node *NewNode(const int _max_len)
{
	NEW->parent=NULL;
	NEW->max_len=_max_len;
	NEW->sz=-1LL;
	NEW->trans.clear();
	return NEW++;
}
void Expand(const char c)
{
	Node *cur=LAST;LAST=NewNode((LAST->max_len)+1);
	for(;cur&&!cur->Contains(c);cur=cur->parent)cur->trans[c]=LAST;
	if(!cur)LAST->parent=ROOT;
	else
	{
		Node *q=cur->trans[c];
		if((cur->max_len)+1==(q->max_len))LAST->parent=q;
		else
		{
			Node *new_q=NewNode((cur->max_len)+1);
			new_q->trans=q->trans;
			new_q->parent=q->parent;
			q->parent=new_q;
			LAST->parent=new_q;
			for(;cur&&cur->trans[c]==q;cur=cur->parent)cur->trans[c]=new_q;
		}
	}
}
LL GetSz(Node *o)
{
	if(o->sz!=-1LL)return o->sz;
	o->sz=1LL;
	for(const auto &it:o->trans)o->sz+=GetSz(it.second);
	return o->sz;
}
void PrintAns(Node *o,const LL &k)
{
	if(k==1LL)return;
	LL sz=1LL;
	for(const auto &it:o->trans)
	{
		if(sz+(it.second->sz)>=k)
		{
			putchar(it.first);
			PrintAns(it.second,k-sz);
			return;
		}
		sz+=it.second->sz;
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	NEW=BUFFER;
	int c=getchar();
	while(c<'a'||c>'z')c=getchar();
	ROOT=LAST=NewNode(0);
	for(;c>='a'&&c<='z';c=getchar())Expand(c);
	GetSz(ROOT);
	int querycount;scanf("%d",&querycount);
	for(LL k;querycount--;)
	{
		scanf("%lld",&k);
		PrintAns(ROOT,k+1LL);puts("");
	}
	return 0;
}
