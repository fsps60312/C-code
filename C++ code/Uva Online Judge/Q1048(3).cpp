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
int IDXtoFROM[21],IDXtoTKTI[21];
vector<vector<int> > TRIP;
struct Trip
{
	int pos,next,cost,num,lastpos,ticketn,ticketi;
	bool operator<(Trip a)const
	{
		if(cost!=a.cost)return cost>a.cost;
		if(num!=a.num)return num>a.num;
		return ticketn>a.ticketn;
	}
	bool operator<=(Trip a)const
	{
		if(cost!=a.cost)return cost>a.cost;
		if(num!=a.num)return num>a.num;
		return ticketn>=a.ticketn;
	}
};
int LASTPOS[21][401],TICKETN[21][401],TICKETI[21][401],BEST[21][401];
Trip solve(vector<int> &sche)
{
	//printf("sche:");for(int i=0;i<sche.size();i++)printf(" %d",sche[i]);printf("\n");
	for(int i=1;i<=20;i++)
	{
		for(int t=1;t<=400;t++)
		{
			LASTPOS[i][t]=TICKETN[i][t]=TICKETI[i][t]=-1;
			BEST[i][t]=2147483647;
		}
	}
	priority_queue<Trip> pq;
	pq.push((Trip){sche[0],0,0,0,-1,-1,-1});
	Trip ans=(Trip){-1,-1,2147483647,2147483647,-1,-1,-1};
	while(!pq.empty())
	{
		Trip t=pq.top();pq.pop();
		while(t.next<sche.size()&&t.pos==sche[t.next])t.next++;
		if(t.cost>=BEST[t.pos][t.num])continue;
		BEST[t.pos][t.num]=t.cost;
		LASTPOS[t.pos][t.num]=t.lastpos;
		TICKETN[t.pos][t.num]=t.ticketn;
		TICKETI[t.pos][t.num]=t.ticketi;
		if(t.next==sche.size())
		{
			if(ans<t)ans=t;
			continue;
		}
		//printf("source:(%d,%d)->(%d,%d)\n",t.pos,t.num,t.lastpos,t.ticketn);
		//printf("%d %d %d %d\n",t.cost,t.num,t.pos,t.next);
		for(int i=0;i<TICKET[t.pos].size();i++)//each ticket from t.pos
		{
			Ticket &tkt=TICKET[t.pos][i];
			int nxt=t.next;
			for(int u=0;u<tkt.to.size();u++)//each position this ticket will go
			{
				while(nxt<sche.size()&&tkt.to[u]==sche[nxt])
				{
					nxt++;//find next unvisited position
					//printf("pos:%d next:%d\n",tkt.to[u],t.next);
				}
				pq.push((Trip){tkt.to[u],nxt,t.cost+tkt.cost,t.num+1,t.pos,tkt.idx,u});
				if(nxt==sche.size())break;
			}
		}
	}
	return ans;
}
void dfsprint(int pos,int num,int idx,vector<int> &sche)
{
	//printf("in(pos=%d num=%d idx=%d)\n",pos,num,idx);
	if(num==0)return;
	int &tktidx=TICKETN[pos][num];
	//printf("\tUsing Ticket %d\n",tktidx);
	Ticket &t=TICKET[IDXtoFROM[tktidx]][IDXtoTKTI[tktidx]];
	for(int u=TICKETI[pos][num];u>=0;u--)
	{
		while(t.to[u]==sche[idx])idx--;
	}
	while(IDXtoFROM[tktidx]==sche[idx])idx--;
	dfsprint(LASTPOS[pos][num],num-1,idx,sche);
	printf(" %d",t.idx);
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
			IDXtoFROM[i]=from;
			IDXtoTKTI[i]=TICKET[from].size();
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
			printf("Case %d, Trip %d: Cost = %d\n  Tickets used:",kase,t+1,ans.cost);
			dfsprint(TRIP[t][TRIP[t].size()-1],ans.num,TRIP[t].size()-1,TRIP[t]);
			//for(int i=0;i<ans.ticket.size();i++)printf(" %d",ans.ticket[i]);
			printf("\n");
		}
	}
	return 0;
}
