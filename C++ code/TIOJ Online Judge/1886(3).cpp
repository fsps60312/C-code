#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y):x(_x),y(_y){}
	bool operator<(const Point &p)const{return y!=p.y?y<p.y:x<p.x;}
};
int N,PID[500001];
void BuildPID(const vector<Point>&p)
{
	int i=-1;
	for(int y=0;y<=N;y++)
	{
		while(i+1<=N&&p[i+1].y<=y)i++;
		PID[y]=i;
	}
}
struct Node
{
	Node *ch[2];
	int sum;
}*TREE[500001],BUFFER[500000*24],*NEW;
Node *NewNode(const int _sum)
{
	NEW->ch[0]=NEW->ch[1]=NULL;
	NEW->sum=_sum;
	return NEW++;
}
Node *Build(int l,int r)
{
	Node *ans=NewNode(0);
	if(l<r)
	{
		const int mid=(l+r)/2;
		ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	}
	return ans;
}
Node *Add(Node *o,int l,int r,int loc)
{
	Node *ans=NewNode(o->sum+1);
	if(l==r){assert(r==loc);return ans;}
	const int mid=(l+r)/2;
	if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc),ans->ch[1]=o->ch[1];
	else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc);
	return ans;
}
int QuerySum(Node *lo,Node *ro,int l,int r,int loc)
{
	if(l==r){assert(loc==r);return ro->sum-lo->sum;}
	const int mid=(l+r)/2;
	if(loc<=mid)return QuerySum(lo->ch[0],ro->ch[0],l,mid,loc);
	else return (ro->ch[0]->sum-lo->ch[0]->sum)+QuerySum(lo->ch[1],ro->ch[1],mid+1,r,loc);
}
int QueryLoc(Node *lo,Node *ro,int l,int r,int sum)
{
	if(l==r){assert(sum==1&&ro->sum-lo->sum==1);return r;}
	const int mid=(l+r)/2;
	const int lsum=ro->ch[0]->sum-lo->ch[0]->sum;
	if(lsum>=sum)return QueryLoc(lo->ch[0],ro->ch[0],l,mid,sum);
	else return QueryLoc(lo->ch[1],ro->ch[1],mid+1,r,sum-lsum);
}
void BuildPlane(const vector<Point>&p)
{
	vector<int>order;
	for(int i=1;i<=N;i++)order.push_back(i);
	sort(order.begin(),order.end(),[&](int a,int b){return p[a].x!=p[b].x?p[a].x<p[b].x:a<b;});
	TREE[0]=Build(0,N);
	for(int x=1,i=0;x<=N;x++)
	{
		TREE[x]=TREE[x-1];
		for(;i<N&&p[order[i]].x<=x;i++)TREE[x]=Add(TREE[x],0,N,order[i]);
	}
}
void InitialPoints()
{
	vector<Point>p;
	p.push_back(Point(0,0));
	for(int i=0,a,b;i<N;i++)scanf("%d%d",&a,&b),p.push_back(Point(a,b));
	sort(p.begin()+1,p.end());
	BuildPID(p);
	BuildPlane(p);
}
bool Solve(const vector<int>&ks)
{
	stack<Point>stk;
	stk.push(Point(0,N));
	for(const int k:ks)
	{
		int lowy=PID[k-1];
		while(!stk.empty()&&stk.top().y<=lowy)stk.pop();
		for(int remain=k;;)
		{
			if(stk.empty())return false;
			Node *lt=TREE[stk.top().x],*rt=TREE[k];
			const int basis=QuerySum(lt,rt,0,N,lowy),supply=QuerySum(lt,rt,0,N,stk.top().y);
			if(supply-basis>=remain)
			{
				stk.push(Point(k,QueryLoc(lt,rt,0,N,basis+remain)));
				break;
			}
			else
			{
				remain-=supply-basis;
				lowy=stk.top().y;
				stk.pop();
			}
		}
	}
	return true;
}
int main()
{
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		NEW=BUFFER;
		scanf("%d",&N);
		InitialPoints();
		int querycount;scanf("%d",&querycount);
		for(int m;querycount--;)
		{
			scanf("%d",&m);
			vector<int>ks;
			for(int v;m--;){scanf("%d",&v);ks.push_back(v);}
			sort(ks.begin(),ks.end());
			puts(Solve(ks)?"1":"0");
		}
	}
}
