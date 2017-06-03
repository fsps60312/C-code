#include<cstdio>
#include<cassert>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N,SEND[50000],PRE[50000],PRE_CNT,BCC[50000],BCC_CNT;
stack<int>STK;
int Dfs(const int u)
{
	STK.push(u);
	int low=PRE[u]=++PRE_CNT;
	const int nxt=SEND[u];
	if(!PRE[nxt])getmin(low,Dfs(nxt));
	else if(BCC[nxt]==-1)getmin(low,PRE[nxt]);
	if(low==PRE[u])
	{
		for(;;)
		{
			const int v=STK.top();STK.pop();
			BCC[v]=BCC_CNT;
			if(v==u)break;
		}
		BCC_CNT++;
	}
	return low;
}
int SIZE[50000];
vector<int>ET[50000];
int DP[50000];
int GetDP(const int u)
{
	int &ans=DP[u];
	if(ans!=-1)return ans;
	ans=SIZE[u];
	for(const int nxt:ET[u])ans+=GetDP(nxt);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			SEND[a]=b;
		}
		for(int i=0;i<N;i++)PRE[i]=0,BCC[i]=-1;
		PRE_CNT=BCC_CNT=0;
		for(int i=0;i<N;i++)if(!PRE[i])Dfs(i),assert(STK.empty());
		for(int i=0;i<BCC_CNT;i++)SIZE[i]=0,ET[i].clear(),DP[i]=-1;
		for(int i=0;i<N;i++)SIZE[BCC[i]]++;
		for(int i=0;i<N;i++)if(BCC[i]!=BCC[SEND[i]])
		{
			ET[BCC[i]].push_back(BCC[SEND[i]]);
		}
		for(int i=0;i<BCC_CNT;i++)sort(ET[i].begin(),ET[i].end()),ET[i].resize(unique(ET[i].begin(),ET[i].end())-ET[i].begin());
		int ans=0;
		for(int i=1;i<N;i++)if(GetDP(BCC[i])>GetDP(BCC[ans]))ans=i;
		static int kase=1;
		printf("Case %d: %d\n",kase++,ans+1);
	}
	return 0;
}
