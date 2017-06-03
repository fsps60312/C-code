#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int N,S[50][50];
vector<pair<int,int> >ANS;
vector<int>ET[50];
void Solve(const vector<int>&nodes)
{
	if(nodes.size()==1)return;
	int a=nodes[0],b=nodes[1];
	for(int i=0;i<(int)nodes.size();i++)
	{
		for(int j=i+1;j<(int)nodes.size();j++)
		{
			const int ni=nodes[i],nj=nodes[j];
			if(S[ni][nj]<S[a][b])a=ni,b=nj;
		}
	}
	ANS.push_back(make_pair(a,b));
	ET[a].push_back(b),ET[b].push_back(a); 
	vector<int>anodes,bnodes;
	anodes.push_back(a),bnodes.push_back(b);
	for(const int node:nodes)if(node!=a&&node!=b)
	{
		(S[a][node]<S[b][node]?bnodes:anodes).push_back(node);
	}
	Solve(anodes),Solve(bnodes);
}
int Dfs(const int u,const int parent,const int target,const int mn)
{
	if(u==target)return mn;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		const int result=Dfs(nxt,u,target,min(mn,S[u][nxt]));
		if(result!=-1)return result;
	}
	return -1;
}
bool Check()
{
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)
	{
		const int result=Dfs(i,-1,j,2147483647);
		assert(result!=-1);
		if(result!=S[i][j])return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)scanf("%d",&S[i][j]);
		vector<int>nodes;
		for(int i=0;i<N;i++)nodes.push_back(i),ET[i].clear();
		ANS.clear();
		Solve(nodes);
		if(Check())
		{
			puts("YES");
			printf("%d\n",N-1);
			assert((int)ANS.size()==N-1);
			for(const auto &p:ANS)printf("%d %d %d\n",p.first+1,p.second+1,S[p.first][p.second]);
		}
		else puts("NO");
	}
	return 0;
}
