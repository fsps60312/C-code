#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N;
vector<int>ET[500000];
int PATH[500000];
bool FindPath(const int u,const int parent)
{
	if(u==N-1)return true;
	for(const int nxt:ET[u])if(nxt!=parent&&FindPath(nxt,u)){PATH[u]=nxt;return true;}
	return false;
}
bool VIS[500000];
bool WalkOn(const int u,const int parent);
bool CAN_WALK_BACK_ON[500000];
bool WalkBackOn(const int u,const int parent)
{
	bool &ans=CAN_WALK_BACK_ON[u];
	if(VIS[u])return ans;
	VIS[u]=true;
	bool walked=false;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		if(walked)return false;
		if(!WalkOn(nxt,u))return ans=false;
		walked=true;
	}
	//if(!walked)Walk(u);
	return true;
}
bool CAN_WALK_ON[500000];
bool WalkOn(const int u,const bool parent)
{
	bool &ans=CAN_WALK_ON[u];
	if(VIS[u])return ans;
	VIS[u]=true;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		if(!WalkBackOn(nxt,u))return ans=false;
	}
	return ans=true;
}
bool WalkDirectToDestination(const int u,const int parent,vector<int>&path)
{
	vector<int>nxts;
	for(const int nxt:ET[u])if(nxt!=PATH[u]&&nxt!=parent)nxts.push_back(nxt);
	if(u==N-1)
	{
		assert(0);
	}
	else
	{
		
	}
}
bool Solve()
{
	for(int cur=0;;)
	{
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)PATH[i]=-1;
		assert(FindPath(0,-1));
		for(int i=0;i<N;i++)VIS[i]=false;
		if(!Solve())puts("BRAK");
		else
		{
			int cur=0;
			vector<int>ans;
			for(;;cur=NEXT[cur])
			{
				printf("%d\n",cur);
				if(cur==N-1)break;
			}
		}
	}
	return 0;
}
