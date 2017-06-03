#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N;
struct Node
{
	Node *ch[2];
	int sum,mx;
	Node(const int &s):sum(s),mx(max(0,s)),ch{NULL,NULL}{}
}*ROOT=new Node(0);
void Maintain(Node* &o)
{
	if(o->ch[0]==NULL)return;
	o->sum=o->ch[0]->sum+o->ch[1]->sum;
	o->mx=max(o->ch[0]->mx,o->ch[0]->sum+o->ch[1]->mx);
}
void Modify(Node* &o,const int &l,const int &r,const int &x1,const int &x2,const int &h)
{
	if(r<x1||l>x2)return;
	if(x1<=l&&r<=x2){o=new Node(h*(r-l+1));return;}
	int mid=(l+r)/2;
	if(o->ch[0]==NULL)
	{
		assert(o->sum%(r-l+1)==0);
		int th=o->sum/(r-l+1);
		o->ch[0]=new Node(th*(mid-l+1));
		o->ch[1]=new Node(th*(r-mid));
	}
	Modify(o->ch[0],l,mid,x1,x2,h);
	Modify(o->ch[1],mid+1,r,x1,x2,h);
	Maintain(o);
}
int Query(Node* &o,const int &l,const int &r,const int &h)
{
//	printf("(%d,%d)%d,sum=%d,mx=%d\n",l,r,h,o->sum,o->mx);
	if(o->ch[0]==NULL)
	{
		assert(o->sum%(r-l+1)==0);
		int th=o->sum/(r-l+1);
		if(th<=0)return INF;
		return l-1+h/th;
	}
	int mid=(l+r)/2;
	if(h<(o->ch[0]->mx))return Query(o->ch[0],l,mid,h);
	else return Query(o->ch[1],mid+1,r,h-o->ch[0]->sum);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	static char type[2];
	while(scanf("%s",type)==1)
	{
		if(type[0]=='E')break;
		else if(type[0]=='I')
		{
			static int a,b,h;
			scanf("%d%d%d",&a,&b,&h);
			Modify(ROOT,1,N,a,b,h);
		}
		else if(type[0]=='Q')
		{
			static int h;scanf("%d",&h);
			printf("%d\n",min(N,Query(ROOT,1,N,h)));
		}
		else assert(0);
	}
	return 0;
}
