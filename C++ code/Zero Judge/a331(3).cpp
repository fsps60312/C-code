#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
unsigned int Random()
{
	static unsigned int seed=20151209;
	seed*=0xdefaced;
	seed+=152134;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2];
	int v,sz;
	unsigned int pri;
	Node(const int _v):ch{NULL,NULL},v(_v),sz(1),pri(Random()){}
};
int Sz(Node* &o){return o?o->sz:0;}
Node *Pull(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);return o;}
Node *Copy(Node* &o)
{
	Node *ans=new Node(o->v);
	ans->ch[0]=o->ch[0],ans->ch[1]=o->ch[1];
	ans->v=o->v,ans->sz=o->sz;
	ans->pri=o->pri;
}
//void Check(Node* &o)
//{
//	if(!o)return;
//	assert(o->sz==Sz(o->ch[0])+1+Sz(o->ch[1]));
//	Check(o->ch[0]),Check(o->ch[1]);
//}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
	{
		Node *ans=Copy(a);
		ans->ch[1]=Merge(ans->ch[1],b);
		return Pull(ans);
	}
	else
	{
		Node *ans=Copy(b);
		ans->ch[0]=Merge(a,ans->ch[0]);
		return Pull(ans);
	}
}
void Split(Node *o,Node* &a,Node* &b,const int v)
{
	if(!o){a=b=NULL;return;}
	if(v<o->v)
	{
		b=Copy(o);
		Split(o->ch[0],a,b->ch[0],v);
		Pull(b);
	}
	else
	{
		a=Copy(o);
		Split(o->ch[1],a->ch[1],b,v);
		Pull(a);
	}
}
void QueryRank(Node* &o,const int v,int &ans)
{
	if(!o)return;
	if(v<=o->v)QueryRank(o->ch[0],v,ans);
	else ans+=Sz(o->ch[0])+1,QueryRank(o->ch[1],v,ans);
}
//void Print(Node* &o)
//{
//	if(!o)return;
//	Print(o->ch[0]);
//	printf(" %d",o->v);
//	Print(o->ch[1]);
//}
int N,M;
Node *ST[100001];
vector<int>VALUE;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		ST[0]=NULL;
		VALUE.clear();
		for(int i=1,v;i<=N;i++)
		{
			scanf("%d",&v);
			VALUE.push_back(v);
			Node *a,*b;
			Split(ST[i-1],a,b,v);
			ST[i]=Merge(a,Merge(new Node(v),b));
		}
	//	for(int i=0;i<N;i++)printf(" %d",VALUE[i]);puts("");
	//	for(int i=0;i<=N;i++)Print(ST[i]),Check(ST[i]),puts("");
		sort(VALUE.begin(),VALUE.end());
		VALUE.resize(unique(VALUE.begin(),VALUE.end())-VALUE.begin());
		while(M--)
		{
			static int i,j,k;scanf("%d%d%d",&i,&j,&k);
			int l=0,r=VALUE.size();
			while(l<r)
			{
				const int mid=(l+r)/2;
				int r1=1,r2=1;
				QueryRank(ST[i-1],VALUE[mid],r1);
	//			printf("version %d, value %d, rank %d\n",)
				QueryRank(ST[j],VALUE[mid],r2);
				const int rank=1+r2-r1;
	//			printf("value=%d,in (%d,%d) rank(%d,%d)=%d\n",VALUE[mid],i,j,r1,r2,rank);
				if(rank<=k)l=mid+1;
				else r=mid;
			}
			printf("%d\n",VALUE[r-1]);
		}
	}
	return 0;
}
