#include<cstdio>
#include<vector>
#include<algorithm>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
using namespace std;
typedef long long LL;
LL W,H,N,M;
LL max(LL a,LL b){return a>b?a:b;}
LL min(LL a,LL b){return a<b?a:b;}
struct Point
{
	LL x1,x2,y,v;
	Point(){}
	Point(LL x1,LL x2,LL y,LL v):x1(x1),x2(x2),y(y),v(v){}
	bool operator<(Point a)const{return y!=a.y?y<a.y:v<a.v;}
};
vector<Point> P1,P2;
LL V[40000000],ADD[40000000];
struct Bst
{
	void clear(LL id,LL l,LL r)
	{
		V[id]=r-l+1LL;
		ADD[id]=0LL;
		if(l==r)return;
		LL mid=(l+r)/2LL,i1=id*2LL,i2=id*2LL+1LL;
		clear(i1,l,mid),clear(i2,mid+1LL,r);
	}
	void Add(LL id,LL l,LL r,LL L,LL R,LL v)
	{
		if(L<=l&&r<=R)
		{
			ADD[id]+=v;
			return;
		}
		if(r<L||l>R)return;
		LL mid=(l+r)/2LL,i1=id*2LL,i2=id*2LL+1LL;
		Add(i1,l,mid,L,R,v),Add(i2,mid+1LL,r,L,R,v);
		V[id]=Query(i1,l,mid)+Query(i2,mid+1LL,r);
	}
	LL Query(LL id,LL l,LL r)
	{
		if(ADD[id])return 0LL;
		return V[id];
	}
}BST;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld%lld",&W,&H,&N,&M)==4)
	{
		P1.clear(),P2.clear();
		LL Mm1=M-1LL;
		for(LL i=0LL,x1,y1,x2,y2;i<N;i++)
		{
			scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
			P1.push_back(Point(max(1LL,x1-Mm1),min(x2,W-Mm1),y1,1LL));
			P1.push_back(Point(max(1LL,x1-Mm1),min(x2,W-Mm1),y2+1LL,-1LL));
			P2.push_back(Point(max(1LL,y1-Mm1),min(y2,H-Mm1),x1,1LL));
			P2.push_back(Point(max(1LL,y1-Mm1),min(y2,H-Mm1),x2+1LL,-1LL));
		}
		sort(P1.begin(),P1.end()),sort(P2.begin(),P2.end());
		LL ans=0LL;
		if(W>=M)
		{
			BST.clear(1LL,1LL,W-Mm1);
			for(LL i=0LL,y1=1LL,y2;;)
			{
				while(i<P1.size()&&y1==P1[i].y)
				{
					Point &p=P1[i];
					BST.Add(1LL,1LL,W-Mm1,p.x1,p.x2,p.v);
					i++;
				}
				y2=i==P1.size()?H:P1[i].y-1LL;
				ans+=(y2-y1+1LL)*BST.Query(1LL,1LL,W-Mm1);
				if(i==P1.size())break;
				y1=++y2;
			}
			LL tmp=BST.Query(1LL,1LL,W-Mm1);if(tmp!=W-Mm1)termin("error%lld\n",tmp);
		}
		if(M>1LL&&H>=M)
		{
			BST.clear(1LL,1LL,H-Mm1);
			for(LL i=0LL,y1=1LL,y2;;)
			{
				while(i<P2.size()&&y1==P2[i].y)
				{
					Point &p=P2[i];
					BST.Add(1LL,1LL,H-Mm1,p.x1,p.x2,p.v); 
					i++;
				}
				y2=i==P2.size()?W:P2[i].y-1LL;
				ans+=(y2-y1+1LL)*BST.Query(1LL,1LL,H-Mm1);
				if(i==P2.size())break;
				y1=++y2;
			}
			LL tmp=BST.Query(1LL,1LL,W-Mm1);if(tmp!=H-Mm1)termin("error%lld\n",tmp);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
