#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9;
unsigned int Rand()
{
	static unsigned int seed=20160219;
	seed*=0xdefaced,seed+=134454;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2];
	const int val;
	unsigned int sz;
	bool flipped;
	Node(const int _val):ch{NULL,NULL},val(_val),sz(1),flipped(false){}
	static unsigned int Sz(Node *o){return o?o->sz:0;}
	void Maintain()
	{
		assert(!flipped);
		sz=Sz(ch[0])+1+Sz(ch[1]);
	}
	void Flip(){flipped^=true,swap(ch[0],ch[1]);}
	void PutDown()
	{
		if(!flipped)return;
		for(int d=0;d<2;d++)if(ch[d])ch[d]->Flip();
		flipped=false;
	}
};
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(Rand()%(a->sz+b->sz)<a->sz)
	{
		a->PutDown();
		a->ch[1]=Merge(a->ch[1],b);
		a->Maintain();
		return a;
	}
	else
	{
		b->PutDown();
		b->ch[0]=Merge(a,b->ch[0]);
		b->Maintain();
		return b;
	}
}
void Split(Node *o,Node* &a,Node* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	if(loc<=(int)Node::Sz(o->ch[0]))
	{
		(b=o)->PutDown();
		Split(b->ch[0],a,b->ch[0],loc);
		b->Maintain();
	}
	else
	{
		(a=o)->PutDown();
		Split(a->ch[1],a->ch[1],b,loc-Node::Sz(o->ch[0])-1);
		a->Maintain();
	}
}
void Extract(Node *o,vector<double>&output)
{
	if(!o)return;
	o->PutDown();
	Extract(o->ch[0],output);
	output.push_back(o->val);
	Extract(o->ch[1],output);
}
double Sq(const double &x){return x*x;}
double GetAns(const vector<double>&xs,const vector<double>&ys,const double &x,const double &y)
{
	assert(xs.size()==ys.size());
	double ans=0.0;
	for(int i=0;i<(int)xs.size();i++)ans=max(ans,sqrt(Sq(x-xs[i])+Sq(y-ys[i])));
	return ans;
}
Node *S[2];
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	int querycount;
	scanf("%d%d",&N,&querycount);
	S[0]=S[1]=NULL;
	for(int d=0;d<2;d++)for(int i=0,v;i<N;i++)scanf("%d",&v),S[d]=Merge(S[d],new Node(v));
	for(int type;querycount--;)
	{
		scanf("%d",&type);
		switch(type)
		{
			case 1:
			{
				int id,l,r;scanf("%d%d%d",&id,&l,&r),l--;
				Node *a,*b,*c;
				Split(S[id],b,c,r);
				Split(b,a,b,l);
				b->Flip();
				S[id]=Merge(a,Merge(b,c));
			}break;
			case 2:
			{
				int id,l1,r1,l2,r2;scanf("%d%d%d%d%d",&id,&l1,&r1,&l2,&r2),l1--,l2--;
				Node *a,*b,*c,*d,*e;
				Split(S[id],d,e,r2);
				Split(d,c,d,l2);
				Split(c,b,c,r1);
				Split(b,a,b,l1);
				S[id]=Merge(Merge(a,d),Merge(c,Merge(b,e)));
			}break;
			case 3:
			{
				int l,r;scanf("%d%d",&l,&r),l--;
				Node *a0,*b0,*c0,*a1,*b1,*c1;
				Split(S[0],b0,c0,r);
				Split(b0,a0,b0,l);
				Split(S[1],b1,c1,r);
				Split(b1,a1,b1,l);
				S[0]=Merge(a0,Merge(b1,c0));
				S[1]=Merge(a1,Merge(b0,c1));
			}break;
			case 4:
			{
				int l,r;scanf("%d%d",&l,&r),l--;
				Node *a0,*b0,*c0,*a1,*b1,*c1;
				Split(S[0],b0,c0,r);
				Split(b0,a0,b0,l);
				Split(S[1],b1,c1,r);
				Split(b1,a1,b1,l);
				vector<double>xs,ys;
				Extract(b0,xs),Extract(b1,ys);
				S[0]=Merge(a0,Merge(b0,c0));
				S[1]=Merge(a1,Merge(b1,c1));
				double x=0.0,y=0.0,bestans=GetAns(xs,ys,x,y);
//				int cnt=0;
				for(double temperature=1e6,ratio=0.98,angle=0.0;temperature>=EPS;temperature*=ratio)
				{
//					const double &angle=0.001*Rand();
					const double &nxtx=x+cos(angle)*temperature,&nxty=y+sin(angle)*temperature;
					const double &ta=GetAns(xs,ys,nxtx,nxty);
					if(ta<bestans)bestans=ta,x=nxtx,y=nxty;
					angle+=1.0;
//					cnt++;
				}
//				printf("cnt=%d\n",cnt);
				printf("%.2f\n",bestans);
			}break;
		}
		assert((int)S[0]->sz==N&&(int)S[1]->sz==N);
	}
	return 0;
}
