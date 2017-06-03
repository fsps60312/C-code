#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,K,VIS[10];
vector<int>C[10];
void Dfs(const int &u,const int &dep)
{
	if(dep==0)
	{
		static vector<int>s;s.clear();
		int ans=0;
		for(int i=0;i<10;i++)if(VIS[i])
		{
			
			for(int j=1;j<C[i].size();j++)s.push_back(C[i][j]);
		}
		sort(s.begin(),s.end());
		
		return;
	}
	VIS[u]=true;
	for(int i=u+1;i<10;i++)Dfs(i,dep-1);
	VIS[u]=false;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&K);
	for(int i=0;i<10;i++)C[i].clear(),VIS[i]=false;
	for(int i=0,c,g;i<N;i++)
	{
		scanf("%d%d",&c,&g);
		C[--g].push_back(c);
	}
	for(int i=1;i<=10&&i<=K;i++)
	{
		
	}
	return 0;
}
