#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
struct Obstacle
{
	int x1,y1,x2,y2;
	LL cost;
	Obstacle(){}
	Obstacle(const int _x1,const int _y1,const int _x2,const int _y2,const LL _c):x1(_x1),y1(_y1),x2(_x2),y2(_y2),cost(_c){}
	bool operator<(const Obstacle &o)const{return x2>o.x2;}
};
vector<Obstacle>OBSTACLE;
int N,M,P;
LL B;
map<int,int>IDX;
LL MN[1600000],TAG[1600000];
void Build(const int id,const int l,const int r)
{
	MN[id]=TAG[id]=0LL;
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void PutDown(const int id)
{
	TAG[id*2]+=TAG[id],TAG[id*2+1]+=TAG[id];
	MN[id*2]+=TAG[id],MN[id*2+1]+=TAG[id];
	TAG[id]=0LL;
}
void Add(const int id,const int l,const int r,const int bl,const int br,const LL &v)
{
	if(l>br||r<bl)return;
	if(bl<=l&&r<=br){MN[id]+=v,TAG[id]+=v;assert(MN[id]>=0LL);return;}
	PutDown(id);
	const int mid=(l+r)/2;
	Add(id*2,l,mid,bl,br,v);
	Add(id*2+1,mid+1,r,bl,br,v);
	MN[id]=min(MN[id*2],MN[id*2+1]);
}
struct Line
{
	int x,y1,y2;
	LL cost;
	Line(){}
	Line(const int _x,const int _y1,const int _y2,const LL _c):x(_x),y1(_y1),y2(_y2),cost(_c){}
	bool operator<(const Line &l)const{return x<l.x;}
};
bool Check(const int sidelen)
{
	if(sidelen==0)return true;
//	printf("sidelen=%d\n",sidelen);
	IDX.clear();IDX[0]=IDX[M-sidelen+1]=-1;
	vector<Line>left,right;
	for(const auto &o:OBSTACLE)
	{
		const int y1=max(0,o.y1-1-sidelen+1);
		const int y2=min(M-sidelen+1,o.y2);
		const int x1=max(0,o.x1-1-sidelen+1);
		const int x2=o.x2;
		left.push_back(Line(x1,y1,y2,o.cost));
		right.push_back(Line(x2,y1,y2,-o.cost));
		IDX[y1]=IDX[y2]=-1;
	}
	int cnt=0;
	for(auto it=IDX.begin();it!=IDX.end();it++)it->second=cnt++;//,printf("(%d,%d)\n",it->first,it->second);
	for(auto &l:left)l.y1=IDX[l.y1],l.y2=IDX[l.y2],assert(l.y1<l.y2);
	for(auto &l:right)l.y1=IDX[l.y1],l.y2=IDX[l.y2],assert(l.y1<l.y2);
	sort(left.begin(),left.end()),sort(right.begin(),right.end());
	Build(1,0,cnt-2);
	for(int bl=0,l=0,r=0;bl+sidelen<=N;)
	{
		while(l<left.size()&&left[l].x<=bl)Add(1,0,cnt-2,left[l].y1,left[l].y2-1,left[l].cost),l++;//printf("left(%d,%d)\n",left[l].y1,left[l].y2-1),l++;
		while(r<right.size()&&right[r].x<=bl)Add(1,0,cnt-2,right[r].y1,right[r].y2-1,right[r].cost),r++;//printf("right(%d,%d)\n",right[r].y1,right[r].y2),r++;
//		printf("MN[1]=%lld\n",MN[1]);
		if(MN[1]<=B)return true;
		assert(r<right.size());
		bl=right[r].x;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%lld%d",&N,&M,&B,&P)==4)
	{
		OBSTACLE.clear();
		for(int i=0,x1,y1,x2,y2;i<P;i++)
		{
			static LL cost;
			scanf("%d%d%d%d%lld",&x1,&y1,&x2,&y2,&cost);
			OBSTACLE.push_back(Obstacle(x1,y1,x2,y2,cost));
		}
		int l=0,r=min(N,M);
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Check(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
