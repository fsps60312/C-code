#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Point
{
	int x[3];
	int operator-(const Point &p)const{return min(abs(x[0]-p.x[0]),min(abs(x[1]-p.x[1]),abs(x[2]-p.x[2])));}
};
int TYPE;
vector<Point>P;
int GetValue(const int a){return P[a].x[TYPE];}
bool Cmp(const int a,const int b){return GetValue(a)<GetValue(b);}
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
	bool operator<(const Edge &e)const{return P[a]-P[b]<P[e.a]-P[e.b];}
};
int N,X[100000];
vector<Edge>EDGE;
void AddEdge(const int a,const int b){EDGE.push_back(Edge(a,b));}
int Find(const int a){return X[a]==a?a:(X[a]=Find(X[a]));}
bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;X[a]=b;return true;}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		P.clear();
		for(int i=0;i<N;i++)
		{
			static Point p;
			for(int j=0;j<3;j++)scanf("%d",&p.x[j]);
			P.push_back(p);
		}
		for(int i=0;i<N;i++)X[i]=i;
		EDGE.clear();
		for(TYPE=0;TYPE<3;TYPE++)
		{
			sort(X,X+N,Cmp);
			for(int i=0;i+1<N;)
			{
				if(GetValue(X[i])==GetValue(X[i+1]))
				{
					int j=i;
					while(j<N&&GetValue(X[j])==GetValue(X[j+1]))AddEdge(X[i],X[++j]);
					i=j;
				}
				else AddEdge(X[i],X[i+1]),i++;
			}
		}
		sort(EDGE.begin(),EDGE.end());
		for(int i=0;i<N;i++)X[i]=i;
		long long ans=0LL;
		for(const Edge &e:EDGE)if(Merge(e.a,e.b))ans+=P[e.a]-P[e.b];
		printf("%lld\n",ans);
	}
	return 0;
}
