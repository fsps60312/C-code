#include<cstdio>
#include<cassert>
#include<vector>
#include<stack>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M;
vector<int>ET[100000];
int PRE[100000],LOW[100000],PRE_CNT,BCC[100000],BCC_CNT,IN[100000];
stack<int>STK;
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(const int nxt:ET[u])
	{
		if(!PRE[nxt])
		{
			Dfs(nxt,u);
			getmin(LOW[u],LOW[nxt]);
		}
		else if(BCC[nxt]==-1)getmin(LOW[u],PRE[nxt]);
	}
	if(LOW[u]==PRE[u])
	{
		for(;;)
		{
			const int v=STK.top();STK.pop();
			BCC[v]=BCC_CNT;
			if(v==u)break;
		}
		BCC_CNT++;
	}
}
int Solve()
{
	for(int i=0;i<N;i++)PRE[i]=0,BCC[i]=-1;
	PRE_CNT=BCC_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1),assert(STK.empty());
	for(int i=0;i<BCC_CNT;i++)IN[i]=0;
	for(int u=0;u<N;u++)for(const int nxt:ET[u])if(BCC[u]!=BCC[nxt])IN[BCC[nxt]]++;
	int ans=0;
	for(int i=0;i<BCC_CNT;i++)if(IN[i]==0)ans++;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int a,b,i=0;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b);
		}
		printf("%d\n",Solve());
	}
	return 0;
}
