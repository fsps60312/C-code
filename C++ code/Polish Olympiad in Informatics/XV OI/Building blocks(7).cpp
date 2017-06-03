#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
struct SegTree
{
	int *SZ,N;
	void Build(const int id,const int l,const int r)
	{
		if(l==r){SZ[id]=0;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		SZ[id]=SZ[id*2]+SZ[id*2+1];
	}
	void Build(const int _N)
	{
		N=_N;
		SZ=new int[N*4];
		Build(1,0,N);
	}
	void Add(const int id,const int l,const int r,const int loc,const int val)
	{
		SZ[id]+=val;
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Add(id*2,l,mid,loc,val);
			else Add(id*2+1,mid+1,r,loc,val);
		}
	}
	void Add(const int loc,const int val)
	{
		Add(1,0,N,loc,val);
	}
	void Set(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r){SZ[id]=val;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Set(id*2,l,mid,loc,val);
		else Set(id*2+1,mid+1,r,loc,val);
		SZ[id]=SZ[id*2]+SZ[id*2+1];
	}
	void Set(const int loc,const int val)
	{
		Set(1,0,N,loc,val);
	}
	int QueryLoc(const int id,const int l,const int r,const int rank)
	{
		assert(1<=rank&&rank<=SZ[id]);
		if(l==r)return r;
		const int mid=(l+r)/2;
		if(rank<=SZ[id*2])return QueryLoc(id*2,l,mid,rank);
		else return QueryLoc(id*2+1,mid+1,r,rank-SZ[id*2]);
	}
	int QueryLoc(const int rank)
	{
		return QueryLoc(1,0,N,rank);
	}
	int QuerySum(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return 0;
		if(bl<=l&&r<=br)return SZ[id];
		const int mid=(l+r)/2;
		return QuerySum(id*2,l,mid,bl,br)+QuerySum(id*2+1,mid+1,r,bl,br);
	}
	int QuerySum(const int bl,const int br)
	{
		return QuerySum(1,0,N,bl,br);
	}
}SEG;
template<class T>struct Bit
{
	T *S,*D;
	int N;
	Bit<T>(){}
	void Build(const int _N)
	{
		N=_N;
		S=new T[N+1],D=new T[N+1];
		for(int i=1;i<=N;i++)S[i]=D[i]=0;
	}
	void Add(int i,const T val){for(D[++i]+=val;i<=N;i+=i&(-i))S[i]+=val;}
	void Set(int i,const T val){Add(i,val-D[i+1]);}
	T Query(int i)const
	{
		T ans=0;
		for(++i;i;i-=i&(-i))ans+=S[i];
		return ans;
	}
	T QuerySum(const int l,const int r)const{return Query(r)-Query(l-1);}
};
inline char GetChar()
{
	static char buf[1<<20],*p=buf,*end=buf;
	if(p==end)
	{
		if((end=buf+fread(buf,1,1<<20,stdin))==buf)return EOF;
		p=buf;
	}
	return *p++;
}
inline int GetInt()
{
	char c=GetChar();
	for(;c<'0'||'9'<c;c=GetChar());
	int ans=0;
	for(;'0'<=c&&c<='9';c=GetChar())ans=ans*10+(c-'0');
	return ans;
}
int N,K,H[100000];
int main()
{
//	freopen("klo11c.in","r",stdin);
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	N=GetInt(),K=GetInt();
	for(int i=0;i<N;i++)H[i]=GetInt();
	multimap<int,int>queries;
	if(true)
	{
		SEG.Build(1000000);
		for(int i=0;i<N;i++)
		{
			SEG.Add(H[i],1);
			if(i-K>=0)SEG.Add(H[i-K],-1);
			if(i>=K-1)queries.insert(make_pair(SEG.QueryLoc(SEG.SZ[1]/2+1),i));
		}
	}
	multimap<int,int>sot;
	for(int i=0;i<N;i++)sot.insert(make_pair(H[i],i));
	long long ansc=9223372036854775807LL;
	int ansv=0,ansi=-1;
	if(true)
	{
		static Bit<long long>upon,down;
		static Bit<int>usz,dsz;
		upon.Build(N),down.Build(N),usz.Build(N),dsz.Build(N);
		for(int i=0;i<N;i++)upon.Set(i,H[i]),usz.Set(i,1);
		for(multimap<int,int>::iterator it=sot.begin(),iq=queries.begin();it!=sot.end()&&iq!=queries.end();++it)
		{
			upon.Set(it->second,0),down.Set(it->second,it->first);
			usz.Set(it->second,0),dsz.Set(it->second,1);
			for(;iq!=queries.end()&&iq->first==it->first;++iq)
			{
				const int l=(iq->second)-(K-1),r=(iq->second);
				const long long ta=(upon.QuerySum(l,r)-(long long)usz.QuerySum(l,r)*it->first)+((long long)dsz.QuerySum(l,r)*it->first-down.QuerySum(l,r));
				if(ta<ansc)ansc=ta,ansv=it->first,ansi=l;
			}
		}
	}
	printf("%lld\n",ansc);
	for(int _i=0;_i<K;_i++)
	{
		const int i=ansi+_i;
		ansc-=abs(H[i]-ansv);
		H[i]=ansv;
	}
	for(int i=0;i<N;i++)printf("%d\n",H[i]);
	assert(ansc==0LL);
	return 0;
}
