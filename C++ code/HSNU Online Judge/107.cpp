#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
int N;
struct Node
{
	int v;
	Node *l,*r,*pre,*nxt;
}S[1000000];
int SEG_SUM[2000001];
void Build(const int id,const int l,const int r)
{
	SEG_SUM[id]=r-l+1;
	if(l==r)return;
	int mid=(l+r)/2;
	Build(id*2,l,mid);
	Build(id*2+1,mid+1,r);
}
void Query(const int id,const int l,const int r,const int rank,int &ans)
{
	if(l==r)
	{
//		printf("rank=%d,SEG_SUM[%d]=%d\n",rank,id,SEG_SUM[id]);
		assert(rank==1&&SEG_SUM[id]==1);
		SEG_SUM[id]=0;
		ans=l;
		return;
	}
	int mid=(l+r)/2;
	if(rank-SEG_SUM[id*2]>=1)Query(id*2+1,mid+1,r,rank-SEG_SUM[id*2],ans);
	else Query(id*2,l,mid,rank,ans);
	SEG_SUM[id]=SEG_SUM[id*2]+SEG_SUM[id*2+1];
}
void Input()
{
	static LL m,a,b,x[1000001];
	scanf("%d%lld%lld%lld%lld",&N,&m,&x[0],&a,&b);
	for(int i=1;i<=N;i++)x[i]=(x[i-1]*a+b)%m;
	Build(1,1,N);
	for(int i=1;i<=N;i++)
	{
		Query(1,1,N,(x[i]+N-i)%(N-i+1)+1,S[i-1].v);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcase_cnt=1;
	scanf("%d",&testcase_cnt);
	while(testcase_cnt--)
	{
		Input();
//		N=10;
//		int s[]={10,9,8,6,4,7,5,3,2,1};
//		int s[]={10,9,8,7,6,5,4,3,2,1};
//		int s[]={1,2,3,4,5,6,7,8,9,10};
//		for(int i=0;i<N;i++)S[i].v=s[i];
//		for(int i=0;i<N;i++)printf(" %d",S[i].v);puts("");
		vector<int>tail;
		for(int i=1;i<=N;i++)
		{
			S[i%N].l=&S[i-1];
			S[i-1].r=&S[i%N];
			if(S[i-1].v<=S[i%N].v)tail.push_back(i-1);
		}
		for(int i=1;i<=tail.size();i++)
		{
			int pre=tail[i-1],nxt=tail[i%tail.size()];
			S[pre].nxt=&S[nxt];
			S[nxt].pre=&S[pre];
		}
		Node *u=&S[tail[0]];
		vector<int>seq;
		while(1)
		{
			seq.push_back((u-S)+1);
			if(u==u->r)break;
			u->r->l=u->l;
			u->l->r=u->r;
			if(u->l->v>u->r->v||u->l->v<u->v)
			{
				u->pre->nxt=u->nxt;
				u->nxt->pre=u->pre;
			}
			else
			{
				u->pre->nxt=u->nxt->pre=u->l;
				u->l->pre=u->pre;
				u->l->nxt=u->nxt;
			}
			u=u->nxt;
		}
		assert(seq.size()==N);
//		for(int i=0;i<seq.size();i++)printf(" %d",seq[i]);puts("");
		LL ans=0LL;
		for(int i=0;i<seq.size();i++)ans+=(i+1LL)*seq[i];
		printf("%lld\n",ans);
	}
	return 0;
}
