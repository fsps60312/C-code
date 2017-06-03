#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,M,K,ANS[9999];
vector<int>ET[9999];
bool VIS[9999];
set<int>BANNED[9999];
void Dfs(const int u)
{
	if(VIS[u])return;
	VIS[u]=true;
	for(int i=0;i<(int)ET[u].size();i++)Dfs(ET[u][i]);
	int &ans=ANS[u]=1;
	for(set<int>::iterator it=BANNED[u].begin();it!=BANNED[u].end()&&(*it)==ans;it++,ans++);
	assert(ans<=K);
	for(int i=0;i<(int)ET[u].size();i++)BANNED[ET[u][i]].insert(ans);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),a--,b--,ET[a].push_back(b),ET[b].push_back(a);
		K=0;
		for(int i=0;i<N;i++)getmax(K,(int)ET[i].size());
		if(K%2==0)K++;
		int mn=INF,source=-1;
		for(int i=0;i<N;i++)if((int)ET[i].size()<mn)mn=(int)ET[i].size(),source=i;
		for(int i=0;i<N;i++)
		{
			VIS[i]=false;
			BANNED[i].clear();
		}
		Dfs(source);
		printf("%d\n",K);
		for(int i=0;i<N;i++)printf("%d\n",ANS[i]);
		break;
	}
	return 0;
}
