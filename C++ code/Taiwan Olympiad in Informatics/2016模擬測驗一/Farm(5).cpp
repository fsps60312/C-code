#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
void GetInt(int &v)
{
	const int ZERO='0',NINE='9';
	v=0;
	int c=getchar();
	while(c<ZERO||c>NINE)c=getchar();
	while(c>=ZERO&&c<=NINE)v=v*10+(c-ZERO),c=getchar();
}
struct Node
{
	Node *ch[2];
	int sum;
}Node_BUFFER[100000*24*4],*NEW;
Node *NewNode(const int _sum)
{
	NEW->ch[0]=NEW->ch[1]=NULL;
	NEW->sum=_sum;
	return NEW++;
}
struct Point
{
	int x,y;
	Point(){}
	Point(const int _x,const int _y):x(_x),y(_y){}
	bool operator<(const Point &p)const{return y!=p.y?y<p.y:x<p.x;}
};
Node *Build(const int l,const int r)
{
	Node *ans=NewNode(0);
	if(l<r)
	{
		const int mid=(l+r)/2;
		ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	}
	return ans;
}
Node *Add(Node *o,const int l,const int r,const int loc)
{
	Node *ans=NewNode(o->sum+1);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc),ans->ch[1]=o->ch[1];
		else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc);
	}
	return ans;
}
int Query(Node *lo,Node *ro,const int l,const int r,const int bl,const int br)
{
	if(bl<=l&&r<=br)return ro->sum-lo->sum;
	const int mid=(l+r)/2;
	int ans=0;
	if(mid>=bl)ans+=Query(lo->ch[0],ro->ch[0],l,mid,bl,br);
	if(mid+1<=br)ans+=Query(lo->ch[1],ro->ch[1],mid+1,r,bl,br);
	return ans;
}
int W,H,N;
void BuildPlane(Node **tree,vector<Point>&ps)
{
	sort(ps.begin(),ps.end());
	tree[0]=Build(0,W+1);
	for(int y=1,i=0;y<=H+1;y++)
	{
		tree[y]=tree[y-1];
		for(;i<N&&ps[i].y<=y;i++)tree[y]=Add(tree[y],0,W+1,ps[i].x);
	}
}
Node *UL[100002],*UR[100002],*DL[100002],*DR[100002];
vector<Point>ULP,URP,DLP,DRP;
struct Farm
{
	int x1,y1,x2,y2;
};
vector<Farm>F;
int main()
{
//	freopen("inB.txt","r",stdin);
	while(scanf("%d%d",&W,&H)==2)
	{
		NEW=Node_BUFFER;
		scanf("%d",&N);
		ULP.clear(),URP.clear(),DLP.clear(),DRP.clear();
		F.clear();
		for(int i=0;i<N;i++)
		{
			static Farm f;
			int &x1=f.x1,&y1=f.y1,&x2=f.x2,&y2=f.y2;
			GetInt(x1),GetInt(y1),GetInt(x2),GetInt(y2);
			x1++,y1++;
			ULP.push_back(Point(x1,y1)),URP.push_back(Point(x2,y1));
			DLP.push_back(Point(x1,y2)),DRP.push_back(Point(x2,y2));
			F.push_back(f);
		}
		BuildPlane(UL,ULP),BuildPlane(UR,URP);
		BuildPlane(DL,DLP),BuildPlane(DR,DRP);
		LL ans=0LL;
		for(const Farm &f:F)
		{
			ans+=Query(UL[0],UL[H+1],0,W+1,f.x2+1,W+1);
			ans+=Query(UR[0],UR[H+1],0,W+1,0,f.x1-1);
			ans+=Query(UL[f.y2],UL[H+1],0,W+1,0,W+1);
			ans+=Query(DL[0],DL[f.y1-1],0,W+1,0,W+1);
			ans-=Query(UL[f.y2],UL[H+1],0,W+1,f.x2+1,W+1);
			ans-=Query(UR[f.y2],UR[H+1],0,W+1,0,f.x1-1);
			ans-=Query(DL[0],DL[f.y1-1],0,W+1,f.x2+1,W+1);
			ans-=Query(DR[0],DR[f.y1-1],0,W+1,0,f.x1-1);
		}
		assert(ans%2LL==0LL);
		printf("%lld\n",(LL)N*(N-1LL)/2LL-ans/2LL);
	}
	return 0;
}
