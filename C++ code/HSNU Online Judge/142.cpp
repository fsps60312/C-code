#include<cstdio>
#include<vector>
#include<stack>
#include<cassert>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;} 
int N,M,ANS;
vector<int>ET[50000];
int PRE[50000],LOW[50000],PRE_CNT;
bool VIS[50000];
stack<int>STK;
void Dfs(const int u,const int fa)
{
	STK.push(u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		if(PRE[nxt])getmin(LOW[u],PRE[nxt]);
		else if(!VIS[nxt])
		{
			Dfs(nxt,u);
			getmin(LOW[u],LOW[nxt]);
			if(LOW[u]<LOW[nxt])ANS++;
		}
	}
	if(LOW[u]==PRE[u])
	{
		for(;;)
		{
			const int v=STK.top();STK.pop();
			VIS[v]=true;
			if(v==u)break;
		}
	}
} 
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)PRE[i]=0,VIS[i]=false,ET[i].clear();
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	ANS=PRE_CNT=0;
	assert(STK.empty());
	Dfs(0,-1);
	assert(STK.empty());
	printf("%d\n",ANS);
	return 0;
}
