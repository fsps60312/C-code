#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;
int R,PRE[500][500],VELO[500][500];
map<string,int> CITYIDX;
map<int,string> CITYNAME;
vector<int> ROAD[500];
int getidx(string name)
{
	if(CITYIDX.find(name)!=CITYIDX.end())return CITYIDX[name];
	int sz=CITYIDX.size();
	CITYIDX[name]=sz;
	CITYNAME[sz]=name;
	ROAD[sz].clear();
	for(int i=0;i<500;i++)PRE[sz][i]=-1;
	//PRE[sz]=-1;
	return sz;
}
void dfsprint(int u,int cn)
{
	if(PRE[u][cn]==-1)
	{
		printf("%s",CITYNAME[u].c_str());
		return;
	}
	dfsprint(PRE[u][cn],cn-1);
	printf(" %s",CITYNAME[u].c_str());
}
void solve(int sp,int ep)
{
	queue<int> q;
	q.push(sp),q.push(0),q.push(0);
	int u,v,cn;
	while(!q.empty())
	{
		u=q.front();q.pop();
		v=q.front();q.pop();
		cn=q.front();q.pop();
		if(u==ep)break;
		for(int i=0;i<ROAD[u].size();i++)
		{
			int j=ROAD[u][i];
			if(j==sp||v>VELO[u][j]||PRE[j][cn+1]!=-1)continue;
			PRE[j][cn+1]=u;
			q.push(j),q.push(VELO[u][j]),q.push(cn+1);
		}
	}
	if(PRE[ep][cn]==-1)printf("No valid route.\n");
	else
	{
		//printf("pass\n");
		dfsprint(ep,cn);
		printf("\n");
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=0;
	while(scanf("%d",&R)==1)
	{
		if(kase++)printf("\n");
		CITYIDX.clear(),CITYNAME.clear();
		char tcity1[31],tcity2[31];
		while(R--)
		{
			int v;
			scanf("%s%s%d",tcity1,tcity2,&v);
			int a=getidx((string)tcity1),b=getidx((string)tcity2);
			VELO[a][b]=VELO[b][a]=v;
			ROAD[a].push_back(b);
			for(int i=ROAD[a].size()-1;i>0&&ROAD[a][i]<ROAD[a][i-1];i--)ROAD[a][i]^=ROAD[a][i-1]^=ROAD[a][i]^=ROAD[a][i-1];
			ROAD[b].push_back(a);
			for(int i=ROAD[b].size()-1;i>0&&ROAD[b][i]<ROAD[b][i-1];i--)ROAD[b][i]^=ROAD[b][i-1]^=ROAD[b][i]^=ROAD[b][i-1];
		}
		//printf(" %d %d\n",getidx("y"),getidx("z"));
		//for(int u=getidx("g"),i=0;i<ROAD[u].size();i++)printf(" %d",ROAD[u][i]);printf("\n");
		scanf("%s%s",tcity1,tcity2);
		solve(getidx((string)tcity1),getidx((string)tcity2));
	}
	return 0;
}
