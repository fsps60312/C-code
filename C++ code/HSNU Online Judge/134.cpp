#include<cstdio>
#include<cassert>
#include<map>
#include<queue>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
int R,C,K,SZ;
map<int,int>IDX[100000];
vector<pair<int,int> >RIDX;
map<int,int>ROWS;
vector<vector<int> >EF;
vector<int>DIST;
int GetIdx(const int c,const int r)
{
	const auto it=IDX[c].find(r);
	if(it==IDX[c].end())
	{
		EF.push_back(vector<int>());
		RIDX.push_back(make_pair(r,c));
		DIST.push_back(INF);
		return IDX[c][r]=SZ++;
	}
	else return it->second;
}
void AddEdge(const int from,const int to){EF[to].push_back(from);}
struct Pq
{
	int r,c,cost;
	Pq(){}
	Pq(const int _r,const int _c,const int _cost):r(_r),c(_c),cost(_cost){}
	bool operator<(const Pq &p)const
	{
		if(cost!=p.cost)return cost>p.cost;
		if(r!=p.r)return r<p.r;
		return c<p.c;
	}
};
int UpperCost(const int r,const int c)
{
	auto it=IDX[c].lower_bound(r);
	if(it==IDX[c].end())return INF;
	else return DIST[it->second];
}
int LEFT_COST[100000],RIGHT_COST[100000];
int Solve()
{
	priority_queue<Pq>pq;
	for(int type=0;type<=1;type++)
	{
		for(int &v:DIST)v=INF;
		const Pq source=Pq(R,type==0?0:C-1,0);
		pq.push(source);
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(UpperCost(p.r,p.c)<=p.cost)continue;
			const int nowu=GetIdx(p.c,p.r);
			DIST[nowu]=p.cost;
//			printf("(%d,%d) is %d\n",p.r,p.c,p.cost);
			for(int i=0;i<(int)EF[nowu].size();i++)
			{
				const int nxtu=EF[nowu][i];
				pq.push(Pq(RIDX[nxtu].first,RIDX[nxtu].second,p.cost));
			}
			if(type==0&&p.c+1<C)pq.push(Pq(p.r,p.c+1,p.cost+1));
			if(type==1&&p.c-1>=0)pq.push(Pq(p.r,p.c-1,p.cost+1));
		}
//		error
//		for(int i=0;i<C;i++)
//		{
//			static vector<int>seq;seq.clear();
//			for(const auto &it:IDX[i])seq.push_back(it.second);
//			for(int j=(int)seq.size()-1;j>=1;j--)getmin(DIST[seq[j-1]],DIST[seq[j]]);
//		}
		for(int i=0;i<C;i++)(type==0?RIGHT_COST:LEFT_COST)[i]=DIST[GetIdx(i,0)];
	}
//	printf("L:");for(int i=0;i<C;i++)printf(" %d",LEFT_COST[i]);puts("");
//	printf("R:");for(int i=0;i<C;i++)printf(" %d",RIGHT_COST[i]);puts("");
	int r=0,l=C-1;
	while(r<C&&RIGHT_COST[r]==0)r++;
	while(l>=0&&LEFT_COST[l]==0)l--;
//	printf("(%d,%d)\n",l,r);
	if(l<r)return r-l-1;
	else return 0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int n;
	scanf(4,"%d%d%d%d",&C,&R,&n,&K);
	for(int i=0;i<C;i++)IDX[i].clear();
	SZ=0,EF.clear(),RIDX.clear(),ROWS.clear(),DIST.clear();
	for(int i=0;i<C;i++)GetIdx(i,0),GetIdx(i,R);
	for(int i=0,c,r,d;i<n;i++)
	{
		scanf(3,"%d%d%d",&c,&r,&d);
		c--;
		ROWS[r]=-1;
		const int a=GetIdx(c,r),b=GetIdx(c+1,r);
		if(d==0)AddEdge(a,b);
		else if(d==1)AddEdge(b,a);
		else assert(0);
	}
	if(1)
	{
		int pre_sz=SZ;
		for(int i=0;i<C;i++)
		{
			static vector<int>seq;seq.clear();
			for(const auto &it:IDX[i])seq.push_back(it.first);
			for(int j=1;j<(int)seq.size();j++)
			{
//				printf("Add(%d,%d)(%d,%d)\n",seq[j],i,seq[j-1],i);
				AddEdge(GetIdx(i,seq[j-1]),GetIdx(i,seq[j]));
			}
		}
//		printf("(%d,%d)\n",pre_sz,SZ);
		assert(SZ==pre_sz);
	}
	const int pre=Solve();
	int ans=0;
	for(int l=0,r=-1;l<C;l++)
	{
		while(r+1<C&&LEFT_COST[l]+RIGHT_COST[r+1]<=K)r++;
//		printf("(%d,%d)=(%d,%d)\n",l,r,LEFT_COST[l],RIGHT_COST[r]);
		getmax(ans,r-l+1);
	}
	printf("%d\n",ans-pre);
	return 0;
}
