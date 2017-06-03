#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
const int INF=2147483647;
struct Hungary
{
	int N,M,MATCH[400],LOW[400];
	int EDGE[200][400],WA[200],WB[400];
	bool VA[200],VB[400];
	bool Extend(const int u)
	{
		VA[u]=true;
		for(int i=0;i<M;i++)
		{
			if(WA[u]+WB[i]==EDGE[u][i])
			{
				if(!VB[i])
				{
					VB[i]=true;
					if(MATCH[i]==-1||Extend(MATCH[i]))
					{
						MATCH[i]=u;
						return true;
					}
				}
			}
			else
			{
				assert(WA[u]+WB[i]<EDGE[u][i]);
				getmin(LOW[u],EDGE[u][i]-WA[u]-WB[i]);
			}
		}
		return false;
	}
	void Slack()
	{
		int low=INF;
		for(int i=0;i<M;i++)getmin(low,LOW[i]);
		for(int i=0;i<N;i++)if(VA[i])WA[i]-=low;
		for(int i=0;i<M;i++)if(VB[i])WB[i]+=low;
	}
	void Solve()
	{
		for(int i=0;i<N;i++)WA[i]=0;
		for(int i=0;i<M;i++)MATCH[i]=-1,WB[i]=0;
		for(int i=0;i<N;i++)
		{
			for(;;)
			{
				for(int j=0;j<N;j++)VA[j]=false;
				for(int j=0;j<M;j++)VB[j]=false,LOW[j]=INF;
				if(Extend(i))break;
				else Slack();
			}
		}
	}
}HUNGARY;
struct Point
{
	int _X,_Y;
	Point(){}
	Point(const int X,const int Y):_X(X),_Y(Y){}
};
int Dist(const Point &a,const Point &b){return abs(a._X-b._X)+abs(a._Y-b._Y);}
Point P[200],W[400];
int M,N,K,S;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&M,&N,&K,&S)==4)
	{
		static bool is_valid[21][21];
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)is_valid[i][j]=true;
		for(int i=0;i<K;i++)
		{
			scanf("%d%d",&P[i]._X,&P[i]._Y);
			is_valid[P[i]._Y][P[i]._X]=false;
		}
		for(int i=0;i<K;i++)
		{
			scanf("%d%d",&W[i]._X,&W[i]._Y);
			is_valid[W[i]._Y][W[i]._X]=false;
		}
		vector<Point>valid;
		for(int y=1;y<=N;y++)for(int x=1;x<=M;x++)if(is_valid[y][x])valid.push_back(Point(x,y));
		HUNGARY.N=K;
		HUNGARY.M=(int)valid.size();
		for(int i=0;i<HUNGARY.N;i++)for(int j=0;j<HUNGARY.M;j++)HUNGARY.EDGE[i][j]=Dist(P[i],valid[j]);
		HUNGARY.Solve();
		vector<pair<Point,int> >ans;
		for(int i=0;i<HUNGARY.M;i++)if(HUNGARY.MATCH[i]!=-1)
		{
			ans.push_back(make_pair())
		}
	}
	return 0;
}
