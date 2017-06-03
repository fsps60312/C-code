#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
int N,K,A,B;
vector<int>ET[100000];
bool VIS[100000];
int LOC,MX;
vector<int>PATH;
void Dfs(const int &u,const int &dep)
{
	if(VIS[u])return;
	VIS[u]=true;
	if(dep>MX)MX=dep,LOC=u;
	for(const int &et:ET[u])Dfs(et,dep+1);
	VIS[u]=false;
}
bool GetPath(const int &u)
{
	if(VIS[u])return false;
	VIS[u]=true;
	if(u==B){PATH.push_back(u);return true;}
	for(const int &et:ET[u])if(GetPath(et)){PATH.push_back(u);return true;}
	VIS[u]=false;
	return false;
}
int Solve()
{
	MX=0,Dfs(0,0);
	MX=0,Dfs(A=LOC,0);
	B=LOC;
	int ans=(N-1)*2-MX+1;
	if(K==1)return ans;
	PATH.clear();
	GetPath(A);
	assert(MX+1==PATH.size());
	int adjust=0,mx1=0,mx2=0;
	for(const int &u:PATH)
	{
		VIS[u]=false;
		MX=0,Dfs(u,0);
		if(MX>=mx1)mx2=mx1,mx1=MX;
		else if(MX>=mx2)mx2=MX;
		MX=0,Dfs(LOC,0);
		adjust=max(adjust,MX);
		VIS[u]=true;
	}
	adjust=max(adjust,mx1+mx2);
	if(adjust>=2)return ans-adjust+1;
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=false;
		for(int i=1;i<N;i++)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		printf("%d\n",Solve());
	}
	return 0;
}
