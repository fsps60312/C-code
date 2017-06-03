#include<cstdio>
#include<vector>
#include<stack>
//#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
void getmin(int &a,const int b){if(b<a)a=b;}
struct Pair
{
	LL x,y;
	Pair(){}
	Pair(const LL _x,const LL _y):x(_x),y(_y){}
	Pair operator-(const Pair &p)const{return Pair(x-p.x,y-p.y);}
};
struct Segment
{
	Pair a,b;
	Segment(){}
	Segment(const Pair &_a,const Pair &_b):a(_a),b(_b){}
//	void Print()const{printf("(%d,%d)(%d,%d)",a.x,a.y,b.x,b.y);}
}SEGMENT[1000][2];
LL Cross(const Pair &a,const Pair &b){return a.x*b.y-b.x*a.y;}
int Direction(const Pair &a,const Pair &b)
{
	const LL ans=Cross(a,b);
	if(ans<0LL)return -1;
	else if(ans>0LL)return 1;
	else return 0;
}
int Direction(const Pair &o,const Pair &a,const Pair &b){return Direction(a-o,b-o);}
bool AtRange(const int o,const int a,const int b){return (a<=o&&o<=b)||(b<=o&&o<=a);}
bool AtRange(const Pair &o,const Segment &s){return AtRange(o.x,s.a.x,s.b.x)&&AtRange(o.y,s.a.y,s.b.y);}
bool Intersect(const Segment &a,const Segment &b)
{
	const int d1=Direction(a.a,a.b,b.a),
			  d2=Direction(a.a,a.b,b.b),
			  d3=Direction(b.a,b.b,a.a),
			  d4=Direction(b.a,b.b,a.b);
	if(d1*d2<0&&d3*d4<0)return true;
	if(d1==0&&AtRange(b.a,a))return true;
	if(d2==0&&AtRange(b.b,a))return true;
	if(d3==0&&AtRange(a.a,b))return true;
	if(d4==0&&AtRange(a.b,b))return true;
	return false;
}
struct SolverSCC
{
	vector<int>ET[2000];
	int PRE[2000],LOW[2000],PRE_CNT,SCC[2000],SCC_CNT;
	void clear(const int n){for(int i=0;i<n;i++)ET[i].clear(),PRE[i]=0,SCC[i]=-1;PRE_CNT=SCC_CNT=0;}
	void AddEdge(const int a,const int b){ET[a].push_back(b),ET[b^1].push_back(a^1);}
	stack<int>STK;
	void Dfs(const int u)
	{
		PRE[u]=LOW[u]=++PRE_CNT;
		STK.push(u);
		for(const int nxt:ET[u])
		{
			if(!PRE[nxt])
			{
				Dfs(nxt);
				getmin(LOW[u],LOW[nxt]);
			}
			else if(SCC[nxt]==-1)getmin(LOW[u],PRE[nxt]);
		}
		if(LOW[u]==PRE[u])
		{
			for(;;)
			{
				const int v=STK.top();STK.pop();
				SCC[v]=SCC_CNT;
				if(v==u)break;
			}
			SCC_CNT++;
		}
	}
	void Solve(const int n){for(int i=0;i<n;i++)if(!PRE[i])Dfs(i),assert(STK.empty());}
	bool Check(const int n){for(int i=0;i<n;i++)if(SCC[i*2+0]==SCC[i*2+1])return false;return true;}
}SOLVER;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d",&N)==1);
		if(N==0)break;
		assert(N>=1&&N<=1000);
		for(int i=0;i<N;i++)
		{
			static LL x[4],y[4];
			for(int j=0;j<4;j++)assert(scanf("%lld%lld",&x[j],&y[j])==2);
			SEGMENT[i][0]=Segment(Pair(x[0],y[0]),Pair(x[2],y[2]));
			SEGMENT[i][1]=Segment(Pair(x[1],y[1]),Pair(x[3],y[3]));
			if(!Intersect(SEGMENT[i][0],SEGMENT[i][1]))
			{
				SEGMENT[i][0]=Segment(Pair(x[0],y[0]),Pair(x[1],y[1]));
				SEGMENT[i][1]=Segment(Pair(x[2],y[2]),Pair(x[3],y[3]));
				if(!Intersect(SEGMENT[i][0],SEGMENT[i][1]))
				{
					SEGMENT[i][0]=Segment(Pair(x[0],y[0]),Pair(x[3],y[3]));
					SEGMENT[i][1]=Segment(Pair(x[1],y[1]),Pair(x[2],y[2]));
				}
			}
			assert(Intersect(SEGMENT[i][0],SEGMENT[i][1]));
		}
		SOLVER.clear(N*2);
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)for(int d1=0;d1<2;d1++)for(int d2=0;d2<2;d2++)
		{
			if(Intersect(SEGMENT[i][d1],SEGMENT[j][d2]))
			{
//				printf("Intersect("),SEGMENT[i][d1].Print(),putchar(','),SEGMENT[j][d2].Print(),printf(")\n");
				SOLVER.AddEdge(i*2+d1,j*2+(d2^1));
				SOLVER.AddEdge(j*2+d2,i*2+(d1^1));
			}
		}
		SOLVER.Solve(N*2);
		puts(SOLVER.Check(N)?"YES":"NO");
	}
	assert(scanf("%d",&N)!=1);
	return 0;
}
