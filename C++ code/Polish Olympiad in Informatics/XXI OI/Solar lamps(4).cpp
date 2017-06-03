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
//		printf("loc=%d,sum=%d,k=%d\n",r,sum,k);
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
	Node *S[800000];
	void Build(const int id,const int l,const int r)
	{
		S[id]=NULL;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(){Build(1,0,YSZ-1);}
	void Modify(const int id,const int l,const int r,const int loc,const int val)
	{
		assert(l<=loc&&loc<=r);
		Insert(S[id],0,N-1,val);
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Modify(id*2,l,mid,loc,val);
			else Modify(id*2+1,mid+1,r,loc,val);
		}
	}
	void Modify(const int loc,const int val){Modify(1,0,YSZ-1,loc,val);}
	void GetQueryData(const int id,const int l,const int r,const int bl,const int br,vector<Node*>&ans)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){ans.push_back(S[id]);return;}
		const int mid=(l+r)/2;
		GetQueryData(id*2,l,mid,bl,br,ans);
		GetQueryData(id*2+1,mid+1,r,bl,br,ans);
	}
	int Query(const int loc,const int k)
	{
		vector<Node*>data;
		GetQueryData(1,0,YSZ-1,0,loc,data);
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
	//Y1x-X1y
	const bool flip1=(Y1*X2-X1*Y2<0LL),flip2=(Y2*X1-X2*Y1<0LL);
//	printf("Cross=%lld\n",Y1*X2-X1*Y2);
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
//		for(int i=0;i<N;i++)printf("id=%d,(%d,%d)\n",i+1,(int)L[i].X,(int)L[i].Y);
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
//				printf("id=%d,a=%d\n",L[i].ID+1,a+1);
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
