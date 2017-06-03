#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
int N;
struct Node
{
	Node *ch[2];
	int mx;
	Node(const int &_h):mx(_h),ch{NULL,NULL}{}
}*ROOT=new Node(0);
void Maintain(Node* &o){if(o->ch[0]==NULL)return;o->mx=max(o->ch[0]->mx,o->ch[1]->mx);}
void Modify(Node* &o,const int &l,const int &r,const int &x1,const int &x2,const int &h)
{
	if(r<x1||x2>l)return;
	if(x1<=l&&r<=x2){o=new Node(h);return;}
	if(o->ch[0]==NULL)
	{
		o->ch[0]=new Node(o->mx);
		o->ch[1]=new Node(o->mx);
	}
	int mid=(l+r)/2;
	Modify(o->ch[0],l,mid,x1,x2,h);
	Modify(o->ch[1],mid+1,r,x1,x2,h);
	Maintain(o);
}
int Query(Node* &o,const int &l,const int &r,const int &h)
{
	if(o->mx<=h)return r;
	if(o->ch[0]==NULL)return 0;
	int mid=(l+r)/2;
	return max(Query(o->ch[0],l,mid,h),Query(o->ch[1],mid+1,r,h));
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
			printf("%d\n",Query(ROOT,1,N,h));
//			puts("pass");
		}
		else assert(0);
	}
	return 0;
}
