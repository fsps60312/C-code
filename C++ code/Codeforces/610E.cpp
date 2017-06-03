#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
int K;
namespace SegTree
{
	map<int,char>D;
	char GetC(const int i)
	{
		auto it=D.upper_bound(i);
		assert(it!=D.begin());
		return (--it)->second;
	}
	struct Node
	{
		int C[10][10],TAG;
		void Rebuild(const int l,const int r)
		{
			for(int i=0;i<K;i++)for(int j=0;j<K;j++)C[i][j]=0;
			for(int i=l;i<=r;i++)++C[GetC(i)-'a'][GetC(i+1)-'a'];
		}
	};
	Node Merge(const Node &a,const Node &b)
	{
		Node o;
		o.TAG=-1;
		for(int i=0;i<K;i++)for(int j=0;j<K;j++)o.C[i][j]=a.C[i][j]+b.C[i][j];
		return o;
	}
	Node S[8000];
	int N;
	void Build(const int id,const int l,const int r)
	{
		S[id].TAG=-1;
		if(r-l+1<=100)
		{
			S[id].Rebuild(l,r);
			return;
		}
		else
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
			S[id]=Merge(S[id*2],S[id*2+1]);
		}
	}
	void Build(const int _N,const char *str)
	{
		N=_N;
		D.clear();
		for(int i=0;i<N;i++)D[i]=str[i];
		Build(1,0,N-2);
	}
	void ModifyOne(const int id,const int l,const int r,const int loc,const char pre_a,const char pre_b,const char now_a,const char now_b)
	{
		
	}
	void Modify(const int l,const int r,const char c)
	{
		if(l-1>=0)ModifyOne(1,0,N-2,l-1,GetC(l-1),GetC(l),GetC(l-1),c);
		if(r+1<N)
		{
			ModifyOne(1,0,N-2,r,GetC(r),GetC(r+1),c,GetC(r+1));
			const char t=GetC(r+1);
			D[r+1]=t;
		}
		D[l]=c;
		auto it=D.find(l);
		for(++it;it!=D.end()&&it->first<=r;)D.erase(it++);
		ModifyToSame(1,0,N-2,l,r-1,c);
	}
};
int N,M;
char S[200001];
int main()
{
	freopen("in.txt","r",stdin);
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
				SegTree::Modify(l,r,c[0]);
			}
			else if(type==2)
			{
				assert(0);
			}
			else assert(0);
		}
	}
}
