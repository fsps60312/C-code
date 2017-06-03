#include<cstdio>
#include<cassert>
#include<string>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Node
{
	Node *green,*edge[26];
	const int max_len;
	int vis,dp;
	Node(const int _max_len):green(NULL),max_len(_max_len),vis(0),dp(-1){for(int i=0;i<26;i++)edge[i]=NULL;}
}*ROOT,*LAST;
void Extend(const int c)
{
	Node *cur=LAST;LAST=new Node(LAST->max_len+1);
	for(;cur&&!cur->edge[c];cur=cur->green)cur->edge[c]=LAST;
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
int N;
int Dfs(Node *o)
{
	int &ans=o->dp;
	if(ans!=-1)return ans;
	
}
int main()
{
	freopen("in.txt","r",stdin);
	static char str[100001];
	scanf("%s",str);
	ROOT=LAST=new Node(0);
	for(int i=0;str[i];i++)Extend(str[i]-'a');
	for(N=1;scanf("%s",str)==1;N++)
	{
		Node *cur=ROOT;
		for(int i=0;str[i];i++)
		{
			const int c=str[i]-'a';
			for(;cur!=ROOT&&(!cur->edge[c]||cur->edge[c]->vis<N-1);cur=cur->green);
			if(cur->edge[c]&&cur->edge[c]->vis>=N-1)cur=cur->edge[c],cur->vis=N;
		}
	}
	printf("%d\n",Dfs(ROOT));
	return 0;
}
