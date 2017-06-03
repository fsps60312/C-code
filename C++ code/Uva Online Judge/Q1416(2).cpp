#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int N,L;
struct Rd{int x,y,z;};
vector<Rd> RD;
vector<int> CITY[201];
struct Trip{int x,y;bool operator<(Trip a)const{return x>a.x;}};
struct Tree
{
	int _vis[201],_edge[8000],_ans;
	void clear()
	{
		_ans=0;
		for(int i=1;i<=N;i++)_vis[i]=0;
		for(int i=0;i<RD.size();i++)_edge[i]=0;
	}
	bool needupdate()
	{
		for(int i=0;i<RD.size();i++)if((RD[i].z&&!_edge[i])||(!RD[i].z&&_edge[i]))return true;
		return false;
	}
	int buildtree(int u)
	{
		if(!needupdate())return _ans;
		clear();
		priority_queue<Trip> pq;
		pq.push((Trip){0,u});
		while(!pq.empty())
		{
			Trip t=pq.top();pq.pop();
			if(_vis[t.y])continue;
			_vis[t.y]=1;
			_ans+=t.x;
			for(int i=0;i<CITY[t.y].size();i++)
			{
				int j=CITY[t.y][i];
				if(!RD[j].z)continue;
				_edge[j]=1;
				pq.push((Trip){t.x+RD[j].y,RD[j].x});
			}
		}
		return _ans;
	}
};
Tree TREE[201];
void addRD(int a,int b,int l)
{
	int sz=RD.size();
	RD.push_back((Rd){b,l,1});
	CITY[a].push_back(sz++);
	RD.push_back((Rd){a,l,1});
	CITY[b].push_back(sz);
}
void getmax(int &a,int b){if(b>a)a=b;}
int cal()
{
	int ans=0;
	for(int i=1;i<=N;i++)
	{
		//printf("city %d = %d\n",i,TREE[i].buildtree(i));
		ans+=TREE[i].buildtree(i);
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int m,kase=0;
	while(scanf("%d%d%d",&N,&m,&L)==3)
	{
		for(int i=1;i<=N;i++)
		{
			CITY[i].clear();
		}
		while(m--)
		{
			int a,b,l;scanf("%d%d%d",&a,&b,&l);
			addRD(a,b,l);
		}
		for(int i=1;i<=N;i++)
		{
			for(int j=i+1;j<=N;j++)
			{
				addRD(i,j,L);
			}
		}
		int ori,ans;
		ori=ans=cal();//return 0;
		for(int i=0;i<RD.size();i+=2)
		{
			RD[i].z=RD[i+1].z=0;
			//printf("cal(%d)=%d\n",i,cal());
			getmax(ans,cal());
			RD[i].z=RD[i+1].z=1;
		}
		if(kase++)printf("\n");
		printf("%d %d\n",ori,ans);
	}
	return 0;
}
