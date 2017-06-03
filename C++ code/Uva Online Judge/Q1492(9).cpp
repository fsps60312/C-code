#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1);}
#define debug(x,...) {}//{printf(x,##__VA_ARGS__);}
#define debu2(x,...) {}//{printf(x,##__VA_ARGS__);}
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
vector<LL> X,Y;
map<LL,LL> XM,YM;
struct Bst
{
	void clear(LL id,LL l,LL r,vector<LL> &c)
	{
		V[id]=c[r+1LL]-c[l];//c[1]==2,c[3]==7,V[id] means 2~6
//		debu2("%lld(%lld,%lld):%lld\n",id,l,r,V[id]);
		ADD[id]=0LL;
		if(l==r)return;
		LL mid=(l+r)/2LL,i1=id*2LL,i2=id*2LL+1LL;
		clear(i1,l,mid,c),clear(i2,mid+1LL,r,c);
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
		P1.clear(),P2.clear(),X.clear(),Y.clear(),XM.clear(),YM.clear();
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
		///////////////////////////////////////////////////////
		LL cnt=0LL;
		XM[1LL]=0LL;
		for(LL i=0LL;i<P1.size();i++)
		{
			Point &p=P1[i];
			XM[p.x1]=XM[p.x2+1LL]=0LL;
			debug("P1%lld %lld\n",p.x1,p.x2);
		}debug("\n");
		for(map<LL,LL>::iterator it=XM.begin();it!=XM.end();it++)
		{
			it->second=cnt++;
			X.push_back(it->first);
			debug("XM(%lld,%lld)",it->first,it->second);
		}debug("\n");
		X.push_back(W-Mm1+1LL);
		for(LL i=0LL;i<P1.size();i++)
		{
			Point &p=P1[i];
			p.x1=XM[p.x1],p.x2=XM[p.x2+1LL]-1LL;
			debug("X%lld %lld\n",p.x1,p.x2);
		}debug("\n");
		///////////////////////////////////////////////////////
		cnt=0LL;
		YM[1LL]=0LL;
		for(LL i=0LL;i<P2.size();i++)
		{
			Point &p=P2[i];
			YM[p.x1]=YM[p.x2+1LL]=0LL;
			debug("P2%lld %lld\n",p.x1,p.x2);
		}debug("\n");
		for(map<LL,LL>::iterator it=YM.begin();it!=YM.end();it++)
		{
			it->second=cnt++;
			Y.push_back(it->first);
			debug("YM(%lld,%lld)",it->first,it->second);
		}debug("\n");
		Y.push_back(H-Mm1+1LL);
		for(LL i=0LL;i<P2.size();i++)
		{
			Point &p=P2[i];
			p.x1=YM[p.x1],p.x2=YM[p.x2+1LL]-1LL;
			debug("Y%lld %lld\n",p.x1,p.x2);
		}debug("\n");
		///////////////////////////////////////////////////////
		LL ans=0LL;
		if(W>=M)
		{
			LL BD=X.size();BD-=2LL;
			BST.clear(1LL,0LL,BD,X);
			for(LL i=0LL,y1=1LL,y2;;)
			{
				while(i<P1.size()&&y1==P1[i].y)
				{
					Point &p=P1[i];
					BST.Add(1LL,0LL,BD,p.x1,p.x2,p.v);
					i++;
				}
				y2=i==P1.size()?H:P1[i].y-1LL;
				debu2("X%lld*%lld=%lld\n",(y2-y1+1LL),BST.Query(1LL,0LL,BD),(y2-y1+1LL)*BST.Query(1LL,0LL,BD));
				ans+=(y2-y1+1LL)*BST.Query(1LL,0LL,BD);
				if(i==P1.size())break;
				y1=++y2;
			}
			LL tmp=BST.Query(1LL,0LL,BD);if(tmp!=W-Mm1)termin("error%lld\n",tmp);
		}
		if(M>1LL&&H>=M)
		{
			LL BD=Y.size();BD-=2LL;
			BST.clear(1LL,0LL,BD,Y);
			for(LL i=0LL,y1=1LL,y2;;)
			{
				while(i<P2.size()&&y1==P2[i].y)
				{
					Point &p=P2[i];
					BST.Add(1LL,0LL,BD,p.x1,p.x2,p.v); 
					i++;
				}
				y2=i==P2.size()?W:P2[i].y-1LL;
				debu2("Y%lld*%lld=%lld\n",(y2-y1+1LL),BST.Query(1LL,0LL,BD),(y2-y1+1LL)*BST.Query(1LL,0LL,BD));
				ans+=(y2-y1+1LL)*BST.Query(1LL,0LL,BD);
				if(i==P2.size())break;
				y1=++y2;
			}
			LL tmp=BST.Query(1LL,0LL,BD);if(tmp!=H-Mm1)termin("error%lld\n",tmp);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
