#include<cstdio>
#include<vector>
using namespace std;
int N,UANS,CNTANS;
vector<int>ET[20000];
int Dfs(const int u,const int fa)
{
	int ans=1;
	vector<int>chsz;
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		int sz=Dfs(nxt,u);
		chsz.push_back(sz);
		ans+=sz;
	}
	chsz.push_back(N-ans);
	int ta=(N-1)*(N-2)/2;
	for(const int v:chsz)ta-=v*(v-1)/2;
	if(ta>CNTANS||(ta==CNTANS&&u<UANS))UANS=u,CNTANS=ta;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		CNTANS=UANS=-1;
		Dfs(0,-1);
		printf("%d %d\n",UANS+1,CNTANS);
	}
	return 0;
}
