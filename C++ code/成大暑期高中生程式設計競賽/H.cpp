#include<cstdio>
#include<cassert>
#include<vector>
//#define int long long
//#include<algorithm>
using namespace std;
//const int INF=2147483647;
//template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
long long ANS;
int N,SZ[30000];
vector<int>ET[30000];
int GetSZ(const int u,const int parent)
{
//	printf("u=%d\n",u+1);
	int &sz=SZ[u]=1;
	for(const int nxt:ET[u])if(nxt!=parent)sz+=GetSZ(nxt,u);
	return sz;
}
void Dfs(const int u,const int parent,const int up_size)
{
	int sum=up_size;
	long long ta=0;
	for(const int nxt:ET[u])if(nxt!=parent)ta+=(long long)sum*SZ[nxt],sum+=SZ[nxt];
	assert(sum==N-1);
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		Dfs(nxt,u,1+sum-SZ[nxt]);
//		printf("sum=%d,sz=%d\n",sum,SZ[nxt]);
	}
//	printf("u=%d,parent=%d,up_size=%d,ta=%lld\n",u+1,parent+1,up_size,ta);
	getmax(ANS,ta);
}
main()
{
//	freopen("inh.txt","r",stdin);
	freopen("out.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
//			printf("(%d,%d)\n",a,b);
		}
		ANS=0;
		GetSZ(0,-1);
		Dfs(0,-1,0);
		printf("%lld\n",ANS);
	}
	return 0;
}
