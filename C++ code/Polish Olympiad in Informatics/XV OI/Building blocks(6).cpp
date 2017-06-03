#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct SegTree
{
	LL *SZ;
	int N;
	void Build(const int id,const int l,const int r,const LL val)
	{
		if(l==r){SZ[id]=val;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid,val),Build(id*2+1,mid+1,r,val);
		SZ[id]=SZ[id*2]+SZ[id*2+1];
	}
	void Build(const int _N,const LL val=0LL)
	{
		N=_N;
		SZ=new LL[N*4];
		Build(1,0,N,val);
	}
	void Add(const int id,const int l,const int r,const int loc,const LL val)
	{
		SZ[id]+=val;
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Add(id*2,l,mid,loc,val);
			else Add(id*2+1,mid+1,r,loc,val);
		}
	}
	void Add(const int loc,const LL val)
	{
		Add(1,0,N,loc,val);
	}
	void Set(const int id,const int l,const int r,const int loc,const LL val)
	{
		if(l==r){SZ[id]=val;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Set(id*2,l,mid,loc,val);
		else Set(id*2+1,mid+1,r,loc,val);
		SZ[id]=SZ[id*2]+SZ[id*2+1];
	}
	void Set(const int loc,const LL val)
	{
		Set(1,0,N,loc,val);
	}
	int QueryLoc(const int id,const int l,const int r,const LL rank)
	{
		assert(1<=rank&&rank<=SZ[id]);
		if(l==r)return r;
		const int mid=(l+r)/2;
		if(rank<=SZ[id*2])return QueryLoc(id*2,l,mid,rank);
		else return QueryLoc(id*2+1,mid+1,r,rank-SZ[id*2]);
	}
	int QueryLoc(const LL rank)
	{
		return QueryLoc(1,0,N,rank);
	}
	LL QuerySum(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return 0LL;
		if(bl<=l&&r<=br)return SZ[id];
		const int mid=(l+r)/2;
		return QuerySum(id*2,l,mid,bl,br)+QuerySum(id*2+1,mid+1,r,bl,br);
	}
	LL QuerySum(const int bl,const int br)
	{
		return QuerySum(1,0,N,bl,br);
	}
}SEG;
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
	LL ansc=INF;
	int ansv=0,ansi=-1;
	if(true)
	{
		static SegTree upon,down,usz,dsz;
		upon.Build(N-1),down.Build(N-1),usz.Build(N-1,1),dsz.Build(N-1);
		for(int i=0;i<N;i++)upon.Set(i,(LL)H[i]);
		for(multimap<int,int>::iterator it=sot.begin(),iq=queries.begin();it!=sot.end()&&iq!=queries.end();++it)
		{
			upon.Set(it->second,0),down.Set(it->second,it->first);
			usz.Set(it->second,0),dsz.Set(it->second,1);
			for(;iq!=queries.end()&&iq->first==it->first;++iq)
			{
				const int l=(iq->second)-(K-1),r=(iq->second);
				const LL ta=(upon.QuerySum(l,r)-usz.QuerySum(l,r)*it->first)+(dsz.QuerySum(l,r)*it->first-down.QuerySum(l,r));
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
