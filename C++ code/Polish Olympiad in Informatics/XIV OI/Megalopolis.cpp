#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Bit
{
	int S[250001],N;
	inline void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	inline void Add(int i,const int v){for(++i;i;i-=i&(-i))S[i]+=v;}
	inline void AddSegment(int l,int r,const int v){Add(r,v),Add(l-1,-v);}
	inline int Query(int i){int ans=0;for(++i;i<=N;i+=i&(-i))ans+=S[i];return ans;}
}BIT;
int N,M,L[250000],R[250000],DEPTH[250000];
vector<int>ET[250000];
void DfsSegments(const int u,const int parent,const int depth,int &tick)
{
	DEPTH[u]=depth;
	L[u]=tick;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)DfsSegments(ET[u][i],u,depth+1,tick);
	R[u]=tick++;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		{int tick=0;DfsSegments(0,-1,0,tick);assert(tick==N);}
		BIT.Clear(N);
		for(int u=1;u<N;u++)BIT.AddSegment(L[u],R[u],1);
		scanf("%d",&M);
		for(int i=0;i<N+M-1;i++)
		{
			static char type[2];scanf("%s",type);
			switch(type[0])
			{
				case'A':
				{
					int a,b;scanf("%d%d",&a,&b),--a,--b;
					if(DEPTH[a]>DEPTH[b])swap(a,b);
					BIT.AddSegment(L[b],R[b],-1);
				}break;
				case'W':
				{
					int u;scanf("%d",&u),--u;
					printf("%d\n",BIT.Query(R[u]));
				}break;
				default:assert(0);break;
			}
		}
	}
	return 0;
}
