#include<cstdio>
#include<queue>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1);}
using namespace std;
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b,int c){return max(max(a,b),c);}
int min(int a,int b,int c){return min(min(a,b),c);}
struct Node
{
	Node *ch[2];
	int sz,height,minq,idx;
	queue<int> q;
	int GetQ(){if(q.empty())return 2147483647;return q.front();}
	Node(){}
	Node(int idx):idx(idx),sz(1),height(1),minq(2147483647),q(queue<int>()){ch[0]=ch[1]=NULL;}
}*ROOT,NODE[100001];
int Sz(Node* &v){return v?v->sz:0;}
int Height(Node* &v){return v?v->height:0;}
int Minq(Node* &v){return v?v->minq:2147483647;}
int Idx(Node* &v){return v?v->idx:-1;}
void show(Node* o)
{
	if(!o)return;
	show(o->ch[0]);
	printf("{%d:(%d,%d)(%d,%d,%d)",Idx(o),Idx(o->ch[0]),Idx(o->ch[1]),Sz(o),Height(o),o->GetQ());
	queue<int>q=o->q;
	while(!q.empty())
	{
		printf(",%d",q.front());
		q.pop();
	}
	printf("}");
	show(o->ch[1]);
}
void Maintain(Node* &n)
{
	n->sz=Sz(n->ch[0])+1+Sz(n->ch[1]);
	n->height=max(Height(n->ch[0]),Height(n->ch[1]))+1;
	n->minq=min(n->GetQ(),Minq(n->ch[0]),Minq(n->ch[1]));
}
void Rotate(Node* &o,int chup)
{
	Node *ro=o;
	if(!o)termin("Rotate:!o\n");
	if(!o->ch[chup])termin("Rotate:!o->ch[chup]\n");
	o=o->ch[chup];
	ro->ch[chup]=o->ch[chup^1];
	o->ch[chup^1]=ro;
	Maintain(ro);
	Maintain(o);
}
void Rotate(Node* &n)
{
	Maintain(n);
	int h1=Height(n->ch[0]),h2=Height(n->ch[1]);
	if(h1-h2>=2)Rotate(n,0);
	else if(h2-h1>=2)Rotate(n,1);
}
void Push(Node* &o,Node *v,int d)
{
	if(!o)
	{
		o=v;
		Maintain(o);
		return;
	}
	Push(o->ch[d],v,d);
	Rotate(o);
}
void Remove(Node* &o)
{
	if(!o->ch[0]||!o->ch[1])
	{
		if(o->ch[0])o=o->ch[0];
		else o=o->ch[1];
		return;
	}
	int chup=Height(o->ch[0])>Height(o->ch[1])?0:1;
	Rotate(o,chup);
	Remove(o->ch[chup^1]);
	Rotate(o);
}
int QueryRemove(Node* &o,int ans,Node* &removed)
{
	int a=o->GetQ(),b=Minq(o->ch[0]),c=Minq(o->ch[1]);
	int v=min(a,b,c);
	if(v==2147483647)
	{
		show(o);
		termin("o=%d,v==%d\n",o!=0,v);
	}
	if(v==b||v==c)
	{
		ans=QueryRemove(o->ch[v==b?0:1],ans+(v==b?0:Sz(o->ch[0])+1),removed);
		Rotate(o);
		return ans;
	}
	ans+=Sz(o->ch[0]);
	removed=o;
	Remove(o);
	return ans;
}
int T,N,M;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		ROOT=NULL;
		for(int i=0;i<N;i++)NODE[i]=Node(i);
		for(int v,i=0;i<M;i++)
		{
			scanf("%d",&v);
			NODE[--v].q.push(i);
		}
//		puts("a");
		for(int i=0;i<N;i++)
		{
			Push(ROOT,&NODE[i],1);
		}
		Node *rem;
		for(int i=0;i<M;i++)
		{
			if(i)printf(" ");
			printf("%d",QueryRemove(ROOT,0,rem));
			queue<int>&q=rem->q;
			if(q.empty())termin("q.empty()\n"); 
			q.pop();
			rem->ch[0]=rem->ch[1]=NULL;
//			puts("bef");show(ROOT);puts("");
			Push(ROOT,rem,0);
//			puts("aft");show(ROOT);puts("");
		}
		puts("");
	}
	return 0;
}
