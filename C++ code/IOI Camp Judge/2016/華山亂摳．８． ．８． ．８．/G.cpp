#include<cstdio>
//#include<cassert>
#include<algorithm>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Node
{
	Node *ch[2];
	int sz;
	Node(const int v):ch{NULL,NULL},sz(-v){}
}*S[1000001];
int Sz(Node* &o){return o?(o->sz<=0?1:o->sz):0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+Sz(o->ch[1]);}
int N,A[100001];
Node *Modify(Node* &o,const int dep,const int v)
{
	if(!o)return new Node(v);
	Node *ans=new Node(0);
	if(o->sz<=0)
	{
		const int d=((-o->sz)>>dep)&1;
		ans->ch[d]=new Node(-(o->sz));
	}
	else ans->ch[0]=o->ch[0],ans->ch[1]=o->ch[1];
	const int d=(v>>dep)&1;
	ans->ch[d]=Modify(ans->ch[d],dep-1,v);
	Maintain(ans);
	return ans;
}
Node *Ch(Node *o,const int dep,const int d)
{
	if(!o)return NULL;
	if(o->sz<=0)
	{
		if(d==(((-o->sz)>>dep)&1))return o;
		else return NULL;
	}
	return o->ch[d];
}
bool Query(Node *lo,Node *ro,const int dep,const int x,int &ans)
{
	if(Sz(lo)==Sz(ro))return false;
	if(ro->sz<=0){ans=-(ro->sz);return true;}
	assert(Sz(lo)<Sz(ro));
	int d[2]={1,0};
	if((x>>dep)&1)swap(d[0],d[1]);
	for(int i=0;i<2;i++)if(Query(Ch(lo,dep,d[i]),Ch(ro,dep,d[i]),dep-1,x,ans))return true;
	assert(0);
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	for(int querycount;testcount--;)
	{
		scanf("%d%d",&N,&querycount);
		for(int i=1;i<=N;i++)scanf("%d",&A[i]);
		S[0]=NULL;
		for(int i=1;i<=N;i++)S[i]=Modify(S[i-1],30,A[i]),assert(Sz(S[i])==i);
		for(int l,r,x;querycount--;)
		{
			scanf("%d%d%d",&l,&r,&x);
			int ans=-1;
			assert(Query(S[l-1],S[r],30,x,ans));
			assert(ans!=-1);
			printf("%d\n",x^ans);
		}
	}
	return 0;
}
