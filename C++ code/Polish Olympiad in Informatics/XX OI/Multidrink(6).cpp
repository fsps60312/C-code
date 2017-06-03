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
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=parent&&FindPath(nxt,u)){PATH[u]=nxt;return true;}
	}
	return false;
}
bool WalkOn(const int u,const int parent,vector<int>&path);
bool WalkBackOn(const int u,const int parent,vector<int>&path)
{
	bool walked=false;
	vector<int>one;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=parent)
		{
			if((int)ET[nxt].size()==1)
			{
				one.push_back(nxt);
			}
			else
			{
				if(walked)return false;
				if(!WalkOn(nxt,u,path))return false;
				walked=true;
			}
		}
	}
	for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
	path.push_back(u);
	return true;
}
bool WalkOn(const int u,const int parent,vector<int>&path)
{
	path.push_back(u);
	bool walked=false;
	vector<int>one;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=parent)
		{
			if((int)ET[nxt].size()==1)
			{
				one.push_back(nxt);
			}
			else
			{
				if(walked)return false;
				if(!WalkBackOn(nxt,u,path))return false;
				walked=true;
			}
		}
	}
	for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
	return true;
}
bool WalkDirectToDestination(const int u,const int parent,vector<int>&path,const bool allow_walk_later)
{
//	printf("u=%d,parent=%d,allow_walk_later=%d\n",u+1,parent+1,(int)allow_walk_later);
	vector<int>nxts,one;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=PATH[u]&&nxt!=parent)
		{
			if((int)ET[nxt].size()==1)one.push_back(nxt);
			else nxts.push_back(nxt);
		}
	}
	if(u==N-1)
	{
		if(nxts.empty())
		{
			if(!one.empty())
			{
				if(!allow_walk_later)return false;
				for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
			}
			path.push_back(u);
			return true;
		}
		else if((int)nxts.size()==1)
		{
			if(allow_walk_later)
			{
				if(WalkOn(nxts[0],u,path))
				{
					for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
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
			if(!one.empty())
			{
				if(allow_walk_later)
				{
					for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
					path.push_back(u);
					return WalkDirectToDestination(PATH[u],u,path,true);
				}
				else
				{
					path.push_back(u);
					for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
					return WalkDirectToDestination(PATH[u],u,path,false);
				}
			}
			else
			{
				path.push_back(u);
				return WalkDirectToDestination(PATH[u],u,path,true);
			}
			return false;
		}
		else if((int)nxts.size()==1)
		{
			const int sz=path.size();
			if(allow_walk_later)
			{
				for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
				if(WalkOn(nxts[0],u,path))
				{
					path.push_back(u);
					return WalkDirectToDestination(PATH[u],u,path,true);
				}
			}
			while((int)path.size()>sz)path.pop_back();
			path.push_back(u);
			if(WalkBackOn(nxts[0],u,path))
			{
				for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
				return WalkDirectToDestination(PATH[u],u,path,false);
			}
			return false;
		}
		else if((int)nxts.size()==2)
		{
			if(allow_walk_later)
			{
				const int sz=path.size();
				for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
				if(WalkOn(nxts[0],u,path))
				{
					path.push_back(u);
					if(WalkBackOn(nxts[1],u,path))
					{
						return WalkDirectToDestination(PATH[u],u,path,false);
					}
				}
				while((int)path.size()>sz)path.pop_back();
				for(int i=0;i<(int)one.size();i++)path.push_back(one[i]);
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
//	freopen("in.txt","r",stdin);
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
			for(int i=0;i<(int)path.size();i++)printf("%d\n",path[i]+1);
		}
	}
	return 0;
}
