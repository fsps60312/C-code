#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL &b){if(b>a)a=b;}
int N,EDGE[699][2];
vector<int>ET[700];
LL DP[699][2];
LL GetDP(const int ei,const int d)
{
	LL &ans=DP[ei][d];
	if(ans!=-1LL)return ans;
	const int u=EDGE[ei][d];
	
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N-1;i++)
		{
			int &a=EDGE[i][0],&b=EDGE[i][1];
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		LL ans=0LL;
		for(int i=0;i<N-1;i++)getmax(ans,GetDP(i,0)*GetDP(i,1);
		printf("%lld\n",ans);
	}
	return 0;
}
