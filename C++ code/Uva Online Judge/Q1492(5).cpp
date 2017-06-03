#include<cstdio>
#include<vector>
#include<algorithm>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
using namespace std;
typedef long long LL;
LL W,H,N,M;
struct Point
{
	LL x1,x2,y,t;
	Point(){}
	Point(LL x1,LL x2,LL y,LL t):x1(x1),x2(x2),y(y),t(t){}
	bool operator<(Point a)const
	{
		if(y!=a.y)return y<a.y;
		return t>a.t;
	}
};
vector<Point> P1,P2;
LL TAG[40000000],ADDN[40000000],V[40000000];
struct Bt
{
	void Clear(LL sz){TAG[1]=1LL,ADDN[1]=1LL,V[1]=sz;}
	void PutDown(LL id,LL l,LL r,LL mid)
	{
		if(TAG[id]!=1LL)return;
		LL i1=id*2LL,i2=id*2LL+1LL;
		TAG[i1]=TAG[i2]=1LL,TAG[id]=0LL;
		ADDN[i1]=ADDN[i2]=ADDN[id];
		V[i1]=(mid-l+1LL)*ADDN[i1],V[i2]=(r-mid)*ADDN[i2];
	}
	void Modify(LL id,LL l,LL r,LL L,LL R,LL v)
	{
		if(l>=L&&r<=R)
		{
			TAG[id]=1LL;
			ADDN[id]=v;
			V[id]=v*(r-l+1LL);
			return;
		}
		if(l>R||r<L)return;
		LL mid=(l+r)/2LL;
		PutDown(id,l,r,mid);
		LL i1=id*2LL,i2=id*2LL+1LL;
		Modify(i1,l,mid,L,R,v);
		Modify(i2,mid+1LL,r,L,R,v);
		V[id]=V[i1]+V[i2];
	}
	LL Query(LL id,LL l,LL r,LL L,LL R)
	{
		if(l>=L&&r<=R)return V[id];
		else if(l>R||r<L)return 0LL;
		LL mid=(l+r)/2LL;
		PutDown(id,l,r,mid);
		return Query(id*2LL,l,mid,L,R)+Query(id*2LL+1LL,mid+1LL,r,L,R);
	}
}BT;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld%lld",&W,&H,&N,&M)==4)
	{
		P1.clear(),P2.clear();
		for(LL i=0LL,x1,x2,y1,y2,tmp;i<N;i++)
		{
			scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
			if(x1>x2)tmp=x1,x1=x2,x2=tmp;
			if(y1>y2)tmp=y1,y1=y2,y2=tmp;
			P1.push_back(Point(x1,x2,y1,0LL));
			P1.push_back(Point(x1,x2,y2+1LL,1LL));
			P2.push_back(Point(y1,y2,x1,0LL));
			P2.push_back(Point(y1,y2,x2+1LL,1LL));
		}
		sort(P1.begin(),P1.end());
		sort(P2.begin(),P2.end());
		LL ans=0LL;
		if(W-M+1LL>0LL)
		{
			BT.Clear(W-M+1LL);
			for(LL i=0LL,y1=1LL,y2=1LL;;)
			{
				while(i<P1.size()&&P1[i].y==y1)
				{
					Point &p=P1[i];
					BT.Modify(1LL,1LL,W-(M-1LL),p.x1-(M-1LL),p.x2,p.t);
					i++;
				}
				y2=(i==P1.size()?H:P1[i].y-1LL);
				ans+=(y2-y1+1LL)*BT.Query(1LL,1LL,W-(M-1LL),1LL,W-(M-1LL));
				y1=++y2;
				if(i==P1.size())break;
			}
			LL check=BT.Query(1LL,1LL,W-(M-1LL),1LL,W-(M-1LL));
			if(check!=W-(M-1LL))termin("should be cleared %d %d\n",check,W-(M-1LL));
		}
		if(M>1LL&&H-M+1LL>0LL)
		{
			BT.Clear(H-M+1LL);
			for(LL i=0LL,y1=1LL,y2=1LL;;)
			{
				while(i<P2.size()&&P2[i].y==y1)
				{
					Point &p=P2[i];
					BT.Modify(1LL,1LL,H-(M-1LL),p.x1-(M-1LL),p.x2,p.t);
					i++;
				}
				y2=(i==P2.size()?W:P2[i].y-1LL);
				ans+=(y2-y1+1LL)*BT.Query(1LL,1LL,H-(M-1LL),1LL,H-(M-1LL));
				y1=++y2;
				if(i==P2.size())break;
			}
			LL check=BT.Query(1LL,1LL,H-(M-1LL),1LL,H-(M-1LL));
			if(check!=H-(M-1LL))termin("should be cleared %d %d\n",check,H-(M-1LL));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
