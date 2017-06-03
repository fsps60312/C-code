#include<cstdio>
#include<cassert>
#include<string>
using namespace std;
typedef long long LL;
struct Node
{
	Node *parent,*trans[26];
	int max_len;
	LL sz;
	Node(const int _max_len):parent(NULL),max_len(_max_len),sz(-1LL){for(int i=0;i<26;i++)trans[i]=NULL;}
}*ROOT,*LAST;
void Expand(const int c)
{
	Node *cur=LAST;LAST=new Node((LAST->max_len)+1);
	for(;cur&&!cur->trans[c];cur=cur->parent)cur->trans[c]=LAST;
	if(!cur)LAST->parent=ROOT;
	else
	{
		Node *q=cur->trans[c];
		if((cur->max_len)+1==(q->max_len))LAST->parent=q;
		else
		{
			Node *new_q=new Node((cur->max_len)+1);
			for(int i=0;i<26;i++)new_q->trans[i]=q->trans[i];
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
	for(int i=0;i<26;i++)if(o->trans[i])o->sz+=GetSz(o->trans[i]);
	return o->sz;
}
void PrintAns(Node *o,const LL &k)
{
	if(k==1LL)return;
	LL sz=1LL;
	for(int i=0;i<26;i++)if(o->trans[i])
	{
		if(sz+(o->trans[i]->sz)>=k)
		{
			putchar('a'+i);
			PrintAns(o->trans[i],k-sz);
			return;
		}
		sz+=o->trans[i]->sz;
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int c=getchar();
	while(c<'a'||c>'z')c=getchar();
	ROOT=LAST=new Node(0);
	for(;c>='a'&&c<='z';c=getchar())Expand(c-'a');
	GetSz(ROOT);
	int querycount;scanf("%d",&querycount);
	for(LL k;querycount--;)
	{
		scanf("%lld",&k);
		PrintAns(ROOT,k+1LL);puts("");
	}
	return 0;
}
