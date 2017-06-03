#include<cstdio>
#include<vector>
#include<map>
#include<queue>
using namespace std;
const int INF=2147483647;
int NT,NI;
map<int,int>IDX;
int MIN[20][400],UPRE[20][400],IPRE[20][400],TICK[20][400];
struct Ticket
{
	int cost,idx;
	vector<int>city;
	Ticket(){}
};
vector<vector<Ticket> >AD;
int GetIdx(int i)
{
	if(IDX.find(i)==IDX.end())
	{
		static int sz;
		sz=IDX.size();
		AD.push_back(vector<Ticket>());
		return IDX[i]=sz++;
	}
	return IDX[i];
}
struct Pq
{
	int u,i,cost,upre,ipre,t;
	Pq(){}
	Pq(int u,int i,int cost,int upre,int ipre,int t):u(u),i(i),cost(cost),upre(upre),ipre(ipre),t(t){}
	bool operator<(const Pq &p)const{return cost!=p.cost?cost>p.cost:i>p.i;}
};
Pq solve(vector<int>&trip)
{
	priority_queue<Pq>pq;
	pq.push(Pq(trip[0],0,0,-1,-1,-1));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(p.u==trip[p.i])p.i++;
		if(p.cost<MIN[p.i-1][p.u])MIN[p.i-1][p.u]=p.cost,UPRE[p.i-1][p.u]=p.upre,IPRE[p.i-1][p.u]=p.ipre,TICK[p.i-1][p.u]=p.t;
		else if(p.cost>=MIN[p.i-1][p.u])continue;
		if(p.i==trip.size())return p;
		for(int i=0;i<AD[p.u].size();i++)
		{
			Ticket &t=AD[p.u][i];
			Pq pt=p;
			pt.cost+=t.cost;
			pt.upre=p.u;
			pt.ipre=p.i;
			pt.t=t.idx;
			for(int i=1;i<t.city.size()&&pt.i<trip.size();i++)
			{
				int &c=t.city[i];
				pt.u=c;
				pq.push(pt);
				if(pt.u==trip[pt.i])pt.i++;
				if(pt.i==trip.size())break;
			}
		}
	}
}
void PrintAns(int i,int u)
{
	if(TICK[i][u]==-1)return;
	PrintAns(IPRE[i][u]-1,UPRE[i][u]);
	printf(" %d",TICK[i][u]+1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&NT)==1&&NT)
	{
		IDX.clear();
		AD.clear();
		for(int i=0;i<NT;i++)
		{
			static Ticket t;
			t.idx=i;
			static int n,v;
			scanf("%d%d",&t.cost,&n);
			t.city.clear();
			while(n--)
			{
				scanf("%d",&v);
				t.city.push_back(GetIdx(v));
			}
			AD[t.city[0]].push_back(t);
		}
		scanf("%d",&NI);
		static int kase=0;
		kase++;
		int trip_cnt=1;
		while(NI--)
		{
			vector<int>trip;
			static int n,v;
			scanf("%d",&n);
			while(n--)
			{
				scanf("%d",&v);
				trip.push_back(GetIdx(v));
			}
			for(int i=0;i<trip.size();i++)for(int j=0;j<IDX.size();j++)MIN[i][j]=INF;
			Pq ans=solve(trip);
			printf("Case %d, Trip %d: Cost = %d\n  Tickets used:",kase,trip_cnt++,ans.cost);
			PrintAns(ans.i-1,ans.u);puts("");
		}
	}
	return 0;
}
