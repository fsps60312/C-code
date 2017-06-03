#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<cassert>
using namespace std;
//void assert(bool valid){if(valid)return;for(;;)printf("E");}
const int INF=2147483647;
int NT,NI;
map<int,int>IDX,RI;
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
		RI[sz]=i;
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
//	for(int i=0;i<trip.size();i++)printf(" %d",RI[trip[i]]);puts("");
	pq.push(Pq(trip[0],0,0,-1,-1,-1));
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		if(p.u==trip[p.i])p.i++;
		if(p.cost<MIN[p.i-1][p.u])MIN[p.i-1][p.u]=p.cost,UPRE[p.i-1][p.u]=p.upre,IPRE[p.i-1][p.u]=p.ipre,TICK[p.i-1][p.u]=p.t;
		else if(p.cost>=MIN[p.i-1][p.u])continue;
//		printf("u=%d,i=%d,cost=%d,upre=%d,ipre=%d,t=%d\n",RI[p.u],p.i,p.cost,RI[p.upre],p.ipre,p.t);
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
	assert(0);
}
vector<int>ANS;
void PrintAns(int i,int u)
{
//	printf("i=%d u=%d t=%d\n",i,RI[u],TICK[i][u]);
	if(TICK[i][u]==-1)return;
	PrintAns(IPRE[i][u]-1,UPRE[i][u]);
	ANS.push_back(TICK[i][u]+1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&NT)==1&&NT)
	{
		IDX.clear();
		RI.clear();
		AD.clear();
vector<Ticket>ticket;
		for(int i=0;i<NT;i++)
		{
			static Ticket t;
			t.idx=i;
			static int n,v;
			scanf("%d%d",&t.cost,&n);
			assert(t.cost>0);
			t.city.clear();
			while(n--)
			{
				scanf("%d",&v);
				t.city.push_back(GetIdx(v));
			}
			AD[t.city[0]].push_back(t);
ticket.push_back(t);
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
			assert(ans.i==trip.size());
			ANS.clear();
			PrintAns(ans.i-1,ans.u);
			for(int i=0;i<ANS.size();i++)printf(" %d",ANS[i]);puts("");
//int now=0;
//for(int i=0;i<ANS.size();i++)
//{
//	vector<int>&city=ticket[ANS[i]-1].city;
//	for(int j=0;j<city.size()&&(i==ANS.size()-1||city[j]!=ticket[ANS[i+1]-1].city[0]);j++)
//	{
//		int &u=city[j];
////		printf("u=%d\n",RI[u]);
//		if(now<trip.size()&&u==trip[now])now++;
//		if(now==trip.size())break;
//	}
//}
//assert(now==trip.size());
		}
	}
	return 0;
}
