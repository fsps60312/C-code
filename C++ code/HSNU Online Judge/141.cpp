#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int N,M,DEG[50000];
vector<int>ET[50000],ANS;
void Solve()
{
	queue<int>q;
	for(int i=0;i<N;i++)if(DEG[i]==0)q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		ANS.push_back(u);
		for(const int nxt:ET[u])if(--DEG[nxt]==0)q.push(nxt);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)DEG[i]=0;
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b),DEG[b]++;
	}
	ANS.clear();
	Solve();
	if((int)ANS.size()!=N)puts("-1");
	else for(const int v:ANS)printf("%d\n",v+1);
	return 0;
}
