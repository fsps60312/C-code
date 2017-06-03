#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;
int R,VELO[500][500];
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
	return sz;
}
bool dfsprint(int sp,int ep,int v,int fa)
{
	if(sp==ep)
	{
		printf("%s",CITYNAME[sp].c_str());
		return true;
	}
	for(int i=0;i<ROAD[sp].size();i++)
	{
		int j=ROAD[sp][i];
		if(j==fa||v<VELO[sp][j])continue;
		if(dfsprint(j,ep,VELO[sp][j],sp));
		{
			printf(" %s",CITYNAME[sp].c_str());
			return true;
		}
	}
	return false;
}
void solve(int sp,int ep)
{
	if(!dfsprint(ep,sp,1000,-1))printf("No valid route.\n");
	else printf("\n");
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&R)==1)
	{
		CITYIDX.clear(),CITYNAME.clear();
		char tcity1[31],tcity2[31];
		while(R--)
		{
			int v;
			scanf("%s%s%d",tcity1,tcity2,&v);
			int a=getidx((string)tcity1),b=getidx((string)tcity2);
			VELO[a][b]=VELO[b][a]=v;
			ROAD[a].push_back(b);
			ROAD[b].push_back(a);
		}
		scanf("%s%s",tcity1,tcity2);
		solve(getidx((string)tcity1),getidx((string)tcity2));
	}
	return 0;
}
