#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
//#define debug(...) {}//__VA_ARGS__
typedef long long LL;
using namespace std;
struct Point
{
	LL x1,x2,y,t;
	Point(){}
	Point(LL x1,LL x2,LL y,LL t):x1(x1),x2(x2),y(y),t(t){}
	bool operator<(Point a)const{return y!=a.y?y<a.y:t<a.t;}
};
vector<Point> PP,P1,P2;
map<LL,LL> XM,YM;
vector<LL> X,Y;
LL W,H,N,M;
void SortMap(map<LL,LL> &m,vector<LL> &v,LL limit)
{
	LL i=0LL;
	for(map<LL,LL>::iterator it=m.begin();it!=m.end();it++)
	{
		if(it->first<1LL)continue;
		if(it->first>limit)
		{
			it->second=i-1LL;
			continue;
		}
		v.push_back(it->first);
		it->second=i++;
	}
}
LL V[50000*4],ADD[50000*4];
struct Bt
{
	void Clear(LL id,LL l,LL r,vector<LL> &c)
	{
		V[id]=c[r]-c[l]+1LL;
		ADD[id]=0LL;
		if(l==r)return;
		LL mid=(l+r)/2LL,i1=id*2LL,i2=id*2LL+1LL;
		Clear(i1,l,mid,c),Clear(i2,mid+1,r,c);
	}
	void Add(LL id,LL l,LL r,LL L,LL R,LL v,vector<LL> &c)
	{
		if(L<=l&&r<=R)
		{
			ADD[id]+=v;
			return;
		}
		else if(l>R||r<L)return;
		LL mid=(l+r)/2LL,i1=id*2LL,i2=id*2LL+1LL;
		Add(i1,l,mid,L,R,v,c),Add(i2,mid+1LL,r,L,R,v,c);
		V[id]=Query(i1,l,mid,c)+Query(i2,mid+1LL,r,c);
	}
	LL Query(LL id,LL l,LL r,vector<LL> &c)
	{
		if(ADD[id])return 0LL;
		return V[id];
	}
}BT;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld%lld",&W,&H,&N,&M)==4)
	{
		PP.clear(),P1.clear(),P2.clear(),XM.clear(),YM.clear(),X.clear(),Y.clear();
		XM[1LL]=XM[W-M+1LL]=YM[1LL]=YM[H-M+1LL]=0LL;
		for(LL i=0LL,x1,y1,x2,y2,sz;i<N;i++)
		{
			scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
			XM[x2]=YM[y2]=XM[x1-M+1LL]=YM[y1-M+1LL]=0LL;
			PP.push_back(Point(x1,y1,x2,y2));
		}
		SortMap(XM,X,W-M+1LL),SortMap(YM,Y,H-M+1LL);
		for(LL i=0LL;i<N;i++)
		{
			Point &p=PP[i];
			LL &x1=p.x1,&y1=p.x2,&x2=p.y,&y2=p.t,&xm=XM[x1-M+1LL],&ym=YM[y1-M+1LL];
			P1.push_back(Point(xm,XM[x2],y1,1LL));
			P1.push_back(Point(xm,XM[x2],y2+1LL,-1LL));
			P2.push_back(Point(ym,YM[y2],x1,1LL));
			P2.push_back(Point(ym,YM[y2],x2+1LL,-1LL));
		}
		sort(P1.begin(),P1.end()),sort(P2.begin(),P2.end());
		LL ans=0LL;
		if(W>=M)
		{
			LL sz=X.size();sz--;
			BT.Clear(1LL,0LL,sz,X);
			for(LL i=0LL,y1=1LL,y2;;)
			{
				while(i<P1.size()&&P1[i].y==y1)
				{
					Point &p=P1[i];
					BT.Add(1LL,0LL,sz,p.x1,p.x2,p.t,X);
					i++;
				}
				y2=i==P1.size()?H:P1[i].y-1LL;
				ans+=(y2-y1+1LL)*BT.Query(1LL,0LL,sz,X);
				y1=++y2;
				if(i==P1.size())break;
			}
		}
		if(M>1LL&&H>=M)
		{
			LL sz=Y.size();sz--;
			BT.Clear(1LL,0LL,sz,Y);
			for(LL i=0LL,y1=1LL,y2;;)
			{
				while(i<P2.size()&&P2[i].y==y1)
				{
					Point &p=P2[i];
					BT.Add(1LL,0LL,sz,p.x1,p.x2,p.t,Y);
					i++;
				}
				y2=i==P2.size()?W:P2[i].y-1LL;
				ans+=(y2-y1+1LL)*BT.Query(1LL,0LL,sz,Y);
				y1=++y2;
				if(i==P2.size())break;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
