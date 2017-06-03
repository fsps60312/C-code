#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int R,C,N;
struct Point
{
	int r,c;
	Point(){}
	Point(const int &_r,const int &_c):r(_r),c(_c){}
	bool operator<(const Point &p)const{return r!=p.r?r<p.r:c<p.c;}
	Point operator-(const Point &p)const{return Point(r-p.r,c-p.c);}
	bool operator==(const Point &p)const{return r==p.r&&c==p.c;}
}P[5000];
int gcd(const int &a,const int &b){return b?gcd(b,a%b):a;}
void Reduce(Point &p){if(p.r<0||(p.r==0&&p.c<0))p.r=-p.r,p.c=-p.c;int g=gcd(abs(p.r),abs(p.c));p.r/=g,p.c/=g;}

int main()
{
	scanf("%d%d%d",&R,&C,&N);
	for(int i=0;i<N;i++){scanf("%d%d",&P[i].r,&P[i].c);}
	int ans=0;
	for(int i=0;i<N;i++)
	{
		vector<Point>to;
		for(int j=0;j<N;j++)if(j!=i)to.push_back(P[j]-P[i]);
		for(int j=0;j<to.size();j++)Reduce(to[j]);
		sort(to.begin(),to.end());
		for(int r=0,l=0;l<to.size();)
		{
			while(r<to.size()&&to[r]==to[l])r++;
			if(r-l==Cnt(P[i],to[l]))ans=max(ans,r-l);
			l=r;
		}
	}
	printf("%d\n",ans);
	return 0;
}
