#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
#include<cassert>
using namespace std;
typedef unsigned int LL;
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
struct SegMn
{
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
}SEGMN;
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
	left.reserve(P),right.reserve(P);
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
	for(auto it=IDX.begin();it!=IDX.end();it++)it->second=cnt++;
	for(auto &l:left)l.y1=IDX[l.y1],l.y2=IDX[l.y2],assert(l.y1<l.y2);
	for(auto &l:right)l.y1=IDX[l.y1],l.y2=IDX[l.y2],assert(l.y1<l.y2);
	sort(left.begin(),left.end()),sort(right.begin(),right.end());
	SEGMN.Build(1,0,cnt-2);
	for(int bl=0,l=0,r=0;bl+sidelen<=N;)
	{
		while(l<left.size()&&left[l].x<=bl)SEGMN.Add(1,0,cnt-2,left[l].y1,left[l].y2-1,left[l].cost),l++;
		while(r<right.size()&&right[r].x<=bl)SEGMN.Add(1,0,cnt-2,right[r].y1,right[r].y2-1,right[r].cost),r++;
//		printf("MN[1]=%lld\n",MN[1]);
		if(SEGMN.MN[1]<=B)return true;
		assert(r<right.size());
		bl=right[r].x;
	}
	return false;
}
int Solve1()
{
	int l=0,r=min(N,M);
	while(l<r)
	{
		const int mid=(l+r+1)/2;
		if(Check(mid))l=mid;
		else r=mid-1;
	}
	return l;
}
vector<int>RI;
struct Seg0
{
	int lmx[1600000],mmx[1600000],rmx[1600000],cover[1600000];
	void Build(const int id,const int l,const int r)
	{
		lmx[id]=mmx[id]=rmx[id]=RI[r+1]-RI[l];
		cover[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	int Lmx(const int id){return cover[id]?0:lmx[id];}
	int Rmx(const int id){return cover[id]?0:rmx[id];}
	int Mmx(const int id){return cover[id]?0:mmx[id];}
	void Add(const int id,const int l,const int r,const int bl,const int br,const int v)
	{
		if(r<bl||l>br)return;
		if(bl<=l&&r<=br){cover[id]+=v;assert(cover[id]>=0);return;}
		const int mid=(l+r)/2;
		Add(id*2,l,mid,bl,br,v);
		Add(id*2+1,mid+1,r,bl,br,v);
		lmx[id]=(Lmx(id*2)==RI[mid+1]-RI[l]?RI[mid+1]-RI[l]+Lmx(id*2+1):Lmx(id*2));
		rmx[id]=(Rmx(id*2+1)==RI[r+1]-RI[mid+1]?Rmx(id*2)+RI[r+1]-RI[mid+1]:Rmx(id*2+1));
		mmx[id]=max(Rmx(id*2)+Lmx(id*2+1),max(Mmx(id*2),Mmx(id*2+1)));
	}
}SEG0;
int Solve2()
{
	IDX.clear();IDX[0]=IDX[M]=-1;
	vector<Line>left,right;
	left.reserve(P),right.reserve(P);
	for(const auto &o:OBSTACLE)
	{
		const int y1=o.y1-1;
		const int y2=o.y2;
		const int x1=o.x1-1;
		const int x2=o.x2;
//		printf("y1=%d,y2=%d\n",o.y1,o.y2);
		left.push_back(Line(x1,y1,y2,1));
		right.push_back(Line(x2,y1,y2,-1));
		IDX[y1]=IDX[y2]=-1;
	}
	int cnt=0;
	RI.clear();
	for(auto it=IDX.begin();it!=IDX.end();it++)it->second=cnt++,RI.push_back(it->first);
//	for(int i=0;i<cnt;i++)printf("%d:%d\n",i,RI[i]);
	for(auto &l:left)l.y1=IDX[l.y1],l.y2=IDX[l.y2],assert(l.y1<l.y2);
	for(auto &l:right)l.y1=IDX[l.y1],l.y2=IDX[l.y2],assert(l.y1<l.y2);
	sort(left.begin(),left.end()),sort(right.begin(),right.end());
	SEG0.Build(1,0,cnt-2);
//	assert(SEG0.mmx[1]==M);
//	printf("a%d\n",SEG0.mmx[1]);
//	for(int r=0;r<left.size();r++)
//	{
//		SEG0.Add(1,0,cnt-2,left[r].y1,left[r].y2-1,left[r].cost);
//		printf("(%d,%d)\n",left[r].y1,left[r].y2);
//		printf("b(%d,%d,%d)\n",SEG0.lmx[1],SEG0.mmx[1],SEG0.rmx[1]);
//	}
//	for(int l=0;l<right.size();l++)
//	{
//		SEG0.Add(1,0,cnt-2,right[l].y1,right[l].y2-1,right[l].cost);
//		printf("(%d,%d)\n",right[l].y1,right[l].y2);
//		printf("b(%d,%d,%d)\n",SEG0.lmx[1],SEG0.mmx[1],SEG0.rmx[1]);
//	}
//	puts("pass");
	assert(SEG0.mmx[1]==M);
	int ans=left[0].x;
	for(int r=0,l=0,bl=0,br;r<left.size();r++)
	{
		SEG0.Add(1,0,cnt-2,left[r].y1,left[r].y2-1,left[r].cost);
		br=(r+1==left.size()?N:left[r+1].x);
		ans=max(ans,min(SEG0.mmx[1],br-bl));
//		printf("(%d,%d)r=%d\n",bl,br,r);
		while(right[l].x<=br&&br-bl>=SEG0.mmx[1])
		{
			SEG0.Add(1,0,cnt-2,right[l].y1,right[l].y2-1,right[l].cost);
			bl=right[l++].x;
			ans=max(ans,min(SEG0.mmx[1],br-bl));
//			printf("(%d,%d)\n",bl,br);
		}
	}
//	puts("pass");
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%u%d",&N,&M,&B,&P)==4)
	{
		OBSTACLE.clear();
		for(int i=0,x1,y1,x2,y2;i<P;i++)
		{
			static LL cost;
			scanf("%d%d%d%d%u",&x1,&y1,&x2,&y2,&cost);
			OBSTACLE.push_back(Obstacle(x1,y1,x2,y2,cost));
		}
		printf("%d\n",B>0?Solve1():Solve2());
	}
	return 0;
}
