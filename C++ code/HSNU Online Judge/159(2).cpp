#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
int N,M;
bool EDGE[3000][3000];
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=true;
	for(int i=0;i<N;i++)EDGE[i][i]=false;
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		EDGE[a][b]=EDGE[b][a]=false;
	}
	multimap<int,int>sot;
	for(int i=0;i<N;i++)
	{
		int deg=0;
		for(int j=0;j<N;j++)if(EDGE[i][j])deg++;
		sot.insert(make_pair(deg,i));
	}
	vector<int>ans;
	for(const auto &it:sot)
	{
		for(const int v:ans)if(EDGE[it.second][v])goto do_continue;
		ans.push_back(it.second);
		if((int)ans.size()==N/3)break;
		do_continue:;
	}
	assert((int)ans.size()==N/3);
	for(const int v:ans)printf("%d\n",v+1);
	return 0;
}
