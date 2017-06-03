#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
typedef __int128 LL;
template<class T>inline bool IsBetween(const T&v,const T&a,const T&b){return (a<=v&&v<=b)||(b<=v&&v<=a);}
struct Fraction
{
	LL x,y;
	Fraction(){}
	Fraction(const LL &_x,const LL &_y):x(_x),y(_y){}
};
inline pair<pair<LL,LL>,LL>GetCenter(const LL &ax,const LL &ay,const LL &bx,const LL &by,const LL &cx,const LL &cy)
{
	const LL &ax1_2=ax+bx,&ay1_2=ay+by ,&ax2_2=bx+cx,ay2_2=by+cy;
	const LL &vx1=(by-ay),&vy1=-(bx-ax),&vx2=(cy-by),vy2=-(cx-bx);
	const LL &upon=(ax1_2*vy1-ay1_2*vx1)-(ax2_2*vy1-ay2_2*vx1),&down=2*(vx2*vy1-vy2*vx1);
	return make_pair(make_pair(ax2_2*down+upon*vx2*2,ay2_2*down+upon*vy2*2),down*2);
//	ax1+t*vx1=ax2+u*vx2
//	ay1+t*vy1=ay2+u*vy2
//	ax1*vy1+t*vx1*vy1=ax2*vy1+u*vx2*vy1
//	ay1*vx1+t*vy1*vx1=ay2*vx1+u*vy2*vx1
//	ax1*vy1-ay1*vx1=ax2*vy1-ay2*vx1+u*(vx2*vy1-vy2*vx1)
//	(ax1*vy1-ay1*vx1)-(ax2*vy1-ay2*vx1)=u*(vx2*vy1-vy2*vx1)
//	((ax1*vy1-ay1*vx1)-(ax2*vy1-ay2*vx1))/(vx2*vy1-vy2*vx1)=u
//	ax2+u*vx2=(ax2*(vx2*vy1-vy2*vx1)+vx2*((ax1*vy1-ay1*vx1)-(ax2*vy1-ay2*vx1)))/(vx2*vy1-vy2*vx1)
//	ax2+u*vx2=(ax2*vx2*vy1-ax2*vy2*vx1+vx2*ax1*vy1-vx2*ay1*vx1-vx2*ax2*vy1+vx2*ay2*vx1)/(vx2*vy1-vy2*vx1)
//	ax2+u*vx2=(-ax2*vx1*vy2+ax1*vx2*vy1-ay1*vx2*vx1+ay2*vx2*vx1)/(vx2*vy1-vy2*vx1)
}
inline pair<pair<LL,LL>,LL>MidPoint(const LL &ax,const LL &ay,const LL &bx,const LL &by){return make_pair(make_pair(ax+bx,ay+by),(LL)2);}
inline LL Abs(const LL &v){return v>=0?v:-v;}
inline void Calculate(const LL *a,LL *b,const LL &mod)
{
	b[0]=a[0]*a[0];
	b[1]=a[0]*a[1]+a[1]*a[0];
	b[2]=a[1]*a[1];
	b[1]+=b[0]/mod,b[0]%=mod;
	b[2]+=b[1]/mod,b[1]%=mod;
}
inline bool IsSmallOrEqual(const pair<pair<LL,LL>,LL>&o,const LL &x,const LL &y,const LL &r)
{
	const LL &dx=Abs(o.first.first-x*o.second),&dy=Abs(o.first.second-y*o.second),&dr=r*o.second;
	const LL &mod=1000000000000000000LL;
	LL xs[2]={dx%mod,dx/mod},ys[2]={dy%mod,dy/mod},rs[2]={dr%mod,dr/mod};
	LL xx[3],yy[3],rr[3];
	Calculate(xs,xx,mod);
	Calculate(ys,yy,mod);
	Calculate(rs,rr,mod);
	xx[0]+=yy[0];
	xx[1]+=yy[1];
	xx[2]+=yy[2];
	xx[1]+=xx[0]/mod,xx[0]%=mod;
	xx[2]+=xx[1]/mod,xx[1]%=mod;
	if(xx[2]!=rr[2])return xx[2]<=rr[2];
	if(xx[1]!=rr[1])return xx[1]<=rr[1];
	return xx[0]<rr[0];
//	return dx*dx+dy*dy<=dr*dr;
}
int X[50],Y[50];
inline bool Coline(const int ai,const int bi,const int ci)
{
	int x1=X[ai]-X[bi],y1=Y[ai]-Y[bi],x2=X[bi]-X[ci],y2=Y[bi]-Y[ci];
	return /*x1:y1=x2:y2*/(LL)x1*y2==(LL)y1*x2;
}
inline bool CmpPoint(const int a,const int b)
{
	if(X[a]!=X[b])return X[a]<X[b];
	return Y[a]<Y[b];
}
inline pair<pair<LL,LL>,LL>GetCenter(const int ai,const int bi,const int ci)
{
	if(Coline(ai,bi,ci))
	{
		int a=ai,b=bi,c=ci;
		if(!CmpPoint(a,b))swap(a,b);
		if(!CmpPoint(b,c))swap(b,c);
		if(!CmpPoint(a,b))swap(a,b);
		assert(IsBetween(X[b],X[a],X[c])&&IsBetween(Y[b],Y[a],Y[c]));
		return MidPoint(X[a],Y[a],X[c],Y[c]);
	}
	return GetCenter(X[ai],Y[ai],X[bi],Y[bi],X[ci],Y[ci]);
}
int N,R;
vector<int>INREC[50];
int GetMaxPoints(const vector<int>&s)
{
	static bool vis[50];
	for(int i=0;i<50;i++)vis[i]=false;
	for(const int i:s)vis[i]=true;
	int ans=0;
	for(const int i:s)
	{
		vector<int>t;
		for(const int j:INREC[i])if(vis[j])t.push_back(j);
		for(int l=0,r=0;r<(int)t.size();r++)
		{
			while(X[t[r]]-X[t[l]]>R)++l;
			getmax(ans,r-l+1);
		}
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	FILE *out=fopen("out.txt","w");
//	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&R);
		{
			vector<pair<int,int> >s;
			for(int i=0,x,y;i<N;i++)
			{
				scanf("%d%d",&x,&y);
				s.push_back(make_pair(x,y));
			}
			sort(s.begin(),s.end());
			for(int i=0;i<N;i++)
			{
				X[i]=s[i].first,Y[i]=s[i].second;
			}
			for(int i=0;i<N;i++)
			{
				INREC[i].clear();
				for(int j=0;j<N;j++)
				{
					if(X[i]-X[j]<=R&&X[j]-X[i]<=R&&Y[i]<=Y[j]&&Y[j]<=Y[i]+R)INREC[i].push_back(j);
				}
			}
		}
		int ans=0;
		for(int ai=0;ai<N;ai++)for(int bi=ai;bi<N;bi++)for(int ci=bi;ci<N;ci++)
		{
			const pair<pair<LL,LL>,LL>&p=GetCenter(ai,bi,ci);
			vector<int>inside,ouside;
			for(int i=0;i<N;i++)(IsSmallOrEqual(p,X[i],Y[i],R)?inside:ouside).push_back(i);
			getmax(ans,GetMaxPoints(inside)+GetMaxPoints(ouside));
		}
		static int kase=0;
		fprintf(out,"Case #%d: %d\n",++kase,ans);
		printf("Case #%d\n",kase);
	}
	fclose(out);
	return 0;
}
