#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Bit
{
	int S[200002],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i,const int val){for(;i<=N;i+=(i&(-i)))S[i]+=val;}
	int Query(int i){int ans=0;for(;i;i-=(i&(-i)))ans+=S[i];return ans;}
};
struct Point
{
	int X,Y;
	Point(){}
	Point(const int _X,const int _Y):X(_X),Y(_Y){}
};
struct QueryType
{
	int a,b1,b2,*p;
	QueryType(){}
	QueryType(const int _a,const int _b1,const int _b2,int *_p):a(_a),b1(_b1),b2(_b2),p(_p){}
};
void Inverse(multimap<int,int>&s)
{
	int mn=INF;
	for(multimap<int,int>::const_iterator it=s.begin();it!=s.end();++it)getmin(mn,-it->first);
	multimap<int,int>ans;
	for(multimap<int,int>::const_iterator it=s.begin();it!=s.end();++it)
	{
		pair<int,int>p=make_pair(it->first,it->second);
		(p.first*=-1)-=mn;
		ans.insert(p);
	}
	s.swap(ans);
}
void Inverse(vector<QueryType>&s)
{
	int mn=INF;
	for(int i=0;i<(int)s.size();i++)getmin(mn,s[i].a*=-1);
	for(int i=0;i<(int)s.size();i++)s[i].a-=mn;
}
void Solve(multimap<int,int>&s,vector<QueryType>&queries)
{
	
	assert(0);
}
int N;
Point P[100000];
vector<QueryType>UPON,DOWN,LEFT,RIGT,VEUR,VEDR,HOUR,HODR;
void Solve()
{
	multimap<int,int>s;
	if(true)
	{
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].Y,P[i].X));
		Solve(s,DOWN);
		Inverse(s),Inverse(UPON);
		Solve(s,UPON);
	}
	if(true)
	{ 
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].X,P[i].Y));
		Solve(s,LEFT);
		Inverse(s),Inverse(RIGT);
		Solve(s,RIGT);
	}
	if(true)
	{
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].X,P[i].X+P[i].Y));
//		Solve(s,)
		assert(0);
	}
	assert(0);
}
int ANS[100000][4],W,H;
vector<int>X,Y;
void Discretize()
{
	X.clear();
	for(int i=0;i<N;i++)X.push_back(P[i].X);
	sort(X.begin(),X.end()),X.resize(W=(int)(unique(X.begin(),X.end())-X.begin()));
	for(int i=0;i<N;i++)P[i].X=(int)(lower_bound(X.begin(),X.end(),P[i].X)-X.begin());
	Y.clear();
	for(int i=0;i<N;i++)Y.push_back(P[i].Y);
	sort(Y.begin(),Y.end()),Y.resize(H=(int)(unique(Y.begin(),Y.end())-Y.begin()));
	for(int i=0;i<N;i++)P[i].Y=(int)(lower_bound(Y.begin(),Y.end(),P[i].Y)-Y.begin());
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("str1.in","r",stdin);
	for(int querycount;scanf("%d%d%d%d",&W,&H,&N,&querycount)==4;)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&P[i].X,&P[i].Y);
		Discretize();
		UPON.clear(),DOWN.clear(),LEFT.clear(),RIGT.clear(),VEUR.clear(),VEDR.clear(),HOUR.clear(),HODR.clear();
		for(int i=0;i<querycount;i++)
		{
			static Point a,b;
			scanf("%d%d%d%d",&a.X,&a.Y,&b.X,&b.Y);
			for(int j=0;j<4;j++)ANS[i][j]=0;
			int *ans1=&ANS[i][0],*ans2=&ANS[i][2];
			if(!(a.X<b.X||(a.X==b.X&&a.Y<b.Y)))swap(a,b),swap(ans1,ans2);
			if(a.X==b.X)
			{
				assert(a.Y<b.Y);
				if(true)
				{
					const int mid=(int)(lower_bound(Y.begin(),Y.end(),Y[a.Y]+(Y[b.Y]-Y[a.Y]+1)/2)-Y.begin())-1;
					DOWN.push_back(QueryType(mid,0,W-1,ans1));
				}
				if(true)
				{
					const int mid=(int)(upper_bound(Y.begin(),Y.end(),Y[a.Y]+(Y[b.Y]-Y[a.Y])/2)-Y.begin());
					UPON.push_back(QueryType(mid,0,W-1,ans2));
				}
			}
			else if(a.Y==b.Y)
			{
				assert(a.X<b.X);
				if(true)
				{
					const int mid=(int)(lower_bound(X.begin(),X.end(),X[a.X]+(X[b.X]-X[a.X]+1)/2)-X.begin())-1;
					LEFT.push_back(QueryType(mid,0,H-1,ans1));
				}
				if(true)
				{
					const int mid=(int)(upper_bound(X.begin(),X.end(),X[a.X]+(X[b.X]-X[a.X])/2)-X.begin());
					RIGT.push_back(QueryType(mid,0,H-1,ans2));
				}
			}
			else if(b.Y-a.Y==b.X-a.X)
			{
				if(true)
				{
					VEUR.push_back(QueryType(1,,,ans1));
					
				}
				if(true)
				{
					VEUR.push_back(QueryType(1,,,ans2));
				}
				assert(0);
			}
			else if(a.Y-b.Y==b.X-a.X)
			{
				assert(0);
			}
			else assert(0);
		}
		Solve();
		for(int i=0;i<querycount;i++)
		{
			const int ans1=ANS[i][0]-ANS[i][1],ans2=ANS[i][2]-ANS[i][3];
			printf("%d %d %d\n",ans1,ans2,N-ans1-ans2);
		}
	}
	return 0;
}
