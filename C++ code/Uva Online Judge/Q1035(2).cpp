#include<cstdio>
#include<cassert>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const double EPS=1e-9;
double Hypot(const double x,const double y){return sqrt(x*x+y*y);}
struct Point
{
	double x,y;
};
double Intersection(const Point &pc,const Point &pd,const Point &pa,const Point &pb)
{
	const double x=pa.x,y=pa.y,X=pc.x,Y=pc.y;
	const double a=pb.x-pa.x,b=pb.y-pa.y,c=pd.x-pc.x,d=pd.y-pc.y;
	if(fabs(a*d-b*c)<EPS)return -1.0;
	return (b*X-b*x+a*y-a*Y)/(a*d-b*c);
}
int N;
Point A[100],B[100];
vector<double>S[100];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%lf%lf%lf%lf",&A[i].x,&A[i].y,&B[i].x,&B[i].y),S[i].clear();
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)
		{
			const double v1=Intersection(A[i],B[i],A[j],B[j]),v2=Intersection(A[j],B[j],A[i],B[i]);
			if(0.0<=v1&&v1<=1.0&&0.0<=v2&&v2<=1.0)S[i].push_back(v1),S[j].push_back(v2);
		}
		int ans=0;
		for(int i=0;i<N;i++)
		{
			const double len=Hypot(A[i].x-B[i].x,A[i].y-B[i].y);
			S[i].push_back(0.0-25.0/len),S[i].push_back(1.0+25.0/len);
			sort(S[i].begin(),S[i].end());
			for(int j=1;j<(int)S[i].size();j++)
			{
				const double dist=len*(S[i][j]-S[i][j-1]);
				if(dist>50.0)ans+=dist/50.0;
			}
		}
		static int kase=0;
		printf("Map %d\nTrees = %d\n",++kase,ans);
	}
	return 0;
}
