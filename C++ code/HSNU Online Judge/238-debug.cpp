#include<cstdio>
#include<string>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cassert>
using namespace std;
struct Point
{
	double x,y;
	Point(){}
	Point(double x,double y):x(x),y(y){}
	Point operator-(Point a)const{return Point(x-a.x,y-a.y);}
};
Point S[1500];
vector<Point>V;
double Cross(Point a,Point b){return a.x*b.y-a.y*b.x;}
int Cmp(Point p1,Point p2)
{
	if(p1.y*p2.y>0)return p2.x*p1.y<p2.y*p1.x;
	else if(!p1.y)return p1.x>0?1:p2.y<0;
	else if(!p2.y)return p2.x>0?0:p1.y>0;
	return p1.y>0;
}
double C(double a,double b)
{
	if(a<b)return 0;
	if(b==2.0)return a*(a-1)/2.0;
	if(b==3.0)return a*(a-1)*(a-2)/6.0;
	if(b==4.0)return a*(a-1)*(a-2)*(a-3)/24.0;
	assert(0);
}
int N;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%lf%lf",&S[i].x,&S[i].y);
	double x=0.0;
	for(int i=0;i<N;i++)
	{
		V.clear();
		for(int j=0;j<N;j++)if(j!=i)V.push_back(S[j]-S[i]);
		sort(V.begin(),V.end(),Cmp);
		for(int j=0;j<N-1;j++)V.push_back(V[j]);
for(int j=0;j<V.size();j++)printf("(%.0lf,%.0lf)",V[j].x,V[j].y);puts("");
		for(int l=0,r=1;l<N-1;l++)
		{
			Point o=V[l];//vectors
			while(Cross(o,V[r])>0||r==l)r++;
			x+=C(r-l-1,2.0);
		}
	}
	printf("ans=%.4f,drap=%.4f\n",C(N,4.0)*2.0,-C(N-1,3.0)*N+x);
	double ans=C(N,4.0)*2.0-C(N-1,3.0)*N+x;
	printf("%lf\n",double(ans)/C(N,3.0)+3);
}
