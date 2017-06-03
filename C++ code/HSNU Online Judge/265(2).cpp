#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Node
{
	Node *ch[2];
	int sz,order,idx;
	LL value,sum;
	Node(const LL &_v,const int _r,const int _i):ch{NULL,NULL},sz(1),order(_r),idx(_i),value(_v),sum(_v){}
}*ROOT;
int Sz(Node* &o){return o?o->sz:0;}
LL Sum(Node* &o){return o?o->sum:0LL;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+(o->value)+Sum(o->ch[1]);
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
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[1])>Sz(o->ch[0]))Rotate(o,1);
}
void Insert(Node* &o,const LL &v,const int r,const int i)
{
	if(!o){o=new Node(v,r,i);return;}
	Insert(o->ch[v<o->value?0:1],v,r,i);
	Maintain(o),Rotate(o);
}
void Query(Node* &o,const LL &budget,const LL &ratio,int &cnt,LL &sum)
{
	assert(budget>=0LL);
	if(!o)return;
	const LL v=Sum(o->ch[0])+(o->value);
	if(Sum(o->ch[0])*ratio>budget)Query(o->ch[0],budget,ratio,cnt,sum);
	else if(v*ratio>budget)cnt+=Sz(o->ch[0]),sum+=Sum(o->ch[0]);
	else Query(o->ch[1],budget-v*ratio,ratio,cnt+=Sz(o->ch[0])+1,sum+=v*ratio);
}
void Extract(Node* &o,vector<int>&ans,int &cnt,const int bound)
{
	if(!o||!cnt)return;
	Extract(o->ch[0],ans,cnt,bound);
	if(cnt&&(o->order)<=bound)ans.push_back(o->idx),cnt--;
	Extract(o->ch[1],ans,cnt,bound);
}
int N;
LL BUDGET;
struct Worker
{
	LL mincost,technique;
	int idx;
	Worker(){}
	Worker(const LL &_m,const LL &_t,const int _i):mincost(_m),technique(_t),idx(_i){}
	//b.c==a.c/a.t*b.t
	//b.c/b.t==a.c/a.t
	//
	bool operator<(const Worker &w)const{return mincost*w.technique<w.mincost*technique;}
};
vector<Worker>WORKER;
FILE *test;
int main()
{
	for(int file=0;file<=43;file++)
	{
	char filename[100];
	do
	{
		sprintf(filename,"hiring.%03d.in",file);
		freopen(filename,"r",stdin);
	}while(0);
	while(scanf("%d%lld",&N,&BUDGET)==2)
	{
		WORKER.clear();
		for(int i=0;i<N;i++)
		{
			static LL cost,tech;
			assert(scanf("%lld%lld",&cost,&tech)==2);
			WORKER.push_back(Worker(cost,tech,i+1));
		}
		sort(WORKER.begin(),WORKER.end());
		ROOT=NULL;
		int anscnt=-1,ansidx=-1;
		LL ansup=-1LL,ansdown=0LL;
		for(int i=0;i<N;i++)
		{
			const Worker &w=WORKER[i];
//			printf("(%lld,%lld)\n",w.mincost,w.technique);
			Insert(ROOT,w.technique,i,w.idx);
			int cnt=0;
			LL cost=0LL;
			Query(ROOT,BUDGET*w.technique,w.mincost,cnt,cost);
			if(cnt>anscnt||(cnt==anscnt&&cost*ansdown<ansup*w.technique))
				anscnt=cnt,ansidx=i,ansup=cost,ansdown=w.technique;
		}
//		printf("%lld/%lld -> %lld\n",ansup,ansdown,ansup/ansdown);
		assert(Sz(ROOT)==N);
		if(anscnt==-1)puts("0");
		else
		{
			printf("%d\n",anscnt);
			do
			{
				sprintf(filename,"hiring.%03d.sol",file);
				freopen(filename,"r",stdin);
				int n;scanf("%d",&n);assert(n==anscnt);
			}while(0);
			vector<int>ans;
			int cnt=anscnt;
			Extract(ROOT,ans,cnt,ansidx);
			sort(ans.begin(),ans.end());
			assert((int)ans.size()==anscnt);
//			for(const auto v:ans)printf("%d\n",v);
		}
		break;
	}
	}
	return 0;
}
