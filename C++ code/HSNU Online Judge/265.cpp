#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const double EPS=1e-9;
typedef long long LL;
struct Node
{
	Node *ch[2];
	int sz,order,idx;
	double value,sum;
	Node(const double &_v,const int _r,const int _i):ch{NULL,NULL},sz(1),order(_r),idx(_i),value(_v),sum(_v){}
}*ROOT;
int Sz(Node* &o){return o?o->sz:0;}
double Sum(Node* &o){return o?o->sum:0.0;}
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
void Insert(Node* &o,const double &v,const int &r,const int i)
{
	if(!o){o=new Node(v,r,i);return;}
	Insert(o->ch[v<o->value?0:1],v,r,i);
	Maintain(o),Rotate(o);
}
void Query(Node* &o,const double &budget,int &cnt,double &sum)
{
	assert(budget>=0.0);
	if(!o)return;
	if(Sum(o->ch[0])>budget)Query(o->ch[0],budget,cnt,sum);
	else if(Sum(o->ch[0])+(o->value)>budget)cnt+=Sz(o->ch[0]),sum+=Sum(o->ch[0]);
	else
	{
		const double &v=Sum(o->ch[0])+(o->value);
		Query(o->ch[1],budget-v,cnt+=Sz(o->ch[0])+1,sum+=v);
	}
}
void Extract(Node* &o,vector<int>&ans,int &cnt,const int bound)
{
	if(!o||!cnt)return;
	Extract(o->ch[0],ans,cnt,bound);
	if((o->order)<=bound)ans.push_back(o->idx),cnt--;
	Extract(o->ch[1],ans,cnt,bound);
}
int N;
double BUDGET;
struct Worker
{
	double mincost,technique;
	int idx;
	Worker(){}
	Worker(const double &_m,const double &_t,const int _i):mincost(_m),technique(_t),idx(_i){}
	//b.c==a.c/a.t*b.t
	//b.c/b.t==a.c/a.t
	//
	bool operator<(const Worker &w)const{return mincost/technique<w.mincost/w.technique;}
};
vector<Worker>WORKER;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lf",&N,&BUDGET)==2)
	{
		WORKER.clear();
		for(int i=0;i<N;i++)
		{
			static double cost,tech;
			assert(scanf("%lf%lf",&cost,&tech)==2);
			WORKER.push_back(Worker(cost,tech,i+1));
		}
		sort(WORKER.begin(),WORKER.end());
		ROOT=NULL;
		int anscnt=-1,ansidx=-1;
		double anscost=-1e100;
		for(int i=0;i<N;i++)
		{
			const Worker &w=WORKER[i];
			const double ratio=w.mincost/w.technique;
//			puts("a");
			Insert(ROOT,w.technique,i,w.idx);
//			printf("sz=%d\n",Sz(ROOT));
//			puts("b");
			int cnt=0;
			double cost=0.0;
			Query(ROOT,BUDGET/ratio,cnt,cost);
//			printf("%d %lf\n",cnt,cost*ratio);
//			puts("c");
			if(cnt>anscnt||(cnt==anscnt&&cost*ratio+EPS<anscost))anscnt=cnt,ansidx=i,anscost=cost*ratio;
		}
		if(anscnt==-1)puts("0");
		else
		{
			printf("%d\n",anscnt);
			vector<int>ans;
			Extract(ROOT,ans,anscnt,ansidx);
			sort(ans.begin(),ans.end());
			for(const auto v:ans)printf("%d\n",v);
		}
		break;
	}
	return 0;
}
