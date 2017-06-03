#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
int N;
struct Pair
{
	int x,y;
	Pair(){}
	Pair(const int _x,const int _y):x(_x),y(_y){}
	bool operator==(const Pair &p)const{return x==p.x&&y==p.y;}
	Pair operator-(const Pair &p)const{return Pair(x-p.x,y-p.y);}
};
vector<Pair>STATION;
int Cross(const Pair &a,const Pair &b){return a.x*b.y-b.x*a.y;}
int Intersect(const Pair &a,const Pair &b){return a.x*b.x+a.y*b.y;}
int Quandrant(const int i,const int c)
{
	if(i>0&&c>=0)return 1;
	else if(i<=0&&c>0)return 2;
	else if(i<=0&&c<=0)return 3;
	else if(i>0&&c<0)return 4;
	else printf("i=%d,c=%d\n",i,c),assert(0);
}
int Quandrant(const Pair &a,const Pair &b){return Quandrant(Intersect(a,b),Cross(a,b));}
bool CmpAngle(const Pair &a,const Pair &b)
{
	const Pair o=Pair(1,0);
	const int ia=Intersect(o,a),ca=Cross(o,a),ib=Intersect(o,b),cb=Cross(o,b);
	const int qa=Quandrant(ia,ca),qb=Quandrant(ib,cb);
	if(qa!=qb)return qa<qb;
	LL va=(LL)ia*abs(ia)*(b.x*b.x+b.y*b.y),vb=(LL)ib*abs(ib)*(a.x*a.x+a.y*a.y);
	switch(qa)
	{
		case 1:
		case 2:return va>vb;
		case 3:
		case 4:return va<vb;
		default:assert(0);
	}
}
int Solve()
{
	if(N<=2)return 0;
	int ans=N*(N-1)*(N-2)/6,extra=0;
	for(int _o=0;_o<N;_o++)
	{
		const Pair &o=STATION[_o];
//		printf("o(%d,%d)\n",o.x,o.y);
		vector<Pair>p,tmp;
		for(int i=0;i<N;i++)if(i!=_o)p.push_back(STATION[i]-o),tmp.push_back(STATION[i]);
		sort(p.begin(),p.end(),CmpAngle);
		for(int i=0;i<N-1;i++)p.push_back(p[i]);//,printf("(%d,%d)\n",p[i].x,p[i].y);
		for(int i=0,l=0,r=-1;i<N-1;i++)
		{
			while(l<=i||(l<i+N-1&&Quandrant(p[i],p[l])<2))l++;
			while(r<i||(r+1<i+N-1&&Quandrant(p[i],p[r+1])<=3))r++;
//			printf("l=%d,r=%d\n",l,r);
			extra+=(r-l+1);
		}
	}
	assert(extra%2==0);
	return ans-=extra/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		STATION.clear();
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			STATION.push_back(Pair(x,y));
		}
		static int kase=1;
		printf("Scenario %d:\nThere are %d sites for making valid tracks\n",kase++,Solve());
	}
	return 0;
}
