#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int INF=2147483647;
int N,YSZ;
struct Node
{
	Node *l,*r;
	int sz;
	Node(const int _sz):l(NULL),r(NULL),sz(_sz){}
};
void Insert(Node* &o,const int l,const int r,const int loc)
{
	assert(l<=loc&&loc<=r);
	if(!o)o=new Node(0);
	++o->sz;
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)Insert(o->l,l,mid,loc);
		else Insert(o->r,mid+1,r,loc);
		assert(o->sz==(o->l?o->l->sz:0)+(o->r?o->r->sz:0));
	}
}
int SumOfLch(const vector<Node*>&s)
{
	int ans=0;
	for(int i=0;i<(int)s.size();i++)if(s[i]&&s[i]->l)ans+=s[i]->l->sz;
	return ans;
}
void MoveToCh(vector<Node*>&s,const int d)
{
	for(int i=0;i<(int)s.size();i++)if(s[i])s[i]=(d==0?s[i]->l:s[i]->r);
}
int Query(vector<Node*>&s,const int l,const int r,const int k)
{
	if(l==r)
	{
		int sum=0;
		for(int i=0;i<(int)s.size();i++)if(s[i])sum+=s[i]->sz;
		return k<=sum?r:INF;
	}
	const int lch_sum=SumOfLch(s);
	const int mid=(l+r)/2;
	if(k>lch_sum)
	{
		MoveToCh(s,1);
		return Query(s,mid+1,r,k-lch_sum);
	}
	else
	{
		MoveToCh(s,0);
		return Query(s,l,mid,k);
	}
}
struct SegTree
{
	Node *S[200001];
	void Build(){for(int i=1;i<=YSZ;i++)S[i]=NULL;}
	void Modify(int i,const int val){++i;while(i<=YSZ)Insert(S[i],0,N-1,val),i+=(i&(-i));}
	int Query(int i,const int k)
	{
		++i;
		vector<Node*>data;
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
	while(scanf("%d",&N)==1)
	{
		ReadInput();
		Discretize();
		sort(L,L+N,CmpX);
		SEG.Build();
		static int ans[200000];
		if(Y1*X2-X1*Y2==0LL)
		{
			Node *o=NULL;
			for(int i=0;i<N;i++)
			{
				if(i&&L[i-1].X!=L[i].X)o=NULL;
				vector<Node*>os;
				os.push_back(o);
				int &a=ans[L[i].ID]=Query(os,0,N-1,L[i].K);
				if(L[i].ID<a)a=L[i].ID;
				Insert(o,0,N-1,a);
			}
		}
		else
		{
			for(int i=0;i<N;i++)
			{
				int &a=ans[L[i].ID]=SEG.Query((int)L[i].Y,L[i].K);
				if(L[i].ID<a)a=L[i].ID;
				SEG.Modify((int)L[i].Y,a);
			}
		}
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
}
