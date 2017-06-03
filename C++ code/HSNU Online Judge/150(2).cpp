#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
unsigned int MyRand()
{
	static unsigned int seed=20160106;
	seed=seed*0xdefaced+94732;
	return seed+=seed>>20;
}
struct Node2D
{
	Node2D *ch[2];
	const int id;
	int mn,sz;
	unsigned int pri;
	Node2D(const int _id):ch{NULL,NULL},id(_id),mn(_id),sz(1),pri(MyRand()){}
};
int Mn(Node2D* &o){return o?o->mn:INF;}
int Sz(Node2D* &o){return o?o->sz:0;}
void Maintain(Node2D* &o)
{
	o->mn=min(o->id,min(Mn(o->ch[0]),Mn(o->ch[1])));
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
}
Node2D *Merge(Node2D *a,Node2D *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
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
void Split(Node2D *o,Node2D* &a,Node2D* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=Sz(o->ch[0]))
	{
		b=o;
		Split(b->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(a->ch[1],a->ch[1],b,loc-(Sz(o->ch[0])+1));
		Maintain(a);
	}
}
int Query(Node2D* &o,const int value)
{
	if(!o||o->mn>value)return -1;
	if(o->id==value)return Sz(o->ch[0]);
	else if(Mn(o->ch[0])==value)return Query(o->ch[0],value);
	else
	{
		assert(Mn(o->ch[1])==value);
		return Sz(o->ch[0])+1+Query(o->ch[1],value);
	}
}
struct Node1D
{
	Node1D *ch[2];
	Node2D *flexible,*fixed;
	int mn,sz;
	unsigned int pri;
	Node1D(Node2D *_fle,Node2D *_fix):ch{NULL,NULL},flexible(_fle),fixed(_fix),mn(min(Mn(_fle),Mn(_fix))),sz(1),pri(MyRand()){}
};
int Id(Node1D* &o){return min(Mn(o->flexible),Mn(o->fixed));}
int Mn(Node1D* &o){return o?o->mn:INF;}
int Sz(Node1D* &o){return o?o->sz:0;}
void Maintain(Node1D* &o)
{
	o->mn=min(Id(o),min(Mn(o->ch[0]),Mn(o->ch[1])));
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
}
Node1D *Merge(Node1D *a,Node1D *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
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
void Split(Node1D *o,Node1D* &a,Node1D* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=Sz(o->ch[0]))
	{
		b=o;
		Split(b->ch[0],a,b->ch[0],loc);
		Maintain(b);
	}
	else
	{
		a=o;
		Split(a->ch[1],a->ch[1],b,loc-(Sz(o->ch[0])+1));
		Maintain(a);
	}
}
int Query(Node1D* &o,const int value)
{
	if(!o||o->mn>value)return -1;
	if(Id(o)==value)return Sz(o->ch[0]);
	else if(Mn(o->ch[0])==value)return Query(o->ch[0],value);
	else
	{
		assert(Mn(o->ch[1])==value);
		return Sz(o->ch[0])+1+Query(o->ch[1],value);
	}
}
Node2D *Merge(Node1D* &o)
{
	if(!o)return NULL;
	Node2D *ans=Merge(o->ch[0]);
	ans=Merge(ans,Merge(o->flexible,o->fixed));
	ans=Merge(ans,Merge(o->ch[1]));
	return ans;
}
void Print(Node2D* &o)
{
	if(!o)return;
	Print(o->ch[0]);
	printf("%d ",o->id);
	Print(o->ch[1]);
}
void Print(Node1D* &o)
{
	if(!o)return;
	Print(o->ch[0]);
	putchar('{');
	Print(o->flexible);
	putchar(',');
	Print(o->fixed);
	putchar('}');
	Print(o->ch[1]);
}
int N,S[100000],ANS[100001];
bool Solve()
{
	Node2D *right=NULL;
	Node1D *left=NULL;
	for(int i=0;i<N;i++)scanf("%d",&S[i]),right=Merge(right,new Node2D(S[i]));
	for(int id=1;id<=N;id++)
	{
		printf("id=%d\n",id);
		printf("left:");Print(left);puts("");
		printf("right:");Print(right);puts("");
		const int loc0=Query(right,id);
		if(loc0!=-1)
		{
			Node2D *a,*b,*c;
			Split(right,a,right,loc0);
			Split(right,b,c,1);
			assert(b->id==id);
			delete b;b=NULL;
			right=c;
			if(a!=NULL)left=Merge(left,new Node1D(a,NULL));
			ANS[id]=1;
		}
		else
		{
			const int loc1=Query(left,id);
			assert(loc1!=-1);
			Node1D *a,*b,*c;
			Split(left,a,b,loc1);
			Split(b,b,c,1);
			const int loc2=Query(b->flexible,id);
			if(loc2!=-1)
			{
				Node2D *d,*e,*f;
				Split(b->flexible,d,e,loc2);
				Split(e,e,f,1);
				assert(e->id==id);
				delete e;e=NULL;
				left=Merge(a,new Node1D(d,Merge(Merge(f,b->fixed),Merge(c))));
			}
			else
			{
				
			}
			ANS[id]=2;
		}
		printf("ans=%d\n\n",ANS[id]);
	}
	assert(0&&"not implement");
	//ReIndex();
	return true;
}
#include<stack>
void CheckAns()
{
	stack<int>a,b;
	int now=1;
	for(int i=0;i<N;i++)
	{
		if(ANS[S[i]]==1)a.push(S[i]);
		else b.push(S[i]);
		while((!a.empty()&&a.top()==now)||(!b.empty()&&b.top()==now))
		{
			if(!a.empty()&&a.top()==now)now++,a.pop();
			else assert(!b.empty()&&b.top()==now),now++,b.pop();
		}
	}
	assert(now==N+1);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		if(Solve())
		{
			puts("TAK");
			for(int i=0;i<N;i++)
			{
				if(i)putchar(' ');
				printf("%d",ANS[S[i]]);
			}
			puts("");
			CheckAns();
		}
		else puts("NIE");
//		break;
	}
	return 0;
}
/*
8
6 2 4 1 8 3 7 5 
*/
