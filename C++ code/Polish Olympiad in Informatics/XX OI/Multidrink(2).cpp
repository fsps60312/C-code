#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N;
set<int>ET[500000];
int PATH[500000];
bool FindPath(const int u,const int parent)
{
	if(u==N-1)return true;
	for(const int nxt:ET[u])if(nxt!=parent&&FindPath(nxt,u)){PATH[u]=nxt;return true;}
	return false;
}
int PRE[500000];
bool VIS[500000];
int WalkOn(const int u,const int pre);
int WalkThrough(const int u,vector<int>&path)
{
	assert(!VIS[u]);
	VIS[u]=true;
	int cnt=0;
	for(const int nxt:ET[u])if(!VIS[nxt])
	{
		cnt++;
		if(cnt==1)
		{
			const int result=WalkOn(nxt,path);
			if(result==-1)return -1;
			path.push_back(u);
		}
		else if(cnt==2)
		{
			const int result=WalkThrough(nxt,path);
			
		}
	}
}
int WalkOn(const int u,vector<int>&path)
{
	assert(!VIS[u]);
	VIS[u]=true;
	path.push_back(u);
	int cnt=0;
	for(const int nxt:ET[u])if(!VIS[nxt])
	{
		cnt++;
		if(cnt==1)
		{
			const int result=WalkThrough(nxt,pre);
			if(result==-1)return false;
			path.push_back(nxt);
		}
	}
}
bool WalkDirectToDestination(const int u,const int pre)
{
	assert(!VIS[u]);
	VIS[u]=true;
	PRE[u]=pre;
	if(u==N-1)return true;
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
			ET[a].insert(b),ET[b].insert(a);
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
