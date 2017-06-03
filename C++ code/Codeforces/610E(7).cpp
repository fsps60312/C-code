#include<cstdio>
#include<cassert>
#include<map>
#include<utility>
using namespace std;
int K;
namespace SegTree
{
	map<int,int>D;
	inline int GetC(const int i)
	{
		auto it=D.upper_bound(i);
		assert(it!=D.begin());
		return (--it)->second;
	}
	struct Node
	{
		static Node POOL[800000];
		int C[100];
		int TAG;
		Node *L,*R;
		inline void Rebuild(const int loc)
		{
			TAG=-1;
			for(int i=0;i<K*K;i++)C[i]=0;
			++C[GetC(loc)*K+GetC(loc+1)];
		}
		inline void SetTag(const int c,const int cnt)
		{
			TAG=c;
			for(int i=0;i<K*K;i++)C[i]=0;
			C[c*K+c]=cnt;
		}
		inline void Maintain()
		{
			TAG=-1;
			for(int i=0;i<K*K;i++)C[i]=L->C[i]+R->C[i];
		}
		inline void PutDown(const int l,const int mid,const int r)
		{
			if(TAG==-1)return;
			const int c=TAG;TAG=-1;
			L->SetTag(c,mid-l+1),R->SetTag(c,r-mid);
		}
	}Node::POOL[800000],*NEW=Node::POOL;
	Node *NewNode(){assert(NEW-Node::POOL<800000);return new (NEW++)Node();}
	Node *ROOT;
	int N;
	Node *Build(const int l,const int r)
	{
		if(l==r)
		{
			Node *o=NewNode();
			o->Rebuild(r);
			return o;
		}
		else
		{
			Node *o=NewNode();
			const int mid=(l+r)/2;
			o->L=Build(l,mid),o->R=Build(mid+1,r);
			o->Maintain();
			return o;
		}
	}
	void Build(const int _N,const char *str)
	{
		N=_N;
		D.clear();
		for(int i=0;i<N;i++)D[i]=str[i]-'a';
		NEW=Node::POOL;
		ROOT=Build(0,N-2);
	}
	void ModifyOne(Node *o,const int l,const int r,const int loc)
	{
		if(l==r)
		{
			assert(loc==r);
			o->Rebuild(loc);
			return;
		}
		else
		{
			const int mid=(l+r)/2;
			o->PutDown(l,mid,r);
			if(loc<=mid)ModifyOne(o->L,l,mid,loc);
			else ModifyOne(o->R,mid+1,r,loc);
			o->Maintain();
		}
	}
	void ModifyToSame(Node *o,const int l,const int r,const int bl,const int br,const int c)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br)
		{
			o->SetTag(c,r-l+1);
			return;
		}
		const int mid=(l+r)/2;
		o->PutDown(l,mid,r);
		ModifyToSame(o->L,l,mid,bl,br,c),ModifyToSame(o->R,mid+1,r,bl,br,c);
		o->Maintain();
	}
	void Modify(const int l,const int r,const int c)
	{
		if(r+1<N)
		{
			const int t=GetC(r+1);
			D[r+1]=t;
		}
		D[l]=c;
		auto it=D.find(l);
		for(++it;it!=D.end()&&it->first<=r;)D.erase(it++);
		if(l-1>=0)ModifyOne(ROOT,0,N-2,l-1);
		if(r+1<N)ModifyOne(ROOT,0,N-2,r);
		ModifyToSame(ROOT,0,N-2,l,r-1,c);
	}
};
int N,M;
char S[200001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		scanf("%s",S);
		SegTree::Build(N,S);
		for(int type;M--;)
		{
			scanf("%d",&type);
			if(type==1)
			{
				int l,r;
				static char c[2];
				scanf("%d%d%s",&l,&r,c),--l,--r;
				SegTree::Modify(l,r,c[0]-'a');
			}
			else if(type==2)
			{
				static char s[11];
				scanf("%s",s);
				static int loc[11];
				for(int i=0;i<K;i++)loc[s[i]-'a']=i;
				int ans=1;
				for(int i=0;i<K*K;i++)if(loc[i/K]>=loc[i%K])ans+=SegTree::ROOT->C[i];
				printf("%d\n",ans);
			}
			else assert(0);
		}
	}
}
