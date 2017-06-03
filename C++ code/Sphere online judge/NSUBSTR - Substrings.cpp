#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Node
{
	Node *parent,*ch[26];
	int max_len;
}*ROOT,*LAST,BUFFER[1+250000*2],*NEW;
Node *NewNode(const int _max_len)
{
	NEW->parent=NULL;
	NEW->max_len=_max_len;
	for(int i=0;i<26;i++)NEW->ch[i]=NULL;
	return NEW++;
}
void Extend(const int c)
{
	Node *cur=LAST;LAST=NewNode((LAST->max_len)+1);
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
//void Print(Node *o,string ans)
//{
//	puts(ans.c_str());
//	for(int i=0;i<26;i++)if(o->ch[i])
//	{
//		ans.push_back('a'+i);
//		Print(o->ch[i],ans);
//		ans.pop_back();
//	}
//}
int N,ANS[250001];
char S[250001];
vector<pair<int,int> >SEGS[250001];
vector<int>ET[500001];
int SZ[500001];
int GetSZ(const int u)
{
	int &ans=SZ[u]=1;
	for(const int nxt:ET[u])ans+=GetSZ(nxt);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	NEW=BUFFER;
	scanf("%s",S);
	ROOT=LAST=NewNode(0);
	for(N=0;S[N];N++)Extend(S[N]-'a');
//	Print(ROOT,"");
	for(int i=1;i<=N;i++)ANS[i]=0;
	for(Node *cur=BUFFER;cur!=NEW;cur++)if(cur->parent)ET[cur->parent-BUFFER].push_back(cur-BUFFER);
	for(Node *cur=BUFFER;cur!=NEW;cur++)
	{
		const int min_len=(cur->parent?cur->parent->max_len+1:0);
		SEGS[min_len].push_back(make_pair(cur->max_len,GetSZ(cur-BUFFER)));
	}
	
	for(int i=1;i<=N;i++)printf("%d\n",ANS[i]);
	return 0;
}
