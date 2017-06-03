#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
using namespace std;
int NT,NI;
struct Ticket
{
	int cost;
	vector<int> to;
};
map<int,int> NtoIDX;
vector<Ticket> TICKET;
vector<vector<int> > TRIP;
int getidx(int n)
{
	if(NtoIDX.find(n)!=NtoIDX.end())return NtoIDX[n];
	int sz=NtoIDX.size();
	NtoIDX[n]=sz;
	return sz;
}
int CS[200][10],NUM[200][10];
int INQ[200];
struct Point
{
	int x,y,z;
	bool operator<(Point a)
	{
		if(x!=a.x)return x<a.x;
		if(y!=a.y)return y<a.y;
		return z<a.z;
	}
};
Point PRE[200][10];
struct Trip{int pos,done;};
struct Ans
{
	int pos,done;
	Point ans;
	bool operator<(Ans a)
	{
		if(pos!=a.pos)return pos<a.pos;
		if(done!=a.done)return done<a.done;
		return ans.z<a.ans.z;
	}
};
void getmin(Ans &a,Ans b){if(b<a)a=b;}
Ans solve(vector<int> &SCH)
{
	for(int c=0;c<NtoIDX.size();c++)
	{
		INQ[c]=0;
		for(int i=0;i<SCH.size();i++)
		{
			CS[c][i]=NUM[c][i]=2147483647;
			PRE[c][i]=(Point){-1,-1,-1};
		}
	}
	CS[SCH[0]][0]=NUM[SCH[0]][0]=0;
	queue<Trip> q;
	q.push((Trip){SCH[0],0});
	INQ[SCH[0]]+=(1<<0);
	Ans ans=(Ans){2147483647,2147483647,(Point){-1,-1,-1}};//cost,num
	while(!q.empty())
	{
		Trip t=q.front();q.pop();
		//printf("At %d, done %d, spend(%d,%d)\n",t.pos,t.done,CS[t.pos][t.done],NUM[t.pos][t.done]);
		INQ[t.pos]-=(1<<t.done);
		int &cs=CS[t.pos][t.done];
		for(int i=0;i<TICKET.size();i++)
		{
			Ticket &tkt=TICKET[i];
			if(t.pos!=tkt.to[0])continue;
			int done=t.done;
			for(int u=0;u<tkt.to.size();u++)
			{
				if(tkt.to[u]==SCH[done])done++;
				if(done==SCH.size())
				{
					Ans tans=(Ans){cs+tkt.cost,NUM[t.pos][t.done]+1,(Point){t.pos,t.done,i}};
					getmin(ans,tans);
					//printf("(%d,%d)\n",tans.pos,tans.done);
					break;
				}
				int &tcs=CS[tkt.to[u]][done];
				if(((Point){cs+tkt.cost,NUM[t.pos][t.done]+1,i})<((Point){tcs,NUM[tkt.to[u]][done],PRE[tkt.to[u]][done].z}))
				{
					tcs=cs+tkt.cost;
					NUM[tkt.to[u]][done]=NUM[t.pos][t.done]+1;
					PRE[tkt.to[u]][done]=(Point){t.pos,t.done,i};
				}
				else continue;
				if(INQ[tkt.to[u]]&(1<<done))continue;
				//printf("push(%d,%d)\n",tkt.to[u],done);
				q.push((Trip){tkt.to[u],done});
				INQ[tkt.to[u]]+=(1<<done);
			}
		}
	}
	return ans;
}
void dfsprint(Point p)
{
	if(p.z==-1)return;
	Point _p=PRE[p.x][p.y];
	dfsprint(_p);
	if(_p.z!=p.z)printf(" %d",p.z+1);
}
int main()
{
	freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
	int kase=0;
	while(scanf("%d",&NT)==1&&NT)
	{
		kase++;
		TICKET.clear();
		NtoIDX.clear();
		for(int i=0;i<NT;i++)
		{
			Ticket t;
			int a,b;scanf("%d%d",&t.cost,&a);
			while(a--)
			{
				scanf("%d",&b);
				t.to.push_back(getidx(b));
			}
			TICKET.push_back(t);
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
				v.push_back(getidx(b));
			}
			TRIP.push_back(v);
		}
		for(int t=0;t<TRIP.size();t++)
		{
			Ans ans=solve(TRIP[t]);
			printf("Case %d, Trip %d: Cost = %d\n  Tickets used:",kase,t+1,ans.pos);
			//for(int i=0;i<ans.ticket.size();i++)printf(" %d",ans.ticket[i]);
			dfsprint(ans.ans);
			printf("\n");
		}
	}
	return 0;
}
