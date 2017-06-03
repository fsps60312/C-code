#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Node
{
	Node *parent,*ch[26];
	int max_len,dep;
}*ROOT,*LAST,BUFFER[1+250000*2],*NEW;
int DP[1+250000*2];
Node *NewNode(const int _max_len)
{
	NEW->parent=NULL;
	NEW->max_len=_max_len;
	NEW->dep=-1;
	for(int i=0;i<26;i++)NEW->ch[i]=NULL;
	DP[NEW-BUFFER]=0;
	return NEW++;
}
void Extend(const int c)
{
	Node *cur=LAST;LAST=NewNode((LAST->max_len)+1);
	DP[LAST-BUFFER]++;
	for(;cur&&!cur->ch[c];cur=cur->parent)cur->ch[c]=LAST;
	if(!cur)LAST->parent=ROOT;
	else
	{
		Node *q=cur->ch[c];
		if(q->max_len==cur->max_len+1)LAST->parent=q;
		else
		{
			Node *new_q=NewNode(cur->max_len+1);
			for(int i=0;i<26;i++)new_q->ch[i]=q->ch[i];
			new_q->parent=q->parent;
			q->parent=new_q;
			LAST->parent=new_q;
			for(;cur&&cur->ch[c]==q;cur=cur->parent)cur->ch[c]=new_q;
		}
	}
}
int N,ANS[250001];
char S[250001];
vector<int>ET[250001];
int main()
{
//	freopen("in.txt","r",stdin);
	NEW=BUFFER;
	scanf("%s",S);
	ROOT=LAST=NewNode(0);
	for(N=0;S[N];N++)Extend(S[N]-'a');
	for(int i=1;i<=N;i++)ANS[i]=0;
	for(Node *cur=BUFFER;cur!=NEW;cur++)ET[cur->max_len].push_back(cur-BUFFER);
	for(int len=N;len>=1;len--)
	{
		for(const int i:ET[len])
		{
			DP[BUFFER[i].parent-BUFFER]+=DP[i];
			getmax(ANS[len],DP[i]);
		}
	}
	for(int i=N-1;i>=1;i--)getmax(ANS[i],ANS[i+1]);
	for(int i=1;i<=N;i++)printf("%d\n",ANS[i]);
	return 0;
}

