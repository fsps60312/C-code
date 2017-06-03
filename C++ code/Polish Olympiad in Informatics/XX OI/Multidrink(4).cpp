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
bool WalkOn(const int u,const int parent,vector<int>&path);
bool WalkBackOn(const int u,const int parent,vector<int>&path)
{
	bool walked=false;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		if(walked)return false;
		if(!WalkOn(nxt,u,path))return false;
		walked=true;
	}
	path.push_back(u);
	return true;
}
bool WalkOn(const int u,const int parent,vector<int>&path)
{
	path.push_back(u);
	bool walked=false;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		if(walked)return false;
		if(!WalkBackOn(nxt,u,path))return false;
		walked=true;
	}
	return true;
}
bool WalkDirectToDestination(const int u,const int parent,vector<int>&path,const bool allow_walk_later)
{
	printf("u=%d,parent=%d,allow_walk_later=%d\n",u+1,parent+1,(int)allow_walk_later);
	vector<int>nxts;
	for(const int nxt:ET[u])if(nxt!=PATH[u]&&nxt!=parent)nxts.push_back(nxt);
	if(u==N-1)
	{
		if(nxts.empty())
		{
			path.push_back(u);
			return true;
		}
		else if((int)nxts.size()==1)
		{
			if(allow_walk_later)
			{
				if(WalkOn(nxts[0],u,path))
				{
					path.push_back(u);
					return true;
				}
			}
			return false;
		}
		else return false;
	}
	else
	{
		if(nxts.empty())
		{
			path.push_back(u);
			return WalkDirectToDestination(PATH[u],u,path,true);
		}
		else if((int)nxts.size()==1)
		{
			const int sz=path.size();
			if(allow_walk_later)
			{
				if(WalkOn(nxts[0],u,path))
				{
					path.push_back(u);
					return WalkDirectToDestination(PATH[u],u,path,true);
				}
			}
			while((int)path.size()>sz)path.pop_back();
			path.push_back(u);
			if(WalkBackOn(nxts[0],u,path))return WalkDirectToDestination(PATH[u],u,path,false);
			return false;
		}
		else if((int)nxts.size()==2)
		{
			if(allow_walk_later)
			{
				const int sz=path.size();
				if(WalkOn(nxts[0],u,path))
				{
					path.push_back(u);
					if(WalkBackOn(nxts[1],u,path))
					{
						return WalkDirectToDestination(PATH[u],u,path,false);
					}
				}
				while((int)path.size()>sz)path.pop_back();
				if(WalkOn(nxts[1],u,path))
				{
					path.push_back(u);
					if(WalkBackOn(nxts[0],u,path))
					{
						return WalkDirectToDestination(PATH[u],u,path,false);
					}
				}
			}
			return false;
		}
		return false;
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
		vector<int>path;
		if(!WalkDirectToDestination(0,-1,path,false))puts("BRAK");
		else
		{
			for(const int v:path)printf("%d\n",v+1);
		}
	}
	return 0;
}
