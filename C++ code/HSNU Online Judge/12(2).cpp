#include<cstdio>
#include<vector>
#include<algorithm>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
using namespace std;
struct Point
{
	int x1,x2,y,v;
	Point(){}
	Point(int x1,int x2,int y,int v):x1(x1),x2(x2),y(y),v(v){}
	bool operator<(Point a)const{return y!=a.y?y<a.y:v<a.v;}
};
vector<Point> P;
int V[120000],ADD[120000];
struct Bt
{
	void Clear(int id,int l,int r)
	{
//		printf(" %d",id);
		V[id]=ADD[id]=0;
		if(l==r)return;
		int mid=(l+r)/2;
		Clear(id*2,l,mid);
		Clear(id*2+1,mid+1,r);
	}
//	void PutDown(int &id,int &l,int &r,int &mid)
//	{
//		if(!ADD[id])return;
//		int i1=id*2,i2=id*2+1;
//		ADD[i1]+=ADD[id],ADD[i2]+=ADD[id];
////		V[id]+=ADD[id]*(r-l+1);
//		ADD[id]=0;
//	}
	void Add(int id,int l,int r,int L,int R,int v)
	{
		if(L<=l&&r<=R)
		{
			ADD[id]+=v;
			return;
		}
		else if(l>R||r<L)return;
		int mid=(l+r)/2;
		int i1=id*2,i2=id*2+1;
//		PutDown(id,l,r,mid);
		Add(i1,l,mid,L,R,v);
		Add(i2,mid+1,r,L,R,v);
		V[id]=Query(i1,l,mid)+Query(i2,mid+1,r);
	}
	int Query(int id,int l,int r)
	{
		if(ADD[id])return r-l+1;
		return V[id];
	}
}BT;
int N;
int main()
{
	while(scanf("%d",&N)==1)
	{
		P.clear();
		for(int i=0,x1,y1,x2,y2;i<N;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x2--;
			P.push_back(Point(x1,x2,y1,1));
			P.push_back(Point(x1,x2,y2,-1));
		}
		sort(P.begin(),P.end());
		int ans=0;
		BT.Clear(1,0,29999);
		if(P.size())
		{
			for(int i=0,y1=P[0].y,y2=0;;)
			{
				while(i<P.size()&&y1==P[i].y)
				{
					Point &p=P[i];
//					printf("%d %d %d %d\n",P[i].x1,P[i].x2,P[i].y,P[i].v);
					BT.Add(1,0,29999,p.x1,p.x2,p.v);
					i++;
				}
				if(i==P.size())break;
				y2=P[i].y-1;
//				printf("%d*%d=%d\n",(y2-y1+1),BT.Query(1,0,29999),(y2-y1+1)*BT.Query(1,0,29999));
				ans+=(y2-y1+1)*BT.Query(1,0,29999);
				y1=++y2;
			}
		}
		if(BT.Query(1,0,29999))termin("%d must be zero\n",BT.Query(1,0,29999));
		printf("%d\n",ans);
	}
	return 0;
}
