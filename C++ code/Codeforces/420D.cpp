#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
unsigned int Rand()
{
	static unsigned int seed=20160220;
	seed*=0xdefaced,seed+=121546;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2];
	const int val;
	unsigned int sz;
	Node(const int _val):ch{NULL,NULL},val(_val),sz(1){}
}*ROOT;
unsigned int Sz(Node *o){return o?o->sz:0;}
void Maintain(Node *o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(Rand()%(a->sz+b->sz)<(a->sz))
	{
		a->ch[1]=Merge(a->ch[1],b);
		Maintain(a);
		return a;
	}
	else
	{
		b->ch[0]=Merge(a,b->ch[0]);
		Maintain(b);
		return b;
	}
}
void Split(Node *o,Node* &a,Node* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=(int)Sz(o->ch[0]))
	{
		b=o;
		Split(b->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(a->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		Maintain(a);
	}
}
void Extract(Node *o,vector<int>&output)
{
	if(!o)return;
	Extract(o->ch[0],output);
	output.push_back(o->val);
	Extract(o->ch[1],output);
}
int N,M;
bool Solve(const vector<pair<int,int> >&operations)
{
	static bool vis[1000001];
	for(int i=1;i<=N;i++)vis[i]=false;
	for(int i=M-1;i>=0;i--)
	{
		const pair<int,int>&p=operations[i];
		Node *begin;
		Split(ROOT,begin,ROOT,1);
		if((begin->val)!=0&&(begin->val)!=p.first)return false;
		if((begin->val)==0&&vis[p.first])return false;
		Node *a,*b;
		Split(ROOT,a,b,p.second-1);
		ROOT=Merge(a,Merge(new Node(p.first),b));
		vis[p.first]=true;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		ROOT=NULL;
		for(int i=0;i<N;i++)ROOT=Merge(ROOT,new Node(0));
		vector<pair<int,int> >operations;
		for(int i=0,x,y;i<M;i++)scanf("%d%d",&x,&y),operations.push_back(make_pair(x,y));
		if(!Solve(operations))puts("-1");
		else
		{
			vector<int>ans;
			Extract(ROOT,ans);
			static int vis[1000001];
			for(int i=1;i<=N;i++)vis[i]=false;
			for(const int v:ans)vis[v]=true;
			vector<int>remain;
			for(int i=1;i<=N;i++)if(!vis[i])remain.push_back(i);
			for(int i=0,j=0;i<N;i++)if(ans[i]==0)assert(j<(int)remain.size()),ans[i]=remain[j++];
			for(int i=0;i<N;i++)
			{
				if(i)putchar(' ');
				printf("%d",ans[i]);
			}
			puts("");
		}
	}
	return 0;
}
