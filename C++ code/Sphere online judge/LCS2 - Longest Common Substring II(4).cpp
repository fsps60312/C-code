#include<cstdio>
#include<cassert>
#include<string>
#include<queue>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Node
{
	Node *green,*edge[26];
	int max_len;
	int vis,degree;
	bool deleted;
	void SetGreen(Node *o)
	{
		if(green)green->degree--;
		(green=o)->degree++;
	}
}*ROOT,*LAST,BUFFER[200001],*NEW;
Node *NewNode(const int _max_len)
{
	NEW->green=NULL;
	NEW->max_len=_max_len;
	NEW->vis=0,NEW->degree=0;
	NEW->deleted=false;
	for(int i=0;i<26;i++)NEW->edge[i]=NULL;
	return NEW++;
}
queue<Node*>LEAF[2];
void Extend(const int c)
{
	Node *cur=LAST;LAST=NewNode(LAST->max_len+1);
	for(;cur&&!cur->edge[c];cur=cur->green)cur->edge[c]=LAST;
	if(!cur)LAST->SetGreen(ROOT);
	else
	{
		Node *pgreen=cur->edge[c];
		if(pgreen->max_len==cur->max_len+1)LAST->SetGreen(pgreen);
		else
		{
			Node *wish=NewNode(cur->max_len+1);
			for(;cur&&cur->edge[c]==pgreen;cur=cur->green)cur->edge[c]=wish;
			for(int i=0;i<26;i++)wish->edge[i]=pgreen->edge[i];
			wish->SetGreen(pgreen->green);
			pgreen->SetGreen(wish);
			LAST->SetGreen(wish);
		}
	}
}
char S[100001];
int main()
{
	freopen("in.txt","r",stdin);
	NEW=BUFFER;
	assert(scanf("%s",S)==1);
	ROOT=LAST=NewNode(0);
	for(int i=0;S[i];i++)Extend(S[i]-'a');
	assert(LEAF[0].empty()&&LEAF[1].empty());
	for(Node *cur=BUFFER;cur!=NEW;cur++)if(!cur->degree)LEAF[0].push(cur);
	int d=0;
	for(int n=1;scanf("%s",S)==1;n++,d^=1)
	{
		Node *cur=ROOT;cur->vis=n;
		for(int i=0;S[i];i++)
		{
			const int c=S[i]-'a';
			for(;cur!=ROOT&&(!cur->edge[c]||cur->edge[c]->deleted);cur=cur->green);
			if(cur->edge[c]&&!cur->edge[c]->deleted)cur=cur->edge[c],cur->vis=n;
		}
		while(!LEAF[d].empty())
		{
			Node *u=LEAF[d].front();LEAF[d].pop();
			assert(!u->degree&&!u->deleted);
			if(u->vis<n)
			{
				u->deleted=true;
				if(!--(u->green->degree))LEAF[d].push(u->green);
			}
			else LEAF[d^1].push(u);
		}
	}
	int ans=0;
	while(!LEAF[d].empty())
	{
		Node *u=LEAF[d].front();LEAF[d].pop();
		getmax(ans,u->max_len),u->deleted=true;
		if(u->green&&!--u->green->degree)LEAF[d].push(u->green);
	}
	printf("%d\n",ans);
	for(Node *cur=BUFFER;cur!=NEW;cur++)assert(cur->deleted);
	return 0;
}
