#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct SegTree
{
	int S[800000];
	void Build(const int id,const int l,const int r)
	{
		S[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Modify(const int id,const int l,const int r,const int loc)
	{
		++S[id];
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Modify(id*2,l,mid,loc);
			else Modify(id*2+1,mid+1,r,loc); 
		}
	}
	int Query(const int id,const int l,const int r,const int k)
	{
		if(l==r)return k<=S[id]?r:INF;
		const int mid=(l+r)/2;
		if(k>S[id*2])return Query(id*2+1,mid+1,r,k-S[id*2]);
		else return Query(id*2,l,mid,k);
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
int N,YSZ,ANS[200000];
struct Bit
{
	int S[200001];
	void Build(){for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i){++i;while(i<=N)++S[i],i+=(i&(-i));}
	int Query(int i,const int v){++i;int ans=0;while(i)ans+=S[i],i-=(i&(-i));return ans;}
}BIT;
void Solve(const int l,const int r)
{
	if(l==r)return;
	const int mid=(l+r)/2;
	Solve(l,mid);
	
	Solve(mid+1,r);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		ReadInput();
		Discretize();
		sort(L,L+N,CmpX);
		for(int i=0;i<N;i++)ANS[i]=i;
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
			SEG.Build(1,0,N-1);
			Solve(0,N-1);
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
