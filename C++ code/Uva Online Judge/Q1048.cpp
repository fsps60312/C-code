#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int NT,NI;
struct Ticket
{
	int idx,cost;
	vector<int> to;
};
vector<Ticket> TICKET[21];
vector<vector<int> > TRIP;
struct Trip
{
	int pos,next,cost,num;//,pre,ticket;
	bool operator<(Trip a)const{return cost>a.cost||(cost==a.cost&&num>a.num);}
};
int BEST[21][21]; 
Trip solve(vector<int> &sche)
{
	//printf("sche:");for(int i=0;i<sche.size();i++)printf(" %d",sche[i]);printf("\n");
	for(int i=1;i<=20;i++)
	{
		for(int t=1;t<=20;t++)
		{
			BEST[i][t]=2147483647;
		}
	}
	priority_queue<Trip> pq;
	pq.push((Trip){sche[0],0,0,0});
	Trip ans=(Trip){-1,-1,2147483647,2147483647};
	while(!pq.empty())
	{
		Trip t=pq.top();pq.pop();
		while(t.next<sche.size()&&t.pos==sche[t.next])t.next++;
		if(t.cost>BEST[t.pos][t.num])continue;
		BEST[t.pos][t.num]=t.cost;
		//printf("%d %d %d %d\n",t.cost,t.num,t.pos,t.next);
		if(t.next==sche.size())
		{
			if(!(t<ans))ans=t;
			continue;
		}
		for(int i=0;i<TICKET[t.pos].size();i++)//each ticket from t.pos
		{
			Ticket &tkt=TICKET[t.pos][i];
			int next=t.next;
			for(int u=0;u<tkt.to.size();u++)//each position this ticket will go
			{
				while(next<sche.size()&&tkt.to[u]==sche[next])
				{
					next++;//find next unvisited position
					//printf("pos:%d next:%d\n",tkt.to[u],t.next);
				}
				pq.push((Trip){tkt.to[u],next,t.cost+tkt.cost,t.num+1});
				if(next==sche.size())break;
			}
		}
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=0;
	while(scanf("%d",&NT)==1&&NT)
	{
		kase++;
		for(int i=1;i<=20;i++)TICKET[i].clear();
		for(int i=1;i<=NT;i++)
		{
			Ticket t;
			t.idx=i;
			int a,b,from;scanf("%d%d%d",&t.cost,&a,&from);
			while(--a)
			{
				scanf("%d",&b);
				t.to.push_back(b);
			}
			TICKET[from].push_back(t);
		}
		TRIP.clear();
		scanf("%d",&NI);
		for(int i=0;i<NI;i++)
		{
			int a,b;scanf("%d",&a);
			vector<int> v;
			while(a--)
			{
				scanf("%d",&b);
				v.push_back(b);
			}
			TRIP.push_back(v);
		}
		for(int t=0;t<TRIP.size();t++)
		{
			Trip ans=solve(TRIP[t]);
			printf("Case %d, Trip %d: Cost = %d\n  Tickets used: %d",kase,t+1,ans.cost,ans.num);
			//for(int i=0;i<ans.ticket.size();i++)printf(" %d",ans.ticket[i]);
			printf("\n");
		}
	}
	return 0;
}
