#include<cstdio>
#include<cstdlib>
#include<set>
#include<vector>
using namespace std;
struct pairtype
{
	long long x;
	long long y;
	bool operator(pairtype a,pairtype b)
	{
		if(a.x!=b.x) return a.x<b.x:
		return a.y<b.y;
	}
};
struct Stype
{
	vector<int> to;
	vector<int> from;
	bool infinity;
}
int n,x[100];
long long vis[100][2];
vector<int> visv[100];
map<pairtype,int> vism;
vector<int> infinity;
vector<int> finity;
void dfs(int a,long long b,long long c)
{
	if(a<50) b|=1<<a;
	else c|=1<<(a-50);
	b|=vis[a][0];
	c|=vis[a][1];
	if(vis[a][0]==b&&vis[a][1]==c) return;
	for(int i=0;i<side[a].size();i++)
	{
		int j=side[a][i];
		dfs(j,b,c);
	}
}
int main()
{
	while(scanf("%d",&n)==1)
	{
		for(int i=0;i<n;i++)
		{
			vis[i][0]=vis[i][1]=0;
			visv[i].clear();
		}
		while(scanf("%d%d",&x[0],&x[1])==2)
		{
			if(x[0]==0&&x[1]==0) break;
			side[--x[0]].push_back(--x[1]);
		}
		scanf("%d",&q);
		for(int i=0;i<q;i++) scanf("%d",&x[i]);
		//find loops
		for(int i=0;i<n;i++)
		{
			dfs(i,0,0);
		}
		vism.clear();
		for(int i=0;i<n;i++)
		{
			pairtype j;
			j.x=vis[i][0];
			j.y=vis[i][1];
			if(vism.find(j)==vism.end())
			{
				vism[j]=vism.size()-1;
			}
			visv[vism[j]].push_back(i);
		}
		infinity.clear();
		finity.clear();
		for(int i=0;vist[i].size();i++)
		{
			if(visv[i].size()==1)
			{
				finity.push_back(visv[i][0]);
			}
			else
			{
				for(int j=0;j<vist[i].size();j++)
				{
					int k=vist[i][j];
					infinity.push_back(k);
				}
			}
		}
	}
	return 0;
}
