#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
struct Point
{
	int X,Y,Z;
	Point(){}
	Point(const int _X,const int _Y,const int _Z):X(_X),Y(_Y),Z(_Z){}
};
bool operator<(const Point &a,const Point &b)
{
	if(a.Z!=b.Z)return a.Z<b.Z;
	if(a.X!=b.X)return a.X<b.X;
	if(a.Y!=b.Y)return a.Y<b.Y;
	return false;
}
struct Vector
{
	int X,Y;
	Vector(){}
	Vector(const int _X,const int _Y):X(_X),Y(_Y){}
};
Vector operator-(const Point &a,const Point &b){return Vector(a.X-b.X,a.Y-b.Y);}
int Trans(const LL v){return v==0?0:(v<0?-1:1);}
int Direction(const Vector &a,const Vector &b)
{
	return Trans((LL)a.X*b.Y-(LL)b.X*a.Y);
}
struct Triangle
{
	Point A,B,C;
	Triangle(){}
	Triangle(const Point &_A,const Point &_B,const Point &_C):A(_A),B(_B),C(_C){}
	bool Contains(const Point &p)const
	{
		return Direction(B-A,p-A)*Direction(p-A,C-A)>=0&&Direction(A-B,p-B)*Direction(p-B,C-B)>=0;
	}
};
Point ReadPoint()
{
	Point p;
	scanf("%d%d%d",&p.X,&p.Y,&p.Z);
	return p;
}
Triangle ReadTriangle(){return Triangle(ReadPoint(),ReadPoint(),ReadPoint());}
int M,H[6000];
Point RI[6000];
vector<Triangle>S;
Point A0,B0;
int A,B;
vector<int>ET[6000];
map<Point,int>ID;
vector<Point>ANS;
bool Dfs(const int u,bool *vis,const int bound)
{
	if(vis[u]||H[u]>bound)return false;
	vis[u]=true;
	ANS.push_back(RI[u]);
	if(u==B){ANS.push_back(B0);return true;}
	for(const int nxt:ET[u])if(Dfs(nxt,vis,bound))return true;
	ANS.pop_back();
	return false;
}
bool Solve(const int bound)
{
	if(A0.Z>bound||B0.Z>bound)return false;
	static bool vis[6000];
	for(int i=0;i<M;i++)vis[i]=false;
	ANS.clear();ANS.push_back(A0);
	return Dfs(A,vis,bound);
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		S.clear();
		for(int i=0;i<N;i++)S.push_back(ReadTriangle());
		A0=ReadPoint(),B0=ReadPoint();
		ID.clear();
		for(const Triangle &t:S)ID[t.A]=ID[t.B]=ID[t.C]=-1;
		{M=0;for(auto &it:ID)H[it.second=M++]=it.first.Z,RI[it.second]=it.first;}
		for(int i=0;i<M;i++)ET[i].clear();
		for(const Triangle &t:S)
		{
			ET[ID[t.A]].push_back(ID[t.B]);
			ET[ID[t.A]].push_back(ID[t.C]);
			ET[ID[t.B]].push_back(ID[t.A]);
			ET[ID[t.B]].push_back(ID[t.C]);
			ET[ID[t.C]].push_back(ID[t.A]);
			ET[ID[t.C]].push_back(ID[t.B]);
		}
		for(const Triangle &t:S)if(t.Contains(A0)){A=ID[min(min(t.A,t.B),t.C)];goto index_foundA;}
		assert(0);index_foundA:;
		for(const Triangle &t:S)if(t.Contains(B0)){B=ID[min(min(t.A,t.B),t.C)];goto index_foundB;}
		assert(0);index_foundB:;
//		printf("A=(%d,%d,%d)\n",RI[A].X,RI[A].Y,RI[A].Z);
//		printf("B=(%d,%d,%d)\n",RI[B].X,RI[B].Y,RI[B].Z);
		int l=0,r=1000000;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Solve(mid))r=mid;
			else l=mid+1;
		}
//		printf("r=%d\n",r);
		assert(Solve(r));
		printf("%d\n",(int)ANS.size());
		for(const Point &p:ANS)printf("%d %d %d\n",p.X,p.Y,p.Z);
	}
	return 0;
}
