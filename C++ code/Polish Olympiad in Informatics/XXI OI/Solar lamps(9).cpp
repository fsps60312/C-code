#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
typedef long long LL;
const int INF=2147483647,POOL_MAX_SIZE=20000000;
int N,YSZ;
struct Node
{
	int lch,younger_brother;
	int sz;
	Node(){}
}NODE[POOL_MAX_SIZE];
int CUR=0;
inline int NewNode(const int _sz)
{
	assert(CUR<POOL_MAX_SIZE);
	Node &o=NODE[CUR];
	o.lch=o.younger_brother=-1;
	o.sz=_sz;
	return CUR++;
}
inline int SizeOf(const int id){return id==-1?0:NODE[id].sz;}
void InsertOnRch(int &id,const int sz,const int l,const int r,const int loc);
void InsertOnLch(int &id,const int l,const int r,const int loc)
{
	assert(l<=loc&&loc<=r);
	if(id==-1)id=NewNode(0);
	Node &o=NODE[id];
	++o.sz;
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)InsertOnLch(o.lch,l,mid,loc);
		else InsertOnRch(o.lch,o.sz-SizeOf(o.lch),mid+1,r,loc);
//		assert(o.sz==(o->l!=-1?o->l->sz:0)+(o->r!=-1?o->r->sz:0));
	}
}
void InsertOnRch(int &id,const int sz,const int l,const int r,const int loc)
{
	assert(l<=loc&&loc<=r);
	if(id==-1)id=NewNode(0);
	Node &o=NODE[id];
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)InsertOnLch(o.younger_brother,l,mid,loc);
		else InsertOnRch(o.younger_brother,sz-SizeOf(o.younger_brother),mid+1,r,loc);
//		assert(o.sz==(o->l!=-1?o->l->sz:0)+(o->r!=-1?o->r->sz:0));
	}
}
int SumOfLchOnLch(const vector<pair<int,int> >&s)
{
	int ans=0;
	for(int i=0;i<(int)s.size();i++)if(s[i].first!=-1)ans+=SizeOf(NODE[s[i].first].lch);
	return ans;
}
int SumOfLchOnRch(const vector<pair<int,int> >&s)
{
	int ans=0;
	for(int i=0;i<(int)s.size();i++)if(s[i].first!=-1)ans+=SizeOf(NODE[s[i].first].younger_brother);
	return ans;
}
void MoveToLchOnLch(vector<pair<int,int> >&s)
{
	for(int i=0;i<(int)s.size();i++)if(s[i].first!=-1)
	{
		const int ch=NODE[s[i].first].lch;
		s[i]=make_pair(ch,SizeOf(ch));
	}
}
void MoveToRchOnLch(vector<pair<int,int> >&s)
{
	for(int i=0;i<(int)s.size();i++)if(s[i].first!=-1)
	{
		int &ch=NODE[s[i].first].lch;
		if(ch==-1)ch=NewNode(0);
		s[i]=make_pair(ch,NODE[s[i].first].sz-NODE[ch].sz);
	}
}
void MoveToLchOnRch(vector<pair<int,int> >&s)
{
	for(int i=0;i<(int)s.size();i++)if(s[i].first!=-1)
	{
		const int ch=NODE[s[i].first].younger_brother;
		s[i]=make_pair(ch,SizeOf(ch));
	}
}
void MoveToRchOnRch(vector<pair<int,int> >&s)
{
	for(int i=0;i<(int)s.size();i++)if(s[i].first!=-1)
	{
		int &ch=NODE[s[i].first].younger_brother;
		if(ch==-1)ch=NewNode(0);
		s[i]=make_pair(ch,s[i].second-NODE[ch].sz);
	}
}
int QueryOnRch(vector<pair<int,int> >&s,const int l,const int r,const int k);
int QueryOnLch(vector<pair<int,int> >&s,const int l,const int r,const int k)
{
	if(l==r)
	{
		int sum=0;
		for(int i=0;i<(int)s.size();i++)sum+=s[i].second;
		return k<=sum?r:INF;
	}
	const int lch_sum=SumOfLchOnLch(s);
	const int mid=(l+r)/2;
	if(k>lch_sum)
	{
		MoveToRchOnLch(s);
		return QueryOnRch(s,mid+1,r,k-lch_sum);
	}
	else
	{
		MoveToLchOnLch(s);
		return QueryOnLch(s,l,mid,k);
	}
}
int QueryOnRch(vector<pair<int,int> >&s,const int l,const int r,const int k)
{
	if(l==r)
	{
		int sum=0;
		for(int i=0;i<(int)s.size();i++)sum+=s[i].second;
		return k<=sum?r:INF;
	}
	const int lch_sum=SumOfLchOnRch(s);
	const int mid=(l+r)/2;
	if(k>lch_sum)
	{
		MoveToRchOnRch(s);
		return QueryOnRch(s,mid+1,r,k-lch_sum);
	}
	else
	{
		MoveToLchOnRch(s);
		return QueryOnLch(s,l,mid,k);
	}
}
struct SegTree
{
	int S[200001];
	void Build(){for(int i=1;i<=YSZ;i++)S[i]=-1;}
	void Modify(int i,const int val){++i;while(i<=YSZ)InsertOnLch(S[i],0,N-1,val),i+=(i&(-i));}
	int Query(int i,const int k)
	{
		++i;
		static vector<pair<int,int> >data;data.clear();
		while(i)data.push_back(make_pair(S[i],SizeOf(S[i]))),i-=(i&(-i));
		return ::QueryOnLch(data,0,N-1,k);
	}
}SEG;
struct Lamp
{
	int ID,K;
	LL X,Y;
	Lamp(){}
	Lamp(const int _ID,const LL _X,const LL _Y):ID(_ID),X(_X),Y(_Y){}
};
LL X1,Y1,X2,Y2;
Lamp L[200000];
void ReadInput()
{
	scanf("%lld%lld%lld%lld",&X1,&Y1,&X2,&Y2);
	const bool flip1=(Y1*X2-X1*Y2<0LL),flip2=(Y2*X1-X2*Y1<0LL);
	for(int i=0;i<N;i++)
	{
		static LL x,y;
		scanf("%lld%lld",&x,&y);
		if(Y1*X2-X1*Y2==0LL)L[i]=Lamp(i,Y1*x-X1*y,X1*x+Y1*y);
		else L[i]=Lamp(i,(flip1?-1:1)*(Y1*x-X1*y),(flip2?-1:1)*(Y2*x-X2*y));
	}
	for(int i=0;i<N;i++)scanf("%d",&L[i].K);
}
void Discretize()
{
	vector<LL>v;
	for(int i=0;i<N;i++)v.push_back(L[i].X);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	for(int i=0;i<N;i++)L[i].X=lower_bound(v.begin(),v.end(),L[i].X)-v.begin();
	v.clear();
	for(int i=0;i<N;i++)v.push_back(L[i].Y);
	sort(v.begin(),v.end()),v.resize(YSZ=(int)(unique(v.begin(),v.end())-v.begin()));
	for(int i=0;i<N;i++)L[i].Y=lower_bound(v.begin(),v.end(),L[i].Y)-v.begin();
}
bool CmpX(const Lamp &a,const Lamp &b){return a.X!=b.X?a.X<b.X:a.Y<b.Y;}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("lam11a.in","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		ReadInput();
		Discretize();
		sort(L,L+N,CmpX);
		static int ans[200000];
		if(Y1*X2-X1*Y2==0LL)
		{
			puts("a");
			int o=-1;
			for(int i=0;i<N;i++)
			{
				CUR=0;
				if(i&&L[i-1].X!=L[i].X)o=-1;
				static vector<pair<int,int> >os;os.clear();
				os.push_back(make_pair(o,SizeOf(o)));
				int &a=ans[L[i].ID]=QueryOnLch(os,0,N-1,L[i].K);
				if(L[i].ID<a)a=L[i].ID;
				InsertOnLch(o,0,N-1,a);
			}
		}
		else
		{
			puts("b");
			SEG.Build();
			CUR=0;
			for(int i=0;i<N;i++)
			{
				int &a=ans[L[i].ID]=SEG.Query((int)L[i].Y,L[i].K);
				if(L[i].ID<a)a=L[i].ID;
				SEG.Modify((int)L[i].Y,a);
			}
		}
		printf("CUR=%d\n",CUR);return 0;
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
}
