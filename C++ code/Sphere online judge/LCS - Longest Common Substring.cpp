#include<cstdio>
#include<cassert>
using namespace std;
struct Node
{
	Node *green,*edge[26];
	const int max_len;
	Node(const int _max_len):green(NULL),max_len(_max_len){for(int i=0;i<26;i++)edge[i]=NULL;}
}*ROOT,*LAST;
void Extend(const int c)
{
	Node *cur=LAST;LAST=new Node(cur->max_len+1);
	for(;cur&&cur->edge[c]==NULL;cur=cur->green)cur->edge[c]=LAST;
	if(!cur)LAST->green=ROOT;
	else
	{
		Node *pgreen=cur->edge[c];
		if(pgreen->max_len==cur->max_len+1)LAST->green=pgreen;
		else
		{
			Node *wish=new Node(cur->max_len+1);
			for(;cur&&cur->edge[c]==pgreen;cur=cur->green)cur->edge[c]=wish;
			for(int i=0;i<26;i++)wish->edge[i]=pgreen->edge[i];
			wish->green=pgreen->green;
			pgreen->green=wish;
			LAST->green=wish;
		}
	}
}
char A[250001],B[250001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s%s",A,B);
	ROOT=LAST=new Node(0);
	for(int i=0;A[i];i++)Extend(A[i]-'a');
	int ans=0;
	Node *cur=ROOT;
	for(int i=0,len=0;B[i];i++)
	{
		while(cur!=ROOT&&cur->edge[B[i]-'a']==NULL)cur=cur->green,len=cur->max_len;
		if(cur->edge[B[i]-'a'])cur=cur->edge[B[i]-'a'],len++;
		if(len>ans)ans=len;
	}
	printf("%d\n",ans);
	return 0;
}
