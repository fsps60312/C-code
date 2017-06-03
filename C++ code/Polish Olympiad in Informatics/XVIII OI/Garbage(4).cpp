#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
int N,M,DEG[100000];
map<int,int>ET[100000];
void AddEdge(const int a,const int b)
{
	++ET[a][b],++ET[b][a];
	DEG[a]++,DEG[b]++;
}
int PATH[1000000],PSZ;
void Dfs(const int u)
{
	map<int,int>&et=ET[u];
	while(!et.empty())
	{
		map<int,int>::iterator it=et.begin();
		const int nxt=it->first;
		if(!--it->second)et.erase(it);
		it=ET[nxt].find(u);
		if(!--it->second)ET[nxt].erase(it);
		Dfs(nxt);
	}
	PATH[++PSZ]=u;
}
vector<vector<int> >ANS;
bool Solve()
{
	for(int i=0;i<N;i++)if(DEG[i]&1)return false;
	static bool vis[100000];
	for(int i=0;i<N;i++)vis[i]=false;
	ANS.clear();
	for(int u=0;u<N;u++)if(!ET[u].empty())
	{
		PSZ=-1;
		Dfs(u);
		static int stk[1000000];
		int ssz=-1;
		for(int i=0;i<=PSZ;i++)
		{
			stk[++ssz]=PATH[i];
			if(vis[PATH[i]])
			{
				vector<int>ans;
				while(vis[stk[ssz]])
				{
					vis[stk[ssz]]=false;
					ans.push_back(stk[ssz]);
					--ssz;
				}
				ans.push_back(stk[ssz]);
				ANS.push_back(ans);
			}
			vis[PATH[i]]=true;
		}
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),DEG[i]=0;
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
