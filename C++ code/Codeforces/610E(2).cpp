#include<cstdio>
#include<cassert>
#include<map>
#include<utility>
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
		map<pair<char,char>,int>C;
		char TAG;
		void Rebuild(const int l,const int r)
		{
			TAG='\0';
			C.clear();
			for(int i=l;i<=r;i++)++C[make_pair(GetC(i),GetC(i+1))];
		}
		void SetTag(const char c,const int cnt)
		{
			TAG=c;
			C.clear();
			C[make_pair(c,c)]=cnt;
		}
	};
	Node Merge(const Node &a,const Node &b)
	{
		Node o;
		o.TAG='\0';
		for(const auto &it:a.C)o.C[it.first]+=it.second;
		for(const auto &it:b.C)o.C[it.first]+=it.second;
		return o;
	}
	Node S[800000];
	int N;
	void Build(const int id,const int l,const int r)
	{
		if(l==r)
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
	void PutDown(const int id,const int l,const int mid,const int r)
	{
		if(S[id].TAG=='\0')return;
		const char c=S[id].TAG;S[id].TAG='\0';
		S[id*2].SetTag(c,mid-l+1),S[id*2+1].SetTag(c,r-mid);
	}
	void ModifyOne(const int id,const int l,const int r,const int loc)
	{
		if(l==r)
		{
			assert(loc==r);
			S[id].Rebuild(l,r);
			return;
		}
		else
		{
			const int mid=(l+r)/2;
			PutDown(id,l,mid,r);
			if(loc<=mid)ModifyOne(id*2,l,mid,loc);
			else ModifyOne(id*2+1,mid+1,r,loc);
			S[id]=Merge(S[id*2],S[id*2+1]);
		}
	}
	void ModifyToSame(const int id,const int l,const int r,const int bl,const int br,const char c)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br)
		{
			S[id].SetTag(c,r-l+1);
			return;
		}
		const int mid=(l+r)/2;
		PutDown(id,l,mid,r);
		ModifyToSame(id*2,l,mid,bl,br,c),ModifyToSame(id*2+1,mid+1,r,bl,br,c);
		S[id]=Merge(S[id*2],S[id*2+1]);
	}
	void Modify(const int l,const int r,const char c)
	{
		if(r+1<N)
		{
			const char t=GetC(r+1);
			D[r+1]=t;
		}
		D[l]=c;
		auto it=D.find(l);
		for(++it;it!=D.end()&&it->first<=r;)D.erase(it++);
		if(l-1>=0)ModifyOne(1,0,N-2,l-1);
		if(r+1<N)ModifyOne(1,0,N-2,r);
		ModifyToSame(1,0,N-2,l,r-1,c);
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
				SegTree::Modify(l,r,c[0]);
			}
			else if(type==2)
			{
				static char s[11];
				scanf("%s",s);
				const auto &result=SegTree::S[1];
				static int loc[11];
				for(int i=0;i<K;i++)loc[s[i]-'a']=i;
				int ans=1;
				for(const auto &it:result.C)if(loc[it.first.first-'a']>=loc[it.first.second-'a'])ans+=it.second;
				printf("%d\n",ans);
			}
			else assert(0);
		}
	}
}
