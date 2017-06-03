#include<cstdio>
#include<vector>
using namespace std;
int T,N,M;
struct Point
{
	int x,y,z;
	Point(){}
	Point(int x,int y,int z):x(x),y(y),z(z){}
};

struct Shape
{
	vector<Point> P;
	void scanf()
	{
		int p;
		scanf("%d",&p);
		vector<int> x,y;
		for(int i=0,a,b;i<p;i++)
		{
			scanf("%d%d",&a,&b);
			x.push_back(a),y.push_back(b);
		}
		double dx[4]={0,0.25,0,-0.25},dy[4]={0.25,0,-0.25,0};
		for(double i=0.5;i<M;i+=1.0)
		{
			for(double j=0.5;j<M;j+=1.0)
			{
				for(int d=0;d<4;d++)
				{
					if(InShape(x,y,i+dx[d],j+dy[d]))P.add(Point((int)i,(int)j,d));
				}
			}
		}
	}
}S[6];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
	}
	return 0;
}
