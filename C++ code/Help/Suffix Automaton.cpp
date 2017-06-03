#include<cstdio>
#include<cassert>
#include<string>
using namespace std;
struct Node
{
	Node *parent,*ch[26];
	int max_len;//
}
void Dfs(Node *o,string &now)
{
	assert(o);
	printf("%s\n",now.c_str());
	for(int i=0;i<26;i++)if(o->trans[i])
	{
		now.push_back('a'+i);
		Dfs(o->trans[i],now);
		now.pop_back();
	}
}
void Build(string s)
{
	ROOT=LAST=new Node(0);
	for(int i=0;i<(int)s.size();i++)
	{
		assert('a'<=s[i]&&s[i]<='z');
		Extend(s[i]-'a');
	}
	string now="";
	Dfs(ROOT,now);
	puts("finished.");
}
int main()
{
	Build("abcde");
	Build("aabaaaab");
	return 0;
}
/*struct Node
{
	Node *parent,*trans[26];
	const int max_len;
	Node(const int _max_len):parent(NULL),max_len(_max_len){for(int i=0;i<26;i++)trans[i]=NULL;}
}*ROOT,*LAST;
void Extend(const int c)
{
	Node *cur=LAST;
	LAST=new Node(LAST->max_len+1);//size of string
	for(;cur&&!cur->trans[c];cur=cur->parent)cur->trans[c]=LAST;
	if(!cur)LAST->parent=ROOT;
	else
	{
		Node *q=cur->trans[c];
		if((cur->max_len)+1==q->max_len)LAST->parent=q;
		else
		{
			Node *new_q=new Node(cur->max_len+1);
			for(int i=0;i<26;i++)new_q->trans[i]=q->trans[i];
			new_q->parent=q->parent;
			q->parent=new_q;//add only {N+1}
			LAST->parent=new_q;
			for(;cur&&cur->trans[c]==q;cur=cur->parent)cur->trans[c]=new_q;
		}
	}
}*/
