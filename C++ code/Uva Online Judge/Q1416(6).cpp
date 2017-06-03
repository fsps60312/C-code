#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#define LL long long
using namespace std;
vector<LL> CITY[101];
struct Road{LL to,l;};
vector<Road> ROAD;
LL N,M,L;
struct Trip
{
	LL x,y,j;
	bool operator<(Trip a)const{return x>a.x;}
};
LL VIS[101];
struct Tree
{
	LL _ans,CNTAN[2000];
	void init()
	{
		for(LL i=0;i<ROAD.size();i++)CNTAN[i]=0;
		for(LL i=1;i<=N;i++)VIS[i]=0;
	}
	LL build(LL sp,LL ban)
	{
		_ans=0;
		init();
		priority_queue<Trip> pq;
		pq.push((Trip){0,sp,-1});
		while(!pq.empty())
		{
			Trip t=pq.top();pq.pop();
			if(t.x>L)break;
			if(VIS[t.y]||t.j==ban||t.j==ban+1)continue; 
			VIS[t.y]=1;
			if(t.j!=-1)CNTAN[t.j]=1;
			//printf("%lld %lld\n",t.x,t.y);
			_ans+=t.x;
			for(LL i=0;i<CITY[t.y].size();i++)
			{
				LL j=CITY[t.y][i];
				pq.push((Trip){t.x+ROAD[j].l,ROAD[j].to,j});
			}
		}
		for(LL i=1;i<=N;i++)if(!VIS[i])_ans+=L;
		return _ans;
	}
}TREE[101];
LL cal(LL ban)
{
	LL ans=0;
	for(LL i=1;i<=N;i++)
	{
		if(TREE[i].CNTAN[ban]||TREE[i].CNTAN[ban+1])ans+=TREE[0].build(i,ban);
		else ans+=TREE[i]._ans;
	}
	return ans;
}
void addside(LL a,LL b,LL l)
{
	LL sz=ROAD.size();
	ROAD.push_back((Road){b,l});
	CITY[a].push_back(sz++);
	ROAD.push_back((Road){a,l});
	CITY[b].push_back(sz);
}
void init()
{
	ROAD.clear();
	for(LL i=1;i<=N;i++)
	{
		CITY[i].clear();
	}
}
void getmax(LL &a,LL b){if(b>a)a=b;}
int main()
{
	while(scanf("%lld%lld%lld",&N,&M,&L)==3)
	{
		init();
		for(LL i=0;i<M;i++)
		{
			LL a,b,l;scanf("%lld%lld%lld",&a,&b,&l);
			addside(a,b,l);
		}
		LL ori=0;
		for(LL i=1;i<=N;i++)
		{
			LL t=TREE[i].build(i,-3);
			//printf("TREE[%lld].build=%lld\n",i,t);
			ori+=t;
		}
		//printf("a\n");
		LL ans=ori;
		for(LL i=0;i<ROAD.size();i+=2)
		{
			getmax(ans,cal(i));
		}
		printf("%lld %lld\n",ori,ans);
	}
	return 0;
}
