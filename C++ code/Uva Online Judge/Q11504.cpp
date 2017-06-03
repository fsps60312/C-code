#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cassert>
using namespace std;
int T,N,M;
bool VIS[100000];
vector<int>TO[100000];
struct Domino
{
	int idx,indeg;
	bool operator<(Domino a)const{return indeg<a.indeg;}
}DOMINO[100000];
void PushDomino(int s)
{
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(VIS[u])continue;
		VIS[u]=true;
		for(int i=0;i<TO[u].size();i++)
		{
			int &j=TO[u][i];
			q.push(j);
		}
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			DOMINO[i].indeg=0;
			DOMINO[i].idx=i;
			VIS[i]=false;
		}
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			assert(a>=0&&a<N&&b>=0&&b<N);
			TO[a].push_back(b);
			DOMINO[b].indeg++;
		}
		sort(DOMINO,DOMINO+N);
		int ans=0;
		for(int ti=0;ti<N;ti++)
		{
			int &i=DOMINO[ti].idx;
			if(VIS[i])continue;
			PushDomino(i);
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
