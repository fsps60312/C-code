#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
int T,N;
void getmin(int &a,int b){if(b<a)a=b;}
struct Tria
{
	int x,y,z;
	Tria(){}
	Tria(int x,int y,int z):x(x),y(y),z(z){}
	Tria(const Tria &a):x(a.x),y(a.y),z(a.z){}
	void rotate60()
	{
		int a,b;
		a=x+y+z;
		b=-x-1;
		x=a,y=b;
		z^=1;
	}
	bool operator==(Tria a)const{return x==a.x&&y==a.y&&z==a.z;}
	bool operator!=(Tria a)const{return x!=a.x||y!=a.y||z!=a.z;}
	bool operator<(Tria a)const
	{
		if(x!=a.x)return x<a.x;
		if(y!=a.y)return y<a.y;
		return z<a.z;
	}
};
struct Shape
{
	Tria tria[16];
	int sz;
	Shape():sz(1){tria[0]=Tria(0,0,0);}
	Shape(const Shape &s):sz(s.sz){for(int i=0;i<sz;i++)tria[i]=s.tria[i];}
	Shape(Tria *t,int sz):sz(sz){for(int i=0;i<sz;i++)tria[i]=t[i];}
	void carry()
	{
		int x,y;x=y=2147483647;
		for(int i=0;i<sz;i++)getmin(x,tria[i].x),getmin(y,tria[i].y);
		for(int i=0;i<sz;i++)tria[i].x-=x,tria[i].y-=y;
		sort(tria,tria+sz);
	}
	bool operator<(Shape a)const
	{
		if(sz!=a.sz)return sz<a.sz;
		for(int i=0;i<sz;i++)
			if(tria[i]!=a.tria[i])return tria[i]<a.tria[i];
		return false;
	}
	void rotate60()
	{
		for(int i=0;i<sz;i++)tria[i].rotate60();
		carry();
	}
	bool contains(Tria t)
	{
		int l=0,r=sz-1,mid;
		while(l<r)
		{
			mid=(l+r)/2;
			if(tria[mid]<t)l=mid+1;
			else r=mid;
		}
		return tria[l]==t;
	}
	void add(set<Shape> &m,int x,int y,int z)
	{
		Tria t;t=Tria(x,y,z);
		if(contains(t))return;
		tria[sz]=t;
		Shape s;
		s=Shape(tria,sz+1);
		for(int i=0;i<6;i++)
		{
			s.rotate60();
			if(m.find(s)!=m.end())return;
		}
		m.insert(s);
	}
	void add(set<Shape> &m)
	{
		for(int i=0;i<sz;i++)
		{
			Tria &t=tria[i];
			add(m,t.x,t.y,t.z^1);
			if(t.z)
			{
				add(m,t.x+1,t.y,t.z^1);
				add(m,t.x,t.y+1,t.z^1);
			}
			else
			{
				add(m,t.x-1,t.y,t.z^1);
				add(m,t.x,t.y-1,t.z^1);
			}
		}
	}
};
int main()
{
	int ans[17]={0,1,1,1,4,6,19,43,120,307,866,2336,6588,18373,52119,147700,422016};
	/*set<Shape> pre,now;
	now.insert(Shape());
	ans[1]=1;
	for(int i=2;i<=16;i++)
	{
		pre=now;
		now.clear();
		for(set<Shape>::iterator it=pre.begin();it!=pre.end();it++)
		{
			Shape s=*it;
			s.add(now);
		}
		ans[i]=now.size();
		printf("%d:%d\n",i,ans[i]);
	}*/
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&N);
		printf("Case #%d: %d\n",kase++,ans[N]);
	}
	return 0;
}
