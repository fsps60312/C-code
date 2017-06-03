#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,F[1000];
vector<int>CYC;
void BuildCYC()
{
	static bool vis[1000];
	for(int i=0;i<N;i++)vis[i]=false;
	int cur=0;
	for(;!vis[cur];cur=F[cur])vis[cur]=true;
	CYC.clear();
	for(;vis[cur];cur=F[cur])vis[cur]=false,CYC.push_back(cur);
	for(const int u:CYC)F[u]=-1;
}
vector<int>ET[1000];
void BuildGraph()
{
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<N;i++)if(F[i]!=-1)ET[F[i]].push_back(i);
}
int Height(const int u)
{
	int ans=1;
	for(const int nxt:ET[u])getmax(ans,Height(nxt)+1);
	return ans;
}
int Solve()
{
	vector<int>hs;
	for(const int u:CYC)hs.push_back(Height(u));
	const int n=hs.size();
	if(n>2)return n;
	assert(n==2);
	return max(2,hs[0]+hs[1]);
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&F[i]),--F[i];
		BuildCYC();
		BuildGraph();
		static int kase=0;
		printf("Case #%d: %d\n",++kase,Solve());
	}
	return 0;
}
