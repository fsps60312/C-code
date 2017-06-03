#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
int N,ROOT;
LL M,C[100000],L[100000];
vector<int>ET[100000];
LL ANS;
struct Node
{
	Node *ch[2];
	int sz;
	LL v,sum;
	Node(){}
	Node(const LL _v):v(_v),sum(_v),sz(1),ch{NULL,NULL}{}
};
int Sz(Node* &o){return o?o->sz:0;}
LL Sum(Node* &o){return o?o->sum:0LL;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+o->v+Sum(o->ch[1]);
}
void Rotate(Node* &o,const int cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])-Sz(o->ch[1])>2)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>2)Rotate(o,1);
}
void Insert(Node* &o,const LL v)
{
	if(!o){o=new Node(v);return;}
	Insert(o->ch[v<o->v?0:1],v);
	Maintain(o);
	Rotate(o);
}
void Merge(Node* &o,Node* &b)
{
	if(!b)return;
	Merge(o,b->ch[0]),Merge(o,b->ch[1]);
	Insert(o,b->v);
	delete b;b=NULL;
}
void Query(Node* &o,int &ans,LL &budget)
{
	if(!o)return;
	if(budget<Sum(o->ch[0])){Query(o->ch[0],ans,budget);return;}
	budget-=Sum(o->ch[0]),ans+=Sz(o->ch[0]);
	if(budget<o->v){return;}
	budget-=o->v,ans++;
	Query(o->ch[1],ans,budget);
}
Node *Dfs(const int u)
{
	Node *o=new Node(C[u]);
	for(int i=0;i<ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		Node *tmp=Dfs(nxt);
		if(Sz(tmp)>Sz(o))swap(tmp,o);
		Merge(o,tmp);
	}
//	printf("u=%d,sz=%d\n",u,Sz(o));
	int cnt=0;
	LL budget=M;
	Query(o,cnt,budget);
//	printf("cnt=%d\n",cnt);
	ANS=max(ANS,L[u]*(LL)cnt);
	return o;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%lld",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	ROOT=-1;
	for(int i=0,v;i<N;i++)
	{
		scanf("%d%lld%lld",&v,&C[i],&L[i]);
		if(v==0)assert(ROOT==-1),ROOT=i;
		else ET[--v].push_back(i);
	}
	assert(ROOT!=-1);
	ANS=0;
	Dfs(ROOT);
	printf("%lld\n",ANS);
	return 0;
}
