#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
#include<stack>
using namespace std;
const int INF=2147483647;
struct Node
{
	Node *ch[2];
	int sum;
}Node_BUFFER[500000*24],*NEW;
Node *NewNode(const int _sum)
{
	NEW->ch[0]=NEW->ch[1]=NULL;
	NEW->sum=_sum;
	return NEW++;
}
Node *Build(const int l,const int r)
{
	Node *ans=NewNode(0);
	if(l<r)
	{
		const int mid=(l+r)/2;
		ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	}
	return ans;
}
Node *Add(Node *o,const int l,const int r,const int loc)
{
	Node *ans=NewNode(o->sum+1);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc),ans->ch[1]=o->ch[1];
		else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc);
	}
	return ans;
}
int QueryLoc(Node *lo,Node *ro,const int l,const int r,const int sum)
{
	if(l==r){assert(sum==1&&ro->sum-lo->sum==sum);return r;}
	const int mid=(l+r)/2;
	const int lsum=ro->ch[0]->sum-lo->ch[0]->sum;
	if(sum<=lsum)return QueryLoc(lo->ch[0],ro->ch[0],l,mid,sum);
	else return QueryLoc(lo->ch[1],ro->ch[1],mid+1,r,sum-lsum);
}
int QuerySum(Node *lo,Node *ro,const int l,const int r,const int loc)
{
	if(l==r){assert(loc==r);return ro->sum-lo->sum;}
	const int mid=(l+r)/2;
	if(loc<=mid)return QuerySum(lo->ch[0],ro->ch[0],l,mid,loc);
	else return (ro->ch[0]->sum-lo->ch[0]->sum)+QuerySum(lo->ch[1],ro->ch[1],mid+1,r,loc);
}
struct Point
{
	int x,y;
	Point(){}
	Point(const int _x,const int _y):x(_x),y(_y){}
	bool operator<(const Point &p)const{return y!=p.y?y<p.y:x<p.x;}
};
int N,PIDS[500001];
void BuildPIDS(const vector<Point>&p)
{
	int pid=-1;
	for(int y=0;y<=N;y++)
	{
		for(;pid+1<=N&&p[pid+1].y<=y;pid++);
		PIDS[y]=pid;
	}
}
Node *TREE[500001];
void BuildPlane(const vector<Point>&p)
{
	vector<int>order;
	for(int i=1;i<=N;i++)order.push_back(i);
	sort(order.begin(),order.end(),[&](const int a,const int b)->bool{return p[a].x!=p[b].x?p[a].x<p[b].x:a<b;});
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
	BuildPIDS(p);
	BuildPlane(p);
}
bool Solve(const vector<int>&ks)
{
	stack<Point>stk;
	stk.push(Point(0,N));
	for(const int k:ks)
	{
//		printf("k=%d\n",k);
		while(!stk.empty()&&stk.top().y<=PIDS[k-1])stk.pop();
		int remain=k;
		for(int lowy=PIDS[k-1];;)
		{
			if(stk.empty())return false;
//			printf("(%d,k=%d)\n",stk.top().x,k);
			Node *lt=TREE[stk.top().x],*rt=TREE[k];
			const int basis=QuerySum(lt,rt,0,N,lowy);
			const int supply=QuerySum(lt,rt,0,N,stk.top().y);
//			printf("basis=%d,supply=%d(%d)\n",basis,supply,stk.top().y);
			if(remain+basis>supply)
			{
				remain-=supply-basis;
				lowy=stk.top().y;
				stk.pop();
			}
			else
			{
				stk.push(Point(k,QueryLoc(lt,rt,0,N,remain+basis)));
				break;
			}
		}
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		NEW=Node_BUFFER;
		scanf("%d",&N);
		InitialPoints();
		int querycount;scanf("%d",&querycount);
		for(int m;querycount--;)
		{
			scanf("%d",&m);
			vector<int>ks;
			for(int v;m--;)scanf("%d",&v),ks.push_back(v);
			sort(ks.begin(),ks.end());
			puts(Solve(ks)?"1":"0");
		}
	}
	return 0;
}
