#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#define debug(x,...) {}//printf(x,__VA_ARGS__)
using namespace std;
const int INF=2147483647;
struct Point
{
	int x,y,ur,ul,dr,dl;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};
vector<Point>P;
int N,X,Y;
void reindex()
{
	map<int,int>x,y;
	for(int i=0;i<P.size();i++)
	{
		Point &p=P[i];
		x[p.x]=y[p.y]=0;
	}
	int idx=1;
	for(map<int,int>::iterator it=x.begin();it!=x.end();it++)it->second=idx++;
	idx=1;
	for(map<int,int>::iterator it=y.begin();it!=y.end();it++)it->second=idx++;
	X=x.size(),Y=y.size();
	for(int i=0;i<P.size();i++)
	{
		Point &p=P[i];
		p.x=x[p.x],p.y=y[p.y];
	}
}
bool cmpl(Point a,Point b){return a.x>b.x;}
bool cmpr(Point a,Point b){return a.x<b.x;}
struct Bt
{
	int *bse,sz;
	void clear(int _sz)
	{
		sz=_sz;
		bse=new int[sz+1];
		for(int i=1;i<=sz;i++)bse[i]=0;
	}
	int lowbit(int i){return i&(-i);}
	void add(int i,int v)
	{
		while(i<=sz)
		{
			bse[i]+=v;
			i+=lowbit(i);
		}
	}
	int query(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=bse[i];
			i-=lowbit(i);
		}
		return ans;
	}
	void build()
	{
		clear(Y);
		for(int i=0;i<P.size();i++)add(P[i].y,1);
	}
}BT;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		P.clear();
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			P.push_back(Point(x,y));
		}
		reindex();
		debug("X=%d,Y=%d\n",X,Y);
		sort(P.begin(),P.end(),cmpl);//<-
		BT.build();
		for(int i=0,ti,cnt=N,xnow;i<P.size();)
		{
			for(ti=i,xnow=P[i].x;ti<P.size()&&P[ti].x==xnow;ti++,cnt--)BT.add(P[ti].y,-1);
			for(;i<ti;i++)P[i].ul=cnt-BT.query(P[i].y),P[i].dl=BT.query(P[i].y-1);
			i=ti;
		}
		sort(P.begin(),P.end(),cmpr);//->
		BT.build();
		for(int i=0,ti,cnt=N,xnow;i<P.size();)
		{
			for(ti=i,xnow=P[i].x;ti<P.size()&&P[ti].x==xnow;ti++,cnt--)BT.add(P[ti].y,-1);
			for(;i<ti;i++)P[i].ur=cnt-BT.query(P[i].y),P[i].dr=BT.query(P[i].y-1);
			i=ti;
		}
		int mine=-1;
		set<int>ans;
		for(int i=0,ti,v1=INF,v2=-1,u1,u2,xnow;i<P.size();v1=INF,v2=-1)
		{
			for(ti=i,xnow=P[i].x;ti<P.size()&&P[ti].x==xnow;ti++)
			{
				Point &p=P[ti];
				u1=p.ur+p.dl,u2,u2=p.ul+p.dr;
				debug("(%d,%d):%d,%d\n",p.x,p.y,u1,u2);
				if(u1<v1||(u1==v1&&u2>v2))v1=u1,v2=u2;
			}
			if(v1>mine)mine=v1,ans.clear();
			if(v1==mine)ans.insert(v2);
			i=ti;
		}
		debug("ians=%d,mine=%d,oppo=%d,x=%d,y=%d\n",ians,mine,oppo,P[ians].x,P[ians].y);
		printf("Stan: %d; Ollie:",mine);
		for(set<int>::iterator it=ans.begin();it!=ans.end();it++)printf(" %d",*it);puts(";");
	}
	return 0;
}
