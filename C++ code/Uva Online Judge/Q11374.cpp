#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int N,S,E,DONE[501][2],PRE[501][2];
vector<int> STAE[501],STAB[501];
struct Route{int from,to,time;};
vector<Route> ECO,BUS;
struct Trip
{
	int station,time,used,pre;
	bool operator<(Trip a)const{return time>a.time;}
};
priority_queue<Trip> PQ;
int dfsprint(int sta)
{
	//printf("sta=%d\n",sta);system("pause");
	if(sta%1000==S)
	{
		printf("%d",S);
		return 0;
	}
	int next=PRE[sta%1000][sta/1000];
	//printf("next=%d\n",next);
	int ans=dfsprint(next);
	printf(" %d",sta%1000);
	if(sta/1000&&!(next/1000))return next;
	else return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=0;
	while(scanf("%d%d%d",&N,&S,&E)==3)
	{
		if(kase++)printf("\n");
		for(int i=1;i<=N;i++)
		{
			STAE[i].clear(),STAB[i].clear();
			DONE[i][0]=DONE[i][1]=false;
		}
		ECO.clear(),BUS.clear();
		int m;scanf("%d",&m);
		while(m--)
		{
			int from,to,time;scanf("%d%d%d",&from,&to,&time);
			STAE[from].push_back(ECO.size());
			ECO.push_back((Route){from,to,time});
			STAE[to].push_back(ECO.size());
			ECO.push_back((Route){to,from,time});
		}
		scanf("%d",&m);
		while(m--)
		{
			int from,to,time;scanf("%d%d%d",&from,&to,&time);
			STAB[from].push_back(BUS.size());
			BUS.push_back((Route){from,to,time});
			STAB[to].push_back(BUS.size());
			BUS.push_back((Route){to,from,time});
		}
		while(!PQ.empty())PQ.pop();
		PQ.push((Trip){S,0,0,0});
		while(!PQ.empty())
		{
			Trip trip=PQ.top();PQ.pop();
			int sta=trip.station,tim=trip.time,used=trip.used,pre=trip.pre;
			//printf("sta=%d\ttim=%d\tused=%d\tpre=%d\n",sta,tim,used,pre);
			if(DONE[sta][used])continue;
			DONE[sta][used]=true;
			PRE[sta][used]=pre;
			if(sta==E)
			{
				//printf("dfs:%d\n",sta+1000*used);
				int express=dfsprint(sta+1000*used);printf("\n");
				if(express)printf("%d\n",express);
				else printf("Ticket Not Used\n");
				printf("%d\n",tim);
				break;
			}
			for(int i=0;i<STAE[sta].size();i++)
			{
				Route r=ECO[STAE[sta][i]];
				PQ.push((Trip){r.to,tim+r.time,used,sta+1000*used});
			}
			if(used)continue;
			for(int i=0;i<STAB[sta].size();i++)
			{
				Route r=BUS[STAB[sta][i]];
				PQ.push((Trip){r.to,tim+r.time,1,sta});
			}
		}
	}
	return 0;
}
