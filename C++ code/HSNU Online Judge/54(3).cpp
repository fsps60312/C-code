#include<cstdio>
#include<algorithm>
#include<vector>
#include<cassert>
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
bool VIS[5001][5001];
bool Valid(const Point &p){return p.r>=1&&p.r<=R&&p.c>=1&&p.c<=C;}
int main()
{
	scanf("%d%d%d",&R,&C,&N);
	for(int r=1;r<=R;r++)for(int c=1;c<=C;c++)VIS[r][c]=false;
	for(int i=0;i<N;i++)
	{
		int &r=P[i].r,&c=P[i].c;
		scanf("%d%d",&r,&c);
		assert(!VIS[r][c]);
		VIS[r][c]=true;
	}
	int ans=1;
	for(int i=0;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			Point v=P[j]-P[i],o=Point(P[j]);
			int cnt=0;
			while(Valid(o)&&VIS[o.r][o.c])cnt++,o=o+v;
			if(Valid(o))continue;
			o=Point(P[i]);
			while(Valid(o)&&VIS[o.r][o.c])cnt++,o=o-v;
			if(Valid(o))continue;
			ans=max(ans,cnt);
		}
	}
	printf("%d\n",ans>=3?ans:0);
	return 0;
}
