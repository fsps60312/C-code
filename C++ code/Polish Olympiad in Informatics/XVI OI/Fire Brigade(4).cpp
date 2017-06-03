#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
const int INF=2147483647;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
template<class T>inline void getmax(T &a,const T &b){if(a<b)a=b;}
struct Bit
{
	int S[200002],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i,const int val){++i;for(;i<=N;i+=(i&(-i)))S[i]+=val;}
	int Query(int i){int ans=0;for(++i;i;i-=(i&(-i)))ans+=S[i];return ans;}
};
struct Point
{
	int X,Y,UR,DR;
	void Build(){UR=X+Y,DR=X-Y;}
};
struct QueryType
{
	int a,b1,b2,*p;
	QueryType(){}
	QueryType(const int _a,const int _b1,const int _b2,int *_p):a(_a),b1(_b1),b2(_b2),p(_p){}
};
bool operator<(const QueryType &a,const QueryType &b){return a.a<b.a;}
int LBound(const vector<int>&s,const int val){return (int)(lower_bound(s.begin(),s.end(),val)-s.begin());}
int UBound(const vector<int>&s,const int val){return (int)(upper_bound(s.begin(),s.end(),val)-s.begin());}
void Inverse(multimap<int,int>&s)
{
	multimap<int,int>ans;
	for(multimap<int,int>::const_iterator it=s.begin();it!=s.end();++it)ans.insert(make_pair(-it->first,it->second));
	s.swap(ans);
}
void Inverse(vector<QueryType>&s){for(int i=0;i<(int)s.size();i++)s[i].a*=-1;}
void Solve(const int n,const multimap<int,int>&s,const vector<QueryType>&queries)
{
	if(queries.empty())return;
	printf("Point:");for(multimap<int,int>::const_iterator it=s.begin();it!=s.end();it++)printf("(%d,%d)",it->first,it->second);puts("");
	printf("Query:");for(int i=0;i<(int)queries.size();i++)printf("(%d,%d,%d)",queries[i].a,queries[i].b1,queries[i].b2);puts("");
	static Bit bit;
	bit.Clear(n);
	multimap<int,int>::const_iterator it=s.begin();
	for(int i=0;i<(int)queries.size();i++)
	{
		const QueryType &q=queries[i];
		for(;it!=s.end()&&it->first<=q.a;++it)bit.Add(it->second,1);
		(*q.p)+=bit.Query(q.b2)-bit.Query(q.b1-1);
	}
}
void Solve(multimap<int,int>&s,vector<QueryType>&queries)
{
	int mn=INF,mx=-INF;
	for(multimap<int,int>::const_iterator it=s.begin();it!=s.end();++it)getmin(mn,it->second),getmax(mx,it->second);
	for(int i=0;i<(int)queries.size();i++)
	{
//		printf("(%d,%d)\n",queries[i].b1,queries[i].b2);
		assert(queries[i].b1<=queries[i].b2+1),getmin(mn,queries[i].b1),getmax(mx,queries[i].b2);
	}
	for(multimap<int,int>::iterator it=s.begin();it!=s.end();++it)it->second-=mn;
	for(int i=0;i<(int)queries.size();i++)queries[i].b1-=mn,queries[i].b2-=mn;
	mx-=mn;
	sort(queries.begin(),queries.end());
	Solve(mx+1,s,queries);
}
int N;
Point P[100000];
vector<QueryType>UPON,DOWN,LEFT,RIGT,VEUR,VEDR,HOUR,HODR;
void Solve()
{
	multimap<int,int>s;
	if(true)
	{
		puts("UD");
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].Y,P[i].X));
		Solve(s,DOWN);
		Inverse(s),Inverse(UPON);
		Solve(s,UPON);
	}
	if(true)
	{
		puts("LR");
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].X,P[i].Y));
		Solve(s,LEFT);
		Inverse(s),Inverse(RIGT);
		Solve(s,RIGT);
	}
	if(true)
	{
		puts("VE");
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].X,P[i].X+P[i].Y));
		Solve(s,VEUR);
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].X,P[i].X-P[i].Y));
		Solve(s,VEDR);
	}
	if(true)
	{
		puts("HO");
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].Y,P[i].X+P[i].Y));
		Solve(s,HOUR);
		s.clear();
		for(int i=0;i<N;i++)s.insert(make_pair(P[i].Y,P[i].X-P[i].Y));
		Solve(s,HODR);
	}
}
int ANS[100000][4];
vector<int>X,Y,UR,DR;
void Discretize()
{
	X.clear();
	for(int i=0;i<N;i++)X.push_back(P[i].X);
	sort(X.begin(),X.end()),X.resize(unique(X.begin(),X.end())-X.begin());
	for(int i=0;i<N;i++)P[i].X=(int)(lower_bound(X.begin(),X.end(),P[i].X)-X.begin());
	Y.clear();
	for(int i=0;i<N;i++)Y.push_back(P[i].Y);
	sort(Y.begin(),Y.end()),Y.resize(unique(Y.begin(),Y.end())-Y.begin());
	for(int i=0;i<N;i++)P[i].Y=(int)(lower_bound(Y.begin(),Y.end(),P[i].Y)-Y.begin());
	UR.clear();
	for(int i=0;i<N;i++)UR.push_back(P[i].UR);
	sort(UR.begin(),UR.end()),UR.resize(unique(UR.begin(),UR.end())-UR.begin());
	for(int i=0;i<N;i++)P[i].UR=(int)(lower_bound(UR.begin(),UR.end(),P[i].UR)-UR.begin());
	DR.clear();
	for(int i=0;i<N;i++)DR.push_back(P[i].DR);
	sort(DR.begin(),DR.end()),DR.resize(unique(DR.begin(),DR.end())-DR.begin());
	for(int i=0;i<N;i++)P[i].DR=(int)(lower_bound(DR.begin(),DR.end(),P[i].DR)-DR.begin());
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("str1.in","r",stdin);
	for(int querycount,___useless1,___useless2;scanf("%d%d%d%d",&___useless1,&___useless2,&N,&querycount)==4;)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&P[i].X,&P[i].Y);
		Discretize();
		UPON.clear(),DOWN.clear(),LEFT.clear(),RIGT.clear(),VEUR.clear(),VEDR.clear(),HOUR.clear(),HODR.clear();
		for(int i=0;i<querycount;i++)
		{
			static Point a,b;
			scanf("%d%d%d%d",&a.X,&a.Y,&b.X,&b.Y);
			a.Build(),b.Build();
			for(int j=0;j<4;j++)ANS[i][j]=0;
			int *ans1=&ANS[i][0],*ans2=&ANS[i][2];
			if(!(a.X<b.X||(a.X==b.X&&a.Y<b.Y)))swap(a,b),swap(ans1,ans2);
			if(a.X==b.X)
			{
				assert(a.Y<b.Y);
				if(true)
				{
					const int mid=LBound(Y,Y[a.Y]+(Y[b.Y]-Y[a.Y]+1)/2)-1;
					DOWN.push_back(QueryType(mid,0,(int)X.size()-1,ans1));
				}
				if(true)
				{
					const int mid=UBound(Y,Y[a.Y]+(Y[b.Y]-Y[a.Y])/2);
					UPON.push_back(QueryType(mid,0,(int)X.size()-1,ans2));
				}
			}
			else if(a.Y==b.Y)
			{
				assert(a.X<b.X);
				if(true)
				{
					const int mid=LBound(X,X[a.X]+(X[b.X]-X[a.X]+1)/2)-1;
					printf("(%d,%d),mid=%d=%d\n",X[a.X],X[b.X],mid,X[mid]);
					LEFT.push_back(QueryType(mid,0,(int)Y.size()-1,ans1));
				}
				if(true)
				{
					const int mid=UBound(X,X[a.X]+(X[b.X]-X[a.X])/2);
					RIGT.push_back(QueryType(mid,0,(int)Y.size()-1,ans2));
				}
			}
			else if(a.DR==b.DR)//vector(a,b): ¡ù 
			{
				assert(a.UR<b.UR&&a.X<b.X&&a.Y<b.Y);
				if(true)
				{
					const int mid=LBound(UR,UR[a.UR]+(UR[b.UR]-UR[a.UR]+1)/2)-1;
					VEUR.push_back(QueryType(b.Y-1,0,mid,ans1));
					VEUR.push_back(QueryType(a.Y,0,mid,ans1+1));
					DOWN.push_back(QueryType(a.Y,0,b.X-1,ans1));
				}
				if(true)
				{
					const int mid=UBound(UR,UR[a.UR]+(UR[b.UR]-UR[a.UR])/2);
					UPON.push_back(QueryType(b.Y,a.X+1,(int)X.size()-1,ans2));
					VEUR.push_back(QueryType(b.Y-1,mid,(int)UR.size()-1,ans2));
					VEUR.push_back(QueryType(a.Y,mid,(int)UR.size()-1,ans2+1));
				}
			}
			else if(a.UR==b.UR)//vector(a,b): ¡û 
			{
				assert(a.DR<b.DR&&a.X<b.X&&a.Y>b.Y);
				if(true)
				{
					const int mid=LBound(DR,DR[a.DR]+(DR[b.DR]-DR[a.DR]+1)/2)-1;
					UPON.push_back(QueryType(a.Y,0,b.X-1,ans1));
					VEDR.push_back(QueryType(a.Y-1,0,mid,ans1));
					VEDR.push_back(QueryType(b.Y,0,mid,ans1+1));
				}
				if(true)
				{
					const int mid=UBound(DR,DR[a.DR]+(DR[b.DR]-DR[a.DR])/2);
					VEDR.push_back(QueryType(a.Y-1,mid,(int)DR.size()-1,ans2));
					VEDR.push_back(QueryType(b.Y,mid,(int)DR.size()-1,ans2+1));
					DOWN.push_back(QueryType(b.Y,a.X+1,(int)X.size()-1,ans2));
				}
			}
			else if(b.X-a.X<b.Y-a.Y)
			{
				assert(a.X<b.X&&a.Y<b.Y);
				if(true)
				{
					const int ur=UR[a.UR]+(UR[b.UR]-UR[a.UR]+1)/2-1;
					const int mid=UBound(UR,ur)-1;
					RIGT.push_back(QueryType(b.X,0,UBound(Y,ur-X[b.X])-1,ans1));
					HOUR.push_back(QueryType(b.X-1,0,mid,ans1));
					HOUR.push_back(QueryType(a.X,0,mid,ans1+1));
					LEFT.push_back(QueryType(a.X,0,UBound(Y,ur-X[a.X])-1,ans1));
				}
				if(true)
				{
					const int ur=UR[a.UR]+(UR[b.UR]-UR[a.UR])/2;
					const int mid=UBound(UR,ur);
					RIGT.push_back(QueryType(b.X,UBound(Y,ur-X[b.X]),(int)Y.size()-1,ans1));
					HOUR.push_back(QueryType(b.X-1,mid,(int)UR.size()-1,ans1));
					HOUR.push_back(QueryType(a.X,mid,(int)UR.size()-1,ans1+1));
					LEFT.push_back(QueryType(a.X,UBound(Y,ur-X[a.X]),(int)Y.size()-1,ans1));
				}
			}
			else if(b.Y-a.Y<a.X-b.X)
			{
				assert(a.X<b.X&&a.Y>b.Y);
				if(true)
				{
					const int dr=DR[a.DR]+(DR[b.DR]-DR[a.DR]+1)/2-1;
					const int mid=UBound(DR,dr)-1;
					RIGT.push_back(QueryType(b.X,LBound(Y,X[b.X]-dr),(int)Y.size(),ans1));
					HODR.push_back(QueryType(b.X-1,0,mid,ans1));
					HODR.push_back(QueryType(a.X,0,mid,ans1+1));
					LEFT.push_back(QueryType(a.X,LBound(Y,X[a.X]-dr),(int)Y.size(),ans1));
				}
				if(true)
				{
					const int dr=DR[a.DR]+(DR[b.DR]-DR[a.DR])/2;
					const int mid=UBound(DR,dr);
					RIGT.push_back(QueryType(b.X,0,LBound(Y,X[b.X]-dr)-1,ans1));
					HODR.push_back(QueryType(b.X-1,mid,(int)DR.size()-1,ans1));
					HODR.push_back(QueryType(a.X,mid,(int)DR.size()-1,ans1+1));
					LEFT.push_back(QueryType(a.X,0,LBound(Y,X[a.X]-dr)-1,ans1));
				}
			}
			else if(0<b.Y-a.Y&&b.Y-a.Y<b.X-a.X)
			{
				assert(a.X<b.X&&a.Y<b.Y);
				if(true)
				{
					const int ur=UR[a.UR]+(UR[b.UR]-UR[a.UR]+1)/2-1;
					const int mid=UBound(UR,ur)-1;
					UPON.push_back(QueryType(b.Y,0,UBound(X,ur-Y[b.Y])-1,ans1));
					VEUR.push_back(QueryType(b.Y-1,0,mid,ans1));
					VEUR.push_back(QueryType(a.Y,0,mid,ans1+1));
					DOWN.push_back(QueryType(a.Y,0,UBound(X,ur-Y[a.Y])-1,ans1));
				}
				if(true)
				{
					const int ur=UR[a.UR]+(UR[b.UR]-UR[a.UR])/2;
					const int mid=UBound(UR,ur);
					UPON.push_back(QueryType(b.Y,UBound(X,ur-Y[b.Y]),(int)Y.size()-1,ans1));
					VEUR.push_back(QueryType(b.Y-1,mid,(int)UR.size()-1,ans1));
					VEUR.push_back(QueryType(a.Y,mid,(int)UR.size()-1,ans1+1));
					DOWN.push_back(QueryType(a.Y,UBound(X,ur-Y[a.Y]),(int)Y.size()-1,ans1));
				}
			}
			else if(a.X-b.X<b.Y-a.Y&&b.Y-a.Y<0)
			{
				assert(a.X<b.X&&a.Y>b.Y);
				if(true)
				{
					const int dr=DR[a.DR]+(DR[b.DR]-DR[a.DR]+1)/2-1;
					const int mid=UBound(DR,dr)-1;
					UPON.push_back(QueryType(a.Y,0,UBound(X,dr+Y[a.Y])-1,ans1));
					VEDR.push_back(QueryType(a.Y-1,0,mid,ans1));
					VEDR.push_back(QueryType(b.Y,0,mid,ans1+1));
					DOWN.push_back(QueryType(b.Y,0,UBound(X,dr+Y[b.Y])-1,ans1));
				}
				if(true)
				{
					const int dr=DR[a.DR]+(DR[b.DR]-DR[a.DR])/2;
					const int mid=UBound(DR,dr);
					UPON.push_back(QueryType(a.Y,UBound(X,dr+Y[a.Y]),(int)X.size()-1,ans1));
					VEDR.push_back(QueryType(a.Y-1,mid,(int)DR.size()-1,ans1));
					VEDR.push_back(QueryType(b.Y,mid,(int)DR.size()-1,ans1+1));
					DOWN.push_back(QueryType(b.Y,UBound(X,dr+Y[b.Y]),(int)X.size()-1,ans1));
				}
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
