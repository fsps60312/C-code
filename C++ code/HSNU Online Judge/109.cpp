#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
int T,N,M;
vector<int>ET[15];
int X[15],Y[15],FA[15],USED_LOC[15];
vector<int>ORDER;
void Traverse(const int u,const int fa)
{
	ORDER.push_back(u);
//	printf("u=%d\n",u);
	FA[u]=fa;
	for(int i=0;i<ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt==fa)continue;
		Traverse(nxt,u);
	}
}
int ANS;
inline int Sq(const int a){return a*a;}
inline int Cost(const int a,const int b)
{
	return Sq(X[a]-X[b])+Sq(Y[a]-Y[b]);
}
void Dfs(const int dep,const int cost)
{
	if(cost>=ANS)return;
	if(dep==N*M){ANS=cost;return;}
	const int u=ORDER[dep];
	assert(FA[u]!=-1);
	for(int i=0;i<N*M;i++)
	{
		if(USED_LOC[i])continue;
		USED_LOC[i]=true;
		Y[u]=i/M,X[u]=i%M;
		Dfs(dep+1,cost+Cost(FA[u],u));
		USED_LOC[i]=false;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&M,&N);
		for(int i=0;i<N*M;i++)ET[i].clear(),USED_LOC[i]=false,FA[i]=-1;
		for(int i=1;i<N*M;i++)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		ORDER.clear();
		Traverse(0,-1);
//		for(int i=0;i<N*M;i++)printf("order=%d,fa=%d\n",ORDER[i],FA[ORDER[i]]);
		ANS=INF;
		for(int i=0,u=ORDER[0];i<N*M;i++)
		{
			USED_LOC[i]=true;
			Y[u]=i/M,X[u]=i%M;
			Dfs(1,0);
			USED_LOC[i]=false;
		}
		printf("%d\n",ANS);
	}
	return 0;
}
