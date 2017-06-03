#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
typedef priority_queue<LL,vector<LL>,greater<LL> > PqLL;
int N,ROOT;
LL M,C[100000],L[100000];
vector<int>ET[100000];
LL ANS;
PqLL *Dfs(const int u)
{
	auto *pq=new PqLL();
	pq->push(C[u]);
	for(int i=0;i<ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		PqLL *tmp=Dfs(nxt);
		if(tmp->size()>pq->size())swap(tmp,pq);
		while(!tmp->empty())pq->push(tmp->top()),tmp->pop();
	}
	return pq;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%lld",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	ROOT=-1;
	for(int i=0,v;i<N;i++)
	{
		scanf("%d%lld%lld",&v,&C[i],&L[i]);
		if(v==0)assert(ROOT==-1),ROOT=i;
		else ET[--v].push_back(i);
	}
	ANS=0;
	Dfs(ROOT);
	printf("%lld\n",ANS);
	return 0;
}
