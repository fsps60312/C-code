#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Farm{int x1,y1,x2,y2;};
vector<Farm>F;
int N;
LL SweepDown()
{
	sort(F.begin(),F.end(),[](const Farm &a,const Farm &b)->bool{return a.y1<b.y1;});
	vector<int>ys;
	for(const Farm &f:F)ys.push_back(f.y2);
	sort(ys.begin(),ys.end());
	int i=0;
	LL ans=0LL;
	for(const Farm &f:F)
	{
		for(;i<N&&ys[i]<f.y1;i++);
		ans+=i;
	}
	return ans;
}
LL SweepUp()
{
	sort(F.begin(),F.end(),[](const Farm &a,const Farm &b)->bool{return a.y2>b.y2;});
	vector<int>ys;
	for(const Farm &f:F)ys.push_back(f.y1);
	sort(ys.begin(),ys.end(),greater<int>());
	int i=0;
	LL ans=0LL;
	for(const Farm &f:F)
	{
		for(;i<N&&ys[i]>f.y2;i++);
		ans+=i;
	}
	return ans;
}
LL SweepRight()
{
	sort(F.begin(),F.end(),[](const Farm &a,const Farm &b)->bool{return a.x1<b.x1;});
	vector<int>xs;
	for(const Farm &f:F)xs.push_back(f.x2);
	sort(xs.begin(),xs.end());
	int i=0;
	LL ans=0LL;
	for(const Farm &f:F)
	{
		for(;i<N&&xs[i]<f.x1;i++);
		ans+=i;
	}
	return ans;
}
LL SweepLeft()
{
	sort(F.begin(),F.end(),[](const Farm &a,const Farm &b)->bool{return a.x2>b.x2;});
	vector<int>xs;
	for(const Farm &f:F)xs.push_back(f.x1);
	sort(xs.begin(),xs.end(),greater<int>());
	int i=0;
	LL ans=0LL;
	for(const Farm &f:F)
	{
		for(;i<N&&xs[i]>f.x2;i++);
		ans+=i;
	}
	return ans;
}
struct Bit
{
	int DATA[100001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)DATA[i]=0;}
	void Add(int i){assert(i);while(i<=N){DATA[i]++;i+=(i&(-i));}}
	int Query(int i){int ans=0;while(i){ans+=DATA[i];i-=(i&(-i));}return ans;}
}BIT;
struct Point
{
	int x,y;
	Point(){}
	Point(const int _x,const int _y):x(_x),y(_y){}
	bool operator<(const Point &p)const{return y!=p.y?y<p.y:x<p.x;}
};
vector<Point>ULP,URP,DLP,DRP;
int W,H;
LL ExcludeUpLeft()
{
	sort(DRP.begin(),DRP.end(),[](const Point &a,const Point &b)->bool{return a.y<b.y;});
	sort(F.begin(),F.end(),[](const Farm &a,const Farm &b)->bool{return a.y1<b.y1;});
	BIT.Clear(W);
	int i=0;
	LL ans=0LL;
	for(const Farm &f:F)
	{
		for(;i<N&&DRP[i].y<f.y1;i++)BIT.Add(DRP[i].x);
		ans+=BIT.Query(f.x1-1);
	}
	return ans;
}
LL ExcludeUpRight()
{
	sort(DLP.begin(),DLP.end(),[](const Point &a,const Point &b)->bool{return a.y<b.y;});
	sort(F.begin(),F.end(),[](const Farm &a,const Farm &b)->bool{return a.y1<b.y1;});
	BIT.Clear(W);
	int i=0;
	LL ans=0LL;
	for(const Farm &f:F)
	{
		for(;i<N&&DLP[i].y<f.y1;i++)BIT.Add(DLP[i].x);
		ans+=BIT.Query(W)-BIT.Query(f.x2);
	}
	return ans;
}
LL ExcludeDownLeft()
{
	sort(URP.begin(),URP.end(),[](const Point &a,const Point &b)->bool{return a.y>b.y;});
	sort(F.begin(),F.end(),[](const Farm &a,const Farm &b)->bool{return a.y2>b.y2;});
	BIT.Clear(W);
	int i=0;
	LL ans=0LL;
	for(const Farm &f:F)
	{
		for(;i<N&&URP[i].y>f.y2;i++)BIT.Add(URP[i].x);
		ans+=BIT.Query(f.x1-1);
	}
	return ans;
}
LL ExcludeDownRight()
{
	sort(ULP.begin(),ULP.end(),[](const Point &a,const Point &b)->bool{return a.y>b.y;});
	sort(F.begin(),F.end(),[](const Farm &a,const Farm &b)->bool{return a.y2>b.y2;});
	BIT.Clear(W);
	int i=0;
	LL ans=0LL;
	for(const Farm &f:F)
	{
		for(;i<N&&ULP[i].y>f.y2;i++)BIT.Add(ULP[i].x);
		ans+=BIT.Query(W)-BIT.Query(f.x2);
	}
	return ans;
}
int main()
{
//	freopen("inB.txt","r",stdin);
	while(scanf("%d%d",&W,&H)==2)
	{
		scanf("%d",&N);
		ULP.clear(),URP.clear(),DLP.clear(),DRP.clear();
		F.clear();
		for(int i=0;i<N;i++)
		{
			static Farm f;
			int &x1=f.x1,&y1=f.y1,&x2=f.x2,&y2=f.y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1++,y1++;
			ULP.push_back(Point(x1,y1)),URP.push_back(Point(x2,y1));
			DLP.push_back(Point(x1,y2)),DRP.push_back(Point(x2,y2));
			F.push_back(f);
		}
		LL ans=SweepDown()+SweepUp()+SweepRight()+SweepLeft();
		ans-=ExcludeUpLeft()+ExcludeUpRight()+ExcludeDownLeft()+ExcludeDownRight();
		assert(ans%2LL==0LL);
		printf("%lld\n",(LL)N*(N-1LL)/2LL-ans/2LL);
	}
	return 0;
}
