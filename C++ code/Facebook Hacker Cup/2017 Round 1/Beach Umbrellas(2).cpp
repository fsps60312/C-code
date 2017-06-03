#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
struct Node
{
	static unsigned int rand()
	{
		static unsigned int seed=20170115;
		seed*=0xdefaced;
		seed+=191705;
		return seed+=seed>>20;
	}
	Node *ch[2];
	LL mul,v;
	unsigned int pri;
	Node(const LL _v):ch{NULL,NULL},mul(_v),v(_v),pri(rand()){}
	void Maintain()
	{
		mul=v;
		if(ch[0])(mul*=ch[0]->mul)%=MOD;
		if(ch[1])(mul*=ch[1]->mul)%=MOD;
	}
};
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
	{
		a->ch[1]=Merge(a->ch[1],b);
		a->Maintain();
		return a;
	}
	else
	{
		b->ch[0]=Merge(a,b->ch[0]);
		b->Maintain();
		return b;
	}
}
void Split(Node *o,Node* &a,Node* &b,const LL v)
{
	if(!o){a=b=NULL;return;}
	if(v<=o->v)
	{
		b=o;
		Split(o->ch[0],a,b->ch[0],v);
		b->Maintain();
	}
	else
	{
		a=o;
		Split(o->ch[1],a->ch[1],b,v);
		a->Maintain();
	}
}
void Delete(Node *o)
{
	if(!o)return;
	Delete(o->ch[0]),Delete(o->ch[1]);
	delete o;
}
int N,M,R[2000];
LL SUM;
//LL C(const int a,const int b)
//{
//	if(b==N-1)
//	{
//		
//	}
//	assert(0);return -1;
//}
int CNT[2001];
LL Solve1()
{
	Node *mul=NULL;
	for(int i=0;i<N-1;i++)mul=Merge(new Node(M+2000-SUM+N-1-i),mul);
	LL ans=0;
	for(int i=2000;i>=1&&M+i-SUM+N-1>=0;i--)
	{
//		if(CNT[i])printf("1: %d->%d\n",i,CNT[i]);
		(ans+=2*CNT[i]*(mul?mul->mul:1)/*C(M+i-SUM+N-1,N-1)*/)%=MOD;
		if(M+i-SUM+N-1==0)break;
		mul=Merge(new Node(M+i-SUM),mul);
		Node *a,*b;
		Split(mul,a,b,M+i-SUM+N-1);
		assert(b&&!b->ch[0]&&!b->ch[1]);
		delete b;
		mul=a;
	}
	Delete(mul);
	return ans;
}
LL Solve2()
{
	Node *mul=NULL;
	for(int i=0;i<N-2;i++)mul=Merge(new Node(M+4000-SUM+N-2-i),mul);
	LL ans=0;
	for(int i=4000;i>=2&&M+i-SUM+N-2>=0;i--)
	{
		for(int j=1;j<i;j++)if(j<=2000&&i-j<=2000)
		{
//			if(CNT[j]*CNT[i-j]-min(CNT[j],CNT[i-j]))printf("2: (%d,%d)->%d\n",i,j,CNT[j]*CNT[i-j]-min(CNT[j],CNT[i-j]));
			(ans+=(CNT[j]*CNT[i-j]-min(CNT[j],CNT[i-j]))*(mul?mul->mul:1)/*C(M+i-SUM+N-2,N-2)*/)%=MOD;
		}
		if(M+i-SUM+N-2==0)break;
		mul=Merge(new Node(M+i-SUM),mul);
		Node *a,*b;
		Split(mul,a,b,M+i-SUM+N-2);
		assert(b&&!b->ch[0]&&!b->ch[1]);
		delete b;
		mul=a;
	}
	Delete(mul);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		M--;
		SUM=0;
		for(int i=0;i<N;i++)scanf("%d",&R[i]),SUM+=R[i]*2;
		sort(R,R+N);
		for(int i=1;i<=2000;i++)CNT[i]=(int)((R+N)-lower_bound(R,R+N,i));
		LL ans=0;
		if(SUM<=M)
		{
			LL mul=1;
			for(int i=1;i<=N;i++)(mul*=M-SUM+i)%=MOD;
			(ans+=mul)%=MOD;
		}
		(ans+=Solve1())%=MOD;
//		printf("Solve1=%lld\n",Solve1());
		if(N>=2)(ans+=Solve2())%=MOD;
		if(N==1)ans=M+1;
		static int kase=0;
		printf("Case #%d: %lld\n",++kase,ans);
	}
	return 0;
}
