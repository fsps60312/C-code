#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
int N,M;
multiset<int>ET[100000];
void AddEdge(const int a,const int b)
{
	ET[a].insert(b),ET[b].insert(a);
}
void Dfs(const int u,vector<int>&path)
{
//	printf("u=%d\n",u);
	while(!ET[u].empty())
	{
		const int nxt=*ET[u].begin();
		ET[u].erase(ET[u].begin());
		ET[nxt].erase(ET[nxt].find(u));
		Dfs(nxt,path);
	}
	path.push_back(u);
}
vector<vector<int> >ANS;
bool Solve()
{
	for(int i=0;i<N;i++)if(ET[i].size()&1)return false;
	static bool vis[100000];
	for(int i=0;i<N;i++)vis[i]=false;
	ANS.clear();
	for(int u=0;u<N;u++)if(!ET[u].empty())
	{
		vector<int>path;
		Dfs(u,path);
		vector<int>stk;
		for(int i=0;i<(int)path.size();i++)
		{
			stk.push_back(path[i]);
			if(vis[path[i]])
			{
				vector<int>ans;
				while(vis[stk.back()])
				{
					vis[stk.back()]=false;
					ans.push_back(stk.back());
					stk.pop_back();
				}
				ans.push_back(stk.back());
				ANS.push_back(ans);
			}
			vis[path[i]]=true;
		}
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b,f,t;i<M;i++)
		{
			scanf("%d%d%d%d",&a,&b,&f,&t),a--,b--;
			if(t<=f)t+=2;
			for(int j=0;j<t-f;j++)AddEdge(a,b);
		}
		if(!Solve())puts("NIE");
		else
		{
			printf("%d\n",(int)ANS.size());
			for(int i=0;i<(int)ANS.size();i++)
			{
				printf("%d",(int)ANS[i].size()-1);
				for(int j=0;j<(int)ANS[i].size();j++)printf(" %d",ANS[i][j]+1);
				puts("");
			}
		}
	}
	return 0;
}
