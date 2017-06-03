#include<cstdio>
#include<vector>
#include<queue>
#include<map>
#include<cassert>
using namespace std;
int NT,NI;
struct Ticket
{
	vector<int>city;
	int cost,idx;
	void scan()
	{
		city.clear();
		static int n,v;
		scanf("%d%d",&cost,&n);
		while(n--)
		{
			scanf("%d",&v);
			city.push_back(v);
		}
	}
	int Sz(){return city.size();}
};
struct Pq
{
	int i,u,s,cnt,cost;
	Pq(){}
	Pq(int i,int u,int s,int cost):i(i),u(u),s(s),cost(cost),cnt(cntbits(s)){}
	int cntbits(int a)
	{
		a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
		a=((a&0xcccccccc)>>2)+(a&0x33333333);
		a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
		a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
		return a;
	}
	bool operator<(const Pq &p)const{return cost!=p.cost?cost>p.cost:cnt>p.cnt;}
};
map<int,vector<Ticket> >TICKET;
Pq solve(vector<int>&trip)
{
	priority_queue<Pq>pq;
	pq.push(Pq(0,trip[0],0,0));
//	for(int i=0;i<trip.size();i++)printf(" %d",trip[i]);puts("");
	while(!pq.empty())
	{
		Pq u=pq.top();pq.pop();
//		printf("i=%d cost=%d ticket=%d\n",u.i,u.cost,u.s);
		if(u.i==trip.size())return u;
		vector<Ticket>&ticket=TICKET[u.u];
		for(int i=0;i<ticket.size();i++)
		{
			Ticket &t=ticket[i];
			if(u.s&(1<<t.idx))continue;
			for(int j=1,k=u.i+1;j<t.Sz();j++)
			{
				int &c=t.city[j];
				while(k<trip.size()&&c==trip[k])k++;
				pq.push(Pq(k,c,u.s|(1<<t.idx),u.cost+t.cost));
			}
		}
	}
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&NT)==1&&NT)
	{
		TICKET.clear();
		for(int i=0;i<NT;i++)
		{
			static Ticket ticket;
			ticket.idx=i;
			ticket.scan();
			TICKET[ticket.city[0]].push_back(ticket);
		}
		scanf("%d",&NI);
		static int kase=0;
		kase++;
		static int trip_cnt;trip_cnt=1;
		while(NI--)
		{
			vector<int> trip;
			static int n,v;
			scanf("%d",&n);
			while(n--)
			{
				scanf("%d",&v);
				trip.push_back(v);
			}
			Pq ans=solve(trip);
//			printf("%d %d ",ans.s,ans.i);
			printf("Case %d, Trip %d: Cost = %d\n  Tickets used: %d\n",kase,trip_cnt++,ans.cost,ans.cnt);
		}
	}
	return 0;
}
