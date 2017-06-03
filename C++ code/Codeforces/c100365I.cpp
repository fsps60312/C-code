#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,DP[100000][2];
vector<int>ET[100000];
bool VIS[100000];
void Dfs(const int u,const int fa)
{
	assert(!VIS[u]);
	VIS[u]=true;
	DP[u][0]=DP[u][1]=0;
	vector<int>s;
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		Dfs(nxt,u);
		s.push_back(DP[nxt][1]-DP[nxt][0]);
		DP[u][0]+=DP[nxt][0],DP[u][1]+=DP[nxt][0];
	}
	sort(s.begin(),s.end());
	if(s.empty())DP[u][0]++;
	else if((int)s.size()==1)DP[u][0]+=min(s[0]+1,1);
	else if((int)s.size()>=2)DP[u][0]+=min(min(s[0]+1,(s[0]+s[1])+1),1);
	else assert(0);
	if(!s.empty())DP[u][1]+=min(s[0],0);
}
int main()
{
	freopen("tour.in","r",stdin);
	freopen("tour.out","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=false;
		for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b),a--,b--,ET[a].push_back(b),ET[b].push_back(a);
		Dfs(0,-1);
		for(int i=0;i<N;i++)assert(VIS[i]); 
		printf("%d\n",DP[0][0]);
		break;
	}
	return 0;
}
