#include<cstdio>
#include<vector>
#include<algorithm>
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
vector<Point> P;
LL TAG[40000000],ADDN[40000000];
struct Bt
{
	void Clear(){TAG[1]=1LL,ADDN[1]=0LL;}
	void PutDown(LL id)
	{
		if(TAG[id]!=1LL)return;
		LL i1=id*2LL,i2=id*2LL+1LL;
		TAG[i1]=TAG[i2]=1LL;
		ADDN[i1]=ADDN[i2]=ADDN[id];
		TAG[id]=0LL; 
	}
	void Add(LL id,LL l,LL r,LL L,LL R,LL v)
	{
		if(l>=L&&r<=R&&TAG[id]==1LL)
		{
			ADDN[id]+=v;
			return;
		}
		else if(l>R||r<L)return;
		LL mid=(l+r)/2LL;
		PutDown(id);
		LL i1=id*2LL,i2=id*2LL+1LL;
		Add(i1,l,mid,L,R,v);
		Add(i2,mid+1LL,r,L,R,v);
		if(TAG[i1]==1LL&&TAG[i2]==1LL&&ADDN[i1]==ADDN[i2])TAG[id]=1LL,ADDN[id]=ADDN[i1];
	}
	LL Query(LL id,LL l,LL r,LL L,LL R)
	{
		if(l>=L&&r<=R&&TAG[id]==1LL)return ADDN[id]==0LL?r-l+1LL:0LL;
		else if(l>R||r<L)return 0LL;
		PutDown(id);
		LL mid=(l+r)/2LL;
		return Query(id*2LL,l,mid,L,R)+Query(id*2LL+1LL,mid+1LL,r,L,R);
	}
}BT;
int main()
{
	while(scanf("%lld%lld%lld%lld",&W,&H,&N,&M)==4)
	{
		W-=M-1;
		P.clear();
		for(LL i=0LL,x1,x2,y1,y2;i<N;i++)
		{
			scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
			P.push_back(Point(x1,x2,y1,0LL));
			P.push_back(Point(x1,x2,y2+1LL,1LL));
		}
		sort(P.begin(),P.end());
		BT.Clear();
		LL ans=0LL;
		for(LL i=0LL,y1=1,y2=1;i<P.size();)
		{
			while(P[i].y==y1)
			{
				Point &p=P[i];
				BT.Add(1,1,W,p.x1-(M-1LL),p.x2,p.t?-1LL:1LL);
				i++;
			}
			y2=i==P.size()?H:P[i].y-1;
			ans+=(y2-y1+1LL)*BT.Query(1LL,1LL,W,1LL,W);
			y1=++y2;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
