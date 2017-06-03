#include<cstdio>
#include<cassert>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL,SQ_MAX=40000000000000000LL;
void getmin(LL &a,const LL b){if(b<a)a=b;}
void getmax(LL &a,const LL b){if(b>a)a=b;}
LL Sq(const LL a){return a*a;}
struct Point
{
	LL x,y;
	Point(){}
	Point(const LL _x,const LL _y):x(_x),y(_y){}
};
//bool CmpY(const Point &a,const Point &b){return a.y<b.y;}
int N;
Point P[100000];
bool SolveTilt(const LL tsq)
{
	LL ymn=0,ymx=0;
	int l,r=0;
	for(l=0;l<N&&P[l].x<0&&Sq(P[l].x)<tsq;l++)getmax(ymx,P[l].y),getmin(ymn,P[l].y);
	for(;;)
	{
		if(l==N||P[l].x>=0)return false;
		for(;r<N&&Sq(P[r].x-P[l].x)<=tsq;r++);
		const LL y2=sqrt(tsq-Sq(P[l].x));
		if(y2>-P[l].x)return false;
		const LL y1=max(-y2,(LL)(y2-sqrt(tsq)));
		if(r==N&&ymn<=y1&&y2<=ymx)return true;
		getmax(ymx,P[l].y),getmin(ymn,P[l].y);
		l++;
	}
}
bool SolveLine(const LL lsq)
{
	static LL lymx[100000],lymn[100000],rymx[100000],rymn[100000];
	lymx[0]=lymn[0]=P[0].y;
	for(int i=1;i<N;i++)lymx[i]=max(lymx[i-1],P[i].y),lymn[i]=min(lymn[i-1],P[i].y);
	rymx[N-1]=rymn[N-1]=P[N-1].y;
	for(int i=N-1;i>=0;i--)rymx[i]=max(rymx[i+1],P[i].y),rymn[i]=min(rymn[i+1],P[i].y);
	for(int r=0,l=0;r<N;r++)
	{
		for(;Sq(P[r].x-P[l].x)>lsq;l++);
		if(l==0&&r==N-1)return true;
		const LL x1=P[l].x,x2=P[r].x,y1=min(l>0?lymn[l-1]:INF,r+1<N?rymn[r+1]:INF),y2=max(l>0?lymx[l-1]:-INF,r+1<N?rymx[r+1]:-INF);
		if(Sq(y2-y1)<=lsq&&max(Sq(y1),Sq(y2))+max(Sq(x1),Sq(x2))<=lsq)return true;
	}
	return false;
}
bool CmpX(const Point &a,const Point &b){return a.x<b.x;}
LL TiltMin()
{
	sort(P,P+N,CmpX);
	LL l=0,r=SQ_MAX;
	while(l<r)
	{
		const LL mid=(l+r)/2;
		if(SolveTilt(mid))r=mid;
		else l=mid+1LL;
	}
	return r;
}
LL LineMin()
{
	sort(P,P+N,CmpX);
	LL l=0,r=SQ_MAX;
	while(l<r)
	{
		const LL mid=(l+r)/2;
		if(SolveLine(mid))r=mid;
		else l=mid+1LL;
	}
	return r;
}
void Flip1(bool ish){for(int i=0;i<N;i++)(ish?P[i].x:P[i].y)*=-1;}
void Flip2(){for(int i=0;i<N;i++)swap(P[i].x,P[i].y);}
void Flip3(){Flip2();Flip1(true),Flip1(false);}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lld%lld",&P[i].x,&P[i].y);
		LL ans=INF;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<2;j++)getmin(ans,TiltMin()),Flip3();
			Flip1(i&1);
		}
		for(int i=0;i<2;i++)getmin(ans,LineMin()),Flip2();
		printf("%lld\n",ans);
	}
	return 0;
}
