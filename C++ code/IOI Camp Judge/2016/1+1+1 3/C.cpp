#include<cstdio>
#include<cassert>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M;
vector<int>ET[1000];
int PRE[1000],LOW[1000],PRE_CNT,BCC[1000],BCC_CNT;
stack<int>STK;
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		if(!PRE[nxt])Dfs(nxt,u),getmin(LOW[u],LOW[nxt]);
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
int IN[1000],OUT[1000];
int Solve()
{
	if(BCC_CNT==1)return 0;
	static vector<int>et[1000];
	for(int i=0;i<BCC_CNT;i++)et[i].clear();
	for(int u=0;u<N;u++)for(const int nxt:ET[u])if(BCC[u]!=BCC[nxt])et[BCC[u]].push_back(BCC[nxt]);
	for(int i=0;i<BCC_CNT;i++)sort(et[i].begin(),et[i].end()),et[i].resize(unique(et[i].begin(),et[i].end())-et[i].begin());
	int ans=0;
	for(int i=0;i<BCC_CNT;i++)
	{
		assert((int)et[i].size()>=1);
		if((int)et[i].size()==1)ans++;
	}
	assert(ans>=2);
	return (ans+1)/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)PRE[i]=0,BCC[i]=-1;
		PRE_CNT=BCC_CNT=0;
		Dfs(0,-1),assert(STK.empty());
		for(int i=0;i<N;i++)assert(PRE[i]);
		printf("%d\n",Solve());
	}
	return 0;
}
