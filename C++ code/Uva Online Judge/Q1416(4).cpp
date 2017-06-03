#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#define LL long long
using namespace std;
LL N,L,BAN[201][201];
struct Pair{int x,y;};
Pair RD[201][201];
vector<Pair> ROAD;
struct Trip{LL x,y;bool operator<(Trip a)const{return x>a.x;}};
struct Tree
{
	LL _vis[201],_edge[8000],_ans;
	void clear()
	{
		_ans=0;
		for(LL i=1;i<=N;i++)_vis[i]=0;
		for(LL i=0;i<RD.size();i++)_edge[i]=0;
	}
	bool needupdate()
	{
		for(LL i=0;i<ROAD.size();i++)if((ROAD[i].z&&!_edge[i])||(!ROAD[i].z&&_edge[i]))return true;
		return false;
	}
	LL buildtree(LL u)
	{
		clear();
		priority_queue<Trip> pq;
		pq.push((Trip){0,u});
		while(!pq.empty())
		{
			Trip t=pq.top();pq.pop();
			if(_vis[t.y])continue;
			_vis[t.y]=1;
			_ans+=t.x;
			for(LL i=1;i<=N;i++)
			{
				if(!BAN[t.y][i])pq.push((Trip){t.x+RD[t.y][i].x,i});
				pq.push((Trip){t.x+RD[t.y][i].y,i});
			}
		}
		return _ans;
	}
};
Tree TREE[201];
void getmax(LL &a,LL b){if(b>a)a=b;}
LL cal()
{
	LL ans=0;
	for(LL i=1;i<=N;i++)
	{
		if(TREE[i].needupdate())ans+=TREE[0].buildtree(i);
		else ans+=TREE[i]._ans;
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	LL m,kase=0;
	while(scanf("%lld%lld%lld",&N,&m,&L)==3)
	{
		ROAD.clear();
		for(LL i=1;i<=N;i++)
		{
			for(LL j=1;j<=N;j++)
			{
				RD[i][j]=L;
				BAN[i][j]=0;
			}
		}
		while(m--)
		{
			LL a,b,l;scanf("%lld%lld%lld",&a,&b,&l);
			RD[a][b]=RD[b][a]=l;
			ROAD.push_back((Pair){a,b});
		}
		LL ori,ans;
		ori=ans=cal();//return 0;
		for(LL i=0;i<ROAD.size();i+=2)
		{
			Pair &p=ROAD[i];
			BAN[p.x][p.y]=BAN[p.y][p.x]=1;
			getmax(ans,cal());
			BAN[p.x][p.y]=BAN[p.y][p.x]=0;
		}
		if(kase++)printf("\n");
		printf("%lld %lld\n",ori,ans);
	}
	return 0;
}
