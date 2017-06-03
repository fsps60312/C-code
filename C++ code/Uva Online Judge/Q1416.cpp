#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int N,L;
struct Rd{int x,y,z;};
vector<Rd> RD;
vector<int> CITY[101];
struct Trip{int x,y,pre;bool operator<(Trip a)const{return x>a.x;}};
struct Tree
{
	int _head[101],_next[1000],_to[1000],_val[1000],_nsz,_vis[101],_edge[1000],_ans;
	void clear()
	{
		_nsz=0;
		for(int i=1;i<=N;i++)_head[i]=-1,_vis[i]=0;
		for(int i=0;i<RD.size();i++)_edge[i]=0;
	}
	void addrd(int from,int to,int v)
	{
		_next[_nsz]=_head[from];
		_head[from]=_nsz;
		_to[_nsz]=to;
		_val[_nsz]=v;
		_nsz++;
	}
	bool needupdate()
	{
		for(int i=0;i<RD.size();i++)if((RD[i].z&&!_edge[i])||(!RD[i].z&&_edge[i]))return true;
		return false;
	}
	int buildtree(int u,int v)
	{
		if(!needupdate())return _ans;
		_ans=0;
		clear();
		priority_queue<Trip> pq;
		pq.push((Trip){0,u,0});
		while(!pq.empty())
		{
			Trip t=pq.top();pq.pop();
			if(_vis[t.y])continue;
			_vis[t.y]=1;
			_ans+=t.x;
			addrd(t.pre,t.y,t.x);
			for(int i=0;i<CITY[t.y].size();i++)
			{
				int j=CITY[t.y][i];
				if(!RD[j].z)continue;
				_edge[j]=1;
				pq.push((Trip){t.x+RD[j].y,RD[j].x,t.y});
			}
		}
		return _ans;
	}
};
Tree TREE[101];
int VIS[101][101];
void addRD(int a,int b,int l)
{
	VIS[a][b]=VIS[b][a]=1;
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
	for(int i=1;i<=N;i++)ans+=TREE[i].buildtree(i,0);
	return ans;
}
int main()
{
	int m,kase=0;
	while(scanf("%d%d%d",&N,&m,&L)==3)
	{
		for(int i=1;i<=N;i++)
		{
			CITY[i].clear();
			for(int j=1;j<=N;j++)VIS[i][j]=0;
		}
		while(m--)
		{
			int a,b,l;scanf("%d%d%d",&a,&b,&l);
			addRD(a,b,l);
		}
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=N;j++)
			{
				addRD(i,j,L);
			}
		}
		int ori,ans;
		ori=ans=cal();
		for(int i=0;i<RD.size();i++)
		{
			RD[i].z=0;
			getmax(ans,cal());
			RD[i].z=1;
		}
		if(kase++)printf("\n");
		printf("%d %d\n",ori,ans);
	}
	return 0;
}
