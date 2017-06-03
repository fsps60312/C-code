#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
const int INF=2147483647;
struct Node
{
	Node *ch[2];
	int sum;
	Node(const int _sum):ch{NULL,NULL},sum(_sum){}
};
Node *Build(const int l,const int r)
{
	Node *ans=new Node(0);
	if(l<r)
	{
		const int mid=(l+r)/2;
		ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	}
	return ans;
}
Node *Add(Node *o,const int l,const int r,const int loc)
{
	Node *ans=new Node(o->sum+1);
	if(l<r)
	{
		const int mid=(l+r)/2;
		if(loc<=mid)ans->ch[0]=Add(o->ch[0],l,mid,loc),ans->ch[1]=o->ch[1];
		else ans->ch[0]=o->ch[0],ans->ch[1]=Add(o->ch[1],mid+1,r,loc);
	}
	return ans;
}
int QueryLoc(Node* lo,Node *ro,const int l,const int r,const int sum)
{
	assert(ro->sum-lo->sum>=sum);
	if(l==r){assert(ro->sum-lo->sum==sum&&sum==1);return r;}
	const int mid=(l+r)/2;
	const int lsum=ro->ch[0]->sum-lo->ch[0]->sum;
	if(lsum>=sum)return QueryLoc(lo->ch[0],ro->ch[0],l,mid,sum);
	else return QueryLoc(lo->ch[1],ro->ch[1],mid+1,r,sum-lsum);
}
int QuerySum(Node* lo,Node *ro,const int l,const int r,const int loc)
{
	if(l==r){assert(r==loc);return ro->sum-lo->sum;}
	const int mid=(l+r)/2;
	if(loc<=mid)return QuerySum(lo->ch[0],ro->ch[0],l,mid,loc);
	else return (ro->ch[0]->sum-lo->ch[0]->sum)+QuerySum(lo->ch[1],ro->ch[1],mid+1,r,loc);
}
struct Point{int x,y;};
vector<int>XS;
vector<Point>PS;
Node *ROOT[500001];
int Y_UPBOUND[500001],X_UPBOUND[500001];
int N;
void BuildPlane()
{
	PS.clear();
	for(int i=0;i<N;i++)
	{
		static Point p;
		scanf("%d%d",&p.x,&p.y);
		PS.push_back(p);
	}
	sort(PS.begin(),PS.end(),[](const Point &a,const Point &b)->bool{return a.y!=b.y?a.y<b.y:a.x<b.x;});
	PS.insert(PS.begin(),Point());
	Y_UPBOUND[0]=0;
	for(int i=1,ans=0;i<=N;i++)
	{
		while(ans+1<N&&PS[ans+1].y==i)ans++;
		Y_UPBOUND[i]=ans;
	}
	vector<int>order;
	for(int i=1;i<=N;i++)order.push_back(i);
	sort(order.begin(),order.end(),[](const int a,const int b)->bool
	{
		if(PS[a].x!=PS[b].x)return PS[a].x<PS[b].x;
		return a<b;
	});
	ROOT[0]=Build(0,N);
	int n=X_UPBOUND[0]=0;
	int j=1;
	for(int i=0;i<N;)
	{
		n++;
		const int x=PS[order[i]].x;
		ROOT[n]=ROOT[n-1];
		for(;i<N&&PS[order[i]].x==x;i++)ROOT[n]=Add(ROOT[n],0,N,order[i]);
		for(;j<x;j++)X_UPBOUND[j]=X_UPBOUND[j-1];
		X_UPBOUND[j++]=n;
	}
	for(;j<=N;j++)X_UPBOUND[j]=X_UPBOUND[j-1];
}
#include<stack>
bool Solve(const vector<pair<int,int> >&ks)//x,count
{
	stack<pair<int,int> >stk;
	stk.push(make_pair(0,INF));//x,y
	for(int i=1;i<(int)ks.size();i++)
	{
//		printf("ks[%d]=(%d,%d)\n",i,ks[i].first,ks[i].second);
		int y_lowbound=Y_UPBOUND[ks[i].first-1];
		int remain=ks[i].first*ks[i].second;
		while(!stk.empty())
		{
			Node *ltree=ROOT[X_UPBOUND[stk.top().first]],*rtree=ROOT[X_UPBOUND[ks[i].first]];
			const int sum=remain+QuerySum(ltree,rtree,0,N,y_lowbound);
			const int y_upbound=(rtree->sum-ltree->sum<sum?INF:QueryLoc(ltree,rtree,0,N,sum));
//			printf("ybound=(%d,%d),xbound=(%d,%d)\n",y_lowbound,y_upbound,X_UPBOUND[stk.top().first],X_UPBOUND[ks[i].first]);
//			printf("basesum=%d,allsum=%d\n",sum,QuerySum(ltree,rtree,0,N,N));
			if(y_upbound>=stk.top().second)
			{
				if((int)stk.size()>1)
				{
					remain-=QuerySum(ltree,rtree,0,N,stk.top().second)-QuerySum(ltree,rtree,0,N,y_lowbound);
					y_lowbound=stk.top().second;
				}
				stk.pop();
			}
			else
			{
				stk.push(make_pair(ks[i].first,y_upbound));
				break;
			}
		}
		if(stk.empty())return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	BuildPlane();
	int querycount;scanf("%d",&querycount);
	for(int m;querycount--;)
	{
		scanf("%d",&m);
		map<int,int>tks;
		for(int i=0,v;i<m;i++)scanf("%d",&v),tks[v]++;
		vector<pair<int,int> >ks;//x,count
		ks.push_back(make_pair(0,0));
		for(const auto &p:tks)ks.push_back(p);
		puts(Solve(ks)?"1":"0");
	}
	return 0;
}
