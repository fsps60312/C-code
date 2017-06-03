#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;
int R,PRE[500];
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
	PRE[sz]=-1;
	return sz;
}
void dfsprint(int u)
{
	if(PRE[u]==-1)
	{
		printf("%s",CITYNAME[u].c_str());
		return;
	}
	dfsprint(PRE[u]);
	printf(" %s",CITYNAME[u].c_str());
}
void solve(int sp,int ep)
{
	queue<int> q;
	q.push(sp);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(u==ep)break;
		for(int i=0;i<ROAD[u].size();i++)
		{
			int j=ROAD[u][i];
			if(j==sp||PRE[j]!=-1)continue;
			PRE[j]=u;
			q.push(j);
		}
	}
	if(PRE[ep]==-1)printf("No valid route.\n");
	else
	{
		//printf("pass\n");
		dfsprint(ep);
		printf("\n");
	}
}
int main()
{
	while(scanf("%d",&R)==1)
	{
		CITYIDX.clear(),CITYNAME.clear();
		char tcity1[31],tcity2[31];
		while(R--)
		{
			scanf("%s%s",tcity1,tcity2);
			ROAD[getidx((string)tcity1)].push_back(getidx((string)tcity2));
			ROAD[getidx((string)tcity2)].push_back(getidx((string)tcity1));
		}
		scanf("%s%s",tcity1,tcity2);
		solve(getidx((string)tcity1),getidx((string)tcity2));
	}
	return 0;
}