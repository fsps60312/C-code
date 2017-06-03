#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int INF=2147483647,POOL_MAX_SIZE=6000000;
int N,YSZ;
struct Node
{
	int l,r;
	int sz,tag;
	Node(){}
}NODE[POOL_MAX_SIZE];
int CUR=0;
int NewNode(const int _loc,const int _sz)
{
	assert(CUR<POOL_MAX_SIZE);
	Node &o=NODE[CUR];
	o.l=o.r=-1;
	o.tag=_loc;
	o.sz=_sz;
	return CUR++;
}
void Insert(int &id,const int l,const int r,const int loc,const int sz)
{
	assert(l<=loc&&loc<=r);
	if(id==-1)
	{
		id=NewNode(loc,sz);
		return;
	}
	Node &o=NODE[id];
	if(o.tag!=-1)
	{
		if(o.tag==loc){o.sz+=sz;return;}
		const int pre_loc=o.tag,pre_sz=o.sz;
		o.tag=-1,o.sz=0;
		Insert(id,l,r,pre_loc,pre_sz);
	}
	o.sz+=sz;
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)Insert(o.l,l,mid,loc,sz);
		else Insert(o.r,mid+1,r,loc,sz);
//		assert(o.sz==(o->l!=-1?o->l->sz:0)+(o->r!=-1?o->r->sz:0));
	}
}
int SumOfLch(const vector<int>&s,const int l,const int r)
{
	int ans=0;
	for(int i=0;i<(int)s.size();i++)if(s[i]!=-1)
	{
		const int tag=NODE[s[i]].tag;
		if(tag!=-1)
		{
			if(l<=tag&&tag<=r)ans+=NODE[s[i]].sz;
		}
		else
		{
			if(NODE[s[i]].l!=-1)ans+=NODE[NODE[s[i]].l].sz;
		}
	}
	return ans;
}
void MoveToCh(vector<int>&s,const int d,const int l,const int r)
{
	for(int i=0;i<(int)s.size();i++)if(s[i]!=-1)
	{
		const int tag=NODE[s[i]].tag;
		if(tag!=-1)
		{
			if(tag<l||r<tag)s[i]=-1;
		}
		else s[i]=(d==0?NODE[s[i]].l:NODE[s[i]].r);
	}
}
int Query(vector<int>&s,const int l,const int r,const int k)
{
	if(l==r)
	{
		int sum=0;
		for(int i=0;i<(int)s.size();i++)if(s[i]!=-1)sum+=NODE[s[i]].sz;
		return k<=sum?r:INF;
	}
	const int mid=(l+r)/2;
	const int lch_sum=SumOfLch(s,l,mid);
	if(k>lch_sum)
	{
		MoveToCh(s,1,mid+1,r);
		return Query(s,mid+1,r,k-lch_sum);
	}
	else
	{
		MoveToCh(s,0,l,mid);
		return Query(s,l,mid,k);
	}
}
struct SegTree
{
	int S[200001];
	void Build(){for(int i=1;i<=YSZ;i++)S[i]=-1;}
	void Modify(int i,const int val){++i;while(i<=YSZ)Insert(S[i],0,N-1,val,1),i+=(i&(-i));}
	int Query(int i,const int k)
	{
		++i;
		static vector<int>data;data.clear();
		while(i)data.push_back(S[i]),i-=(i&(-i));
		return ::Query(data,0,N-1,k);
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
//	freopen("lam11a.in","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		ReadInput();
		Discretize();
		sort(L,L+N,CmpX);
		SEG.Build();
		static int ans[200000];
		if(Y1*X2-X1*Y2==0LL)
		{
//			puts("a");
			int o=-1;
			for(int i=0;i<N;i++)
			{
				if(i&&L[i-1].X!=L[i].X)o=-1;
				static vector<int>os;os.clear();
				os.push_back(o);
				int &a=ans[L[i].ID]=Query(os,0,N-1,L[i].K);
				if(L[i].ID<a)a=L[i].ID;
				Insert(o,0,N-1,a,1);
			}
		}
		else
		{
//			puts("b");
			for(int i=0;i<N;i++)
			{
				int &a=ans[L[i].ID]=SEG.Query((int)L[i].Y,L[i].K);
				if(L[i].ID<a)a=L[i].ID;
				SEG.Modify((int)L[i].Y,a);
			}
		}
//		printf("CUR=%d\n",CUR);return 0;
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
}
