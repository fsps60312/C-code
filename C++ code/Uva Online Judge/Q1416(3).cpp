#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#define LL long long
using namespace std;
LL N,L;
struct Rd{LL x,y,z;};
vector<Rd> RD;
vector<LL> CITY[201];
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
		for(LL i=0;i<RD.size();i++)if((RD[i].z&&!_edge[i])||(!RD[i].z&&_edge[i]))return true;
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
			for(LL i=0;i<CITY[t.y].size();i++)
			{
				LL j=CITY[t.y][i];
				if(!RD[j].z)continue;
				_edge[j]=1;
				pq.push((Trip){t.x+RD[j].y,RD[j].x});
			}
		}
		return _ans;
	}
};
Tree TREE[201];
void addRD(LL a,LL b,LL l)
{
	LL sz=RD.size();
	RD.push_back((Rd){b,l,1});
	CITY[a].push_back(sz++);
	RD.push_back((Rd){a,l,1});
	CITY[b].push_back(sz);
}
void getmax(LL &a,LL b){if(b>a)a=b;}
LL cal()
{
	LL ans=0;
	for(LL i=1;i<=N;i++)
	{
		//printf("city %lld = %lld\n",i,TREE[i].buildtree(i));
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
		for(LL i=1;i<=N;i++)
		{
			CITY[i].clear();
		}
		while(m--)
		{
			LL a,b,l;scanf("%lld%lld%lld",&a,&b,&l);
			addRD(a,b,l);
		}
		for(LL i=1;i<=N;i++)
		{
			for(LL j=i+1;j<=N;j++)
			{
				addRD(i,j,L);
			}
		}
		LL ori,ans;
		ori=ans=cal();//return 0;
		for(LL i=0;i<RD.size();i+=2)
		{
			RD[i].z=RD[i+1].z=0;
			//printf("cal(%lld)=%lld\n",i,cal());
			getmax(ans,cal());
			RD[i].z=RD[i+1].z=1;
		}
		if(kase++)printf("\n");
		printf("%lld %lld\n",ori,ans);
	}
	return 0;
}
