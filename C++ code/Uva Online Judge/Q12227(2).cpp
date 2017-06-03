#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#include<cassert>
using namespace std;
struct Point
{
	int x,y,z;
	Point(){}
	Point(int x,int y,int z):x(x),y(y),z(z){}
	void Scanf(){scanf("%d%d%d",&x,&y,&z);}
	bool operator<(const Point &p)const
	{
		if(x!=p.x)return x<p.x;
		if(y!=p.y)return y<p.y;
		return z<p.z;
	}
}BEGIN,END;
int T,N;
struct Warmhole
{
	Point entry,exit;
	int creation,shift;
	void Scanf()
	{
		entry.Scanf(),exit.Scanf();
		scanf("%d%d",&creation,&shift);
	}
};
vector<Warmhole>WARMHOLE;
int Hypot(int a,int b,int c){return (int)(sqrt(a*a+b*b+c*c)+0.5);}
int Dis(Point &a,Point &b){return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
vector<Point>P;
int LEN[52][52];
void BuildP()
{
	P.clear();
	for(int i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		P.push_back(w.exit);
	}
	P.push_back(BEGIN);
	P.push_back(END);
}
void BuildLEN()
{
	for(int i=0;i<P.size();i++)
	{
		for(int j=0;j<P.size();j++)
		{
			if(j<N)
			{
				Point &p=WARMHOLE[j].entry;
				LEN[i][j]=min(Dis(P[i],P[j]),Dis(P[i],p.begin));
			}
			else LEN[i][j]=Dis(P[i],P[j]);
		}
	}
}
int Solve()
{
	for(int m=0;m<P.size();m++)
	{
		for(int i=0;i<P.size();i++)
		{
			for(int j=0;j<P.size();j++)
			{
				if(LEN[i][m]+LEN[m][j]<LEN[i][j])LEN[i][j]=LEN[i][m]+LEN[m][j];
			}
		}
	}
	for(int i=0;i<P.size();i++)if(LEN[i][i]<0)return -1;
	return LEN[N][N+1];
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			BEGIN.Scanf(),END.Scanf();
			scanf("%d",&N);
			WARMHOLE.clear();
			for(int i=0;i<N;i++)
			{
				static Warmhole w;
				w.Scanf();
				WARMHOLE.push_back(w);
			}
		}
		BuildP();
		BuildLEN();
		printf("%d\n",Solve());
	}
	return 0;
}
