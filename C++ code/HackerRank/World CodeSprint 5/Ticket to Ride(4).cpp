#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
typedef long long LL;
const LL INF=9223372036854775807LL;
struct SegTree
{
	int N;
	LL S[800000],TAG[800000];
	inline void PutDown(const int id)
	{
		if(!TAG[id])return;
		const LL v=TAG[id];TAG[id]=0;
		S[id*2]+=v,S[id*2+1]+=v;
		TAG[id*2]+=v,TAG[id*2+1]+=v;
	}
	inline void Maintain(const int id)
	{
		S[id]=max(S[id*2],S[id*2+1]);
	}
	void Build(const int id,const int l,const int r)
	{
		S[id]=TAG[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _N){N=_N;Build(1,0,N-1);}
	void Add(const int id,const int l,const int r,const int bl,const int br,const LL val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){S[id]+=val,TAG[id]+=val;return;}
		const int mid=(l+r)/2;
		PutDown(id);
		Add(id*2,l,mid,bl,br,val),Add(id*2+1,mid+1,r,bl,br,val);
		Maintain(id);
	}
	void Add(const int bl,const int br,const LL val){Add(1,0,N-1,bl,br,val);}
	LL QueryMax(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return -INF;
		if(bl<=l&&r<=br)return S[id];
		const int mid=(l+r)/2;
		PutDown(id);
		return max(QueryMax(id*2,l,mid,bl,br),QueryMax(id*2+1,mid+1,r,bl,br));
	}
	LL QueryMax(const int bl,const int br){return QueryMax(1,0,N-1,bl,br);}
}SEG;
struct Edge
{
	int A,B,COST;
	Edge(){}
	Edge(const int _A,const int _B,const int _COST):A(_A),B(_B),COST(_COST){}
};
vector<Edge>EDGE,TICKET;
int N,M;
vector<int>ET[200000],EK[200000];
int L[200000],R[200000],SZ[200000];
void BuildSquashedTree(const int u,const int parent,int &tick)
{
	L[u]=tick;
	SZ[u]=1+(int)EK[u].size();
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt==parent)continue;
		BuildSquashedTree(nxt,u,tick);
		SZ[u]+=SZ[nxt];
	}
	R[u]=tick++;
}
#include<utility>
LL ANS;
void DfsSummarize(const int u,const int parent,const int ql,const int qr)
{
	for(const int ki:EK[u])
	{
		const Edge &ticket=TICKET[ki];
		const int nxt=(u==ticket.A?ticket.B:ticket.A);
		if(ql<=R[nxt]&&R[nxt]<=qr)SEG.Add(L[nxt],R[nxt],ticket.COST);
//		printf("Add(%lld)\n",ticket.COST);
	}
	getmax(ANS,SEG.QueryMax(ql,qr)+SEG.QueryMax(R[u],R[u]));
//	printf("u=%d, best=%lld\n",u+1,SEG.QueryMax(ql,qr)-now_cost);
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt!=parent)DfsSummarize(nxt,u,ql,qr);
	}
	for(const int ki:EK[u])
	{
		const Edge &ticket=TICKET[ki];
		const int nxt=(u==ticket.A?ticket.B:ticket.A);
		if(ql<=R[nxt]&&R[nxt]<=qr)SEG.Add(L[nxt],R[nxt],-ticket.COST);
	}
}
struct Node
{
	int SZ,L,R;
	vector<int>CH;
	Node(const int _SZ,const int _L,const int _R):SZ(_SZ),L(_L),R(_R){}
};
Node*Merge(const int u,Node*a,Node*b)
{
	if(a->SZ>b->SZ)swap(a,b);
//	printf("from:");for(auto v:a->CH)printf(" %d",v.first+1);puts("");
//	printf("to  :");for(auto v:b->CH)printf(" %d",v.first+1);puts("");
	for(const int nxt:a->CH)
	{
		DfsSummarize(nxt,u,b->L,b->R);
		b->CH.push_back(nxt);
	}
	b->SZ+=a->SZ;
	getmin(b->L,a->L);
	getmax(b->R,a->R);
	vector<int>().swap(a->CH);
	delete a;
	return b;
}
void DfsSolve(const int u,const int parent)
{
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt==parent)continue;
		DfsSolve(nxt,u);
		SEG.Add(L[nxt],R[nxt],-e.COST);
	}
	for(const int ki:EK[u])
	{
		const Edge &ticket=TICKET[ki];
		const int nxt=(u==ticket.A?ticket.B:ticket.A);
		if(L[u]<=R[nxt]&&R[nxt]<R[u])SEG.Add(L[nxt],R[nxt],ticket.COST);
//		printf("Add(%lld)\n",ticket.COST);
	}
//	printf("u=%d\n",u);
	getmax(ANS,SEG.QueryMax(L[u],R[u]));
	Node*p=new Node(0,L[u],L[u]);
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.A?e.B:e.A);
		if(nxt==parent)continue;
		Node*chp=new Node(SZ[nxt],L[nxt],R[nxt]);
		chp->CH.push_back(nxt);
		p=Merge(u,p,chp);
	}
	vector<int>().swap(p->CH);
	delete p;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear(),EK[i].clear();
		EDGE.clear(),TICKET.clear();
		for(int i=0,a,b,cost;i<N-1;i++)
		{
			scanf("%d%d%d",&a,&b,&cost),--a,--b;
			EDGE.push_back(Edge(a,b,cost));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		scanf("%d",&M);
		for(int i=0,a,b,cost;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&cost),--a,--b;
			TICKET.push_back(Edge(a,b,cost));
			EK[a].push_back(i),EK[b].push_back(i);
		}
		{int tick=0;BuildSquashedTree(2*N/3,-1,tick);assert(tick==N);}
		ANS=0;
		SEG.Build(N);
		DfsSolve(2*N/3,-1);
//		for(int i=0;i<N;i++)printf("LEN[%d]=%lld\n",i+1,SEG.QueryMax(R[i],R[i]));
		printf("%lld\n",ANS);
	}
	return 0;
}
