#include<cstdio>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<cassert>
using namespace std;
int N,W;
struct Point
{
	int x,y;
	Point(){}
	Point(const int _x,const int _y):x(_x),y(_y){}
};
vector<Point>P;
struct Wall
{
	int a,b,da,db;
	Wall(){}
	Wall(const int _a,const int _da,const int _b,const int _db):a(_a),da(_da),b(_b),db(_db){}
};
vector<Wall>WALL;
int DEG[100000],ET[100000][4];//up,right,down,left
struct CmpY{bool operator()(const int a,const int b)const{return P[a].y!=P[b].y?P[a].y<P[b].y:P[a].x<P[b].x;}};
set<int,CmpY>REMAIN;
set<int>ONE;
void AddDegree(const int p)
{
	const int &deg=++DEG[p];
	if(deg==1)assert(REMAIN.find(p)==REMAIN.end()&&ONE.find(p)==ONE.end()),REMAIN.insert(p),ONE.insert(p);
	else if(deg==2)assert(ONE.find(p)!=ONE.end()),ONE.erase(p);
}
void MinusDegree(const int p)
{
	const int &deg=--DEG[p];
	if(deg==0)assert(REMAIN.find(p)!=REMAIN.end()&&ONE.find(p)!=ONE.end()),REMAIN.erase(p),ONE.erase(p);
	else if(deg==1)assert(ONE.find(p)==ONE.end()),ONE.insert(p);
}
void Delete(const Wall &w)
{
	assert(ET[w.a][w.da]!=-1&&ET[w.b][w.db]!=-1);
	ET[w.a][w.da]=ET[w.b][w.db]=-1;
	MinusDegree(w.a),MinusDegree(w.b);
}
bool VIS[200000];
int Nxt(const int u,int &d,int &e)
{
	(d+=3)%=4;
	while((e=ET[u][d])==-1)(++d)%=4;
	const Wall &w=WALL[e];
	return u==w.a?w.b:w.a;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)for(int j=0;j<4;j++)ET[i][j]=-1;
	for(int i=0;i<N;i++)DEG[i]=0;
	P.clear(),WALL.clear();
	for(int i=0,x,y;i<N;i++)scanf("%d%d",&x,&y),P.push_back(Point(x,y));
	scanf("%d",&W);
	for(int i=0,a,b;i<W;i++)
	{
		scanf("%d%d",&a,&b);
		a--,b--;
		assert((P[a].x==P[b].x)!=(P[a].y==P[b].y));
		int da=-1,db=-1;
		if(P[a].x!=P[b].x)
		{
			if(P[a].x>P[b].x)swap(a,b);
			assert(ET[a][da=1]==-1&&ET[b][db=3]==-1);
			ET[a][1]=ET[b][3]=i;
		}
		else
		{
			if(P[a].y>P[b].y)swap(a,b);
			assert(ET[a][da=2]==-1&&ET[b][db=0]==-1);
			ET[a][2]=ET[b][0]=i;
		}
		assert(da>=0&&da<4&&db>=0&&db<4);
		WALL.push_back(Wall(a,da,b,db));
		AddDegree(a),AddDegree(b);
	}
	vector<int>ans;
	for(int i=0;i<W;i++)VIS[i]=false;
//	printf("N=%d,W=%d\n",N,W);
	int cnt=0;
	for(;;)
	{
		while(!ONE.empty())
		{
			const int u=*ONE.begin();
			int e=-1,d=1;
			Nxt(u,d,e);
			ans.push_back(e);
//			printf("ans %d\n",e+1);
			Delete(WALL[e]),cnt++;
//			printf("Delete");Print(WALL[e]);
		}
		if(REMAIN.empty())break;
		const int s=*REMAIN.begin();
		vector<int>edge;
		int e=-1;
		for(int d=2,u=Nxt(s,d,e);u!=s;u=Nxt(u,d,e))VIS[e]^=true,edge.push_back(e);
		VIS[e]^=true,edge.push_back(e);
		for(const int u:edge)if(VIS[u])Delete(WALL[u]),cnt++;
	}
	printf("%d\n",ans.size());
	for(const int v:ans)printf("%d\n",v+1);
	assert(cnt==W);
	return 0;
}
