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
	Point operator+(const Point &p)const{return Point(r+p.r,c+p.c);}
	Point operator-(const Point &p)const{return Point(r-p.r,c-p.c);}
	Point operator*(const int &a)const{return Point(r*a,c*a);}
	bool operator<(const Point &p)const{return r!=p.r?r<p.r:c<p.c;}
	bool operator==(const Point &p)const{return r==p.r&&c==p.c;}
}P[5000];
int cmpangle(const Point &a,const Point &b)
{
	if(a.r*b.c!=a.c*b.r)return a.r*b.c<a.c*b.r?-1:1;
	return 0;
}
int cmpaxis(const Point &a,const Point &b)
{
	if(a.r!=b.r)return a.r<b.r?-1:1;
	if(a.c!=b.c)return a.c<b.c?-1:1;
	return 0;
}
bool cmp(const Point &a,const Point &b)
{
	static int tmp;
	if((tmp=cmpangle(a,b))!=0)return tmp<0;
	return cmpaxis(a,b)==-1;
}
bool VIS[5001][5001];
int main()
{
	scanf("%d%d%d",&R,&C,&N);
	for(int r=1;r<=R;r++)for(int c=1;c<=C;c++)VIS[r][c]=false;
	for(int i=0;i<N;i++)
	{
		int &r=P[i].r,&c=P[i].c;
		scanf("%d%d",&r,&c);
		VIS[r][c]=true;
	}
	int ans=0;
	for(int i=0;i<N;i++)
	{
		vector<Point>to;
		for(int j=0;j<N;j++)if(j!=i)to.push_back(P[j]-P[i]);
		sort(to.begin(),to.end(),cmp);
		for(int r=0,l=0;l<to.size();)
		{
			while(r<to.size()&&cmpangle(to[r],to[l])==0)r++;
			if(r-l<=1)ans=max(ans,r-l);
			else
			{
				int cnt=0;
				for(int j=l;j<r;j++)
				{
					Point &v=to[j];
					for()
				}
			}
			l=r;
		}
	}
	printf("%d\n",ans);
	return 0;
}
