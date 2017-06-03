#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N;
struct Node
{
	Node *ch[2];
	int sum;
	Node(const int &s):sum(s),ch{NULL,NULL}{}
}*ROOT=new Node(0);
void Maintain(Node* &o){if(o->ch[0]==NULL)return;o->sum=o->ch[0]->sum+o->ch[1]->sum;}
void Modify(Node* &o,const int &l,const int &r,const int &x1,const int &x2,const int &h)
{
//	printf("Modify(%d,%d)%d\n",l,r,o->sum);
	if(r<x1||l>x2)return;
	if(x1<=l&&r<=x2){o=new Node(h*(r-l+1));return;}
	int mid=(l+r)/2;
	if(o->ch[0]==NULL)
	{
		assert(o->sum%(r-l+1)==0);
		int th=o->sum%(r-l+1);
		o->ch[0]=new Node(th*(mid-l+1));
		o->ch[1]=new Node(th*(r-mid));
	}
	Modify(o->ch[0],l,mid,x1,x2,h);
	Modify(o->ch[1],mid+1,r,x1,x2,h);
	Maintain(o);
}
int Query(Node* &o,const int &l,const int &r,const int &sum)
{
//	printf("Query(%d,%d)%d\n",l,r,o->sum);
	if(o->ch[0]==NULL)
	{
		assert(o->sum%(r-l+1)==0);
		int h=o->sum/(r-l+1);
		if(!h)return INF;
		return l-1+sum/h;
	}
	int mid=(l+r)/2;
	if(sum<(o->ch[0]->sum))return Query(o->ch[0],l,mid,sum);
	else return Query(o->ch[1],mid+1,r,sum-o->ch[0]->sum);
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	static char type[2];
	while(scanf("%s",type)==1)
	{
//		printf("type=%s\n",type);
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
//			puts("pass");
		}
		else assert(0);
	}
	return 0;
}
