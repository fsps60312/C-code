#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Pair
{
	int a,b;
	Pair(){}
	Pair(const int _a,const int _b):a(_a),b(_b){}
};
int N,M;
vector<int>ET[1000];
int PRE[1000],LOW[1000],PRE_CNT,NODE[1000],MXP[1000];
vector<Pair>ANS;
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const auto nxt:ET[u])if(nxt!=fa)
	{
		ANS.push_back(Pair(u,nxt));
		if(PRE[nxt])
		{
			getmin(LOW[u],PRE[nxt]);
			if(PRE[u]>MXP[nxt])MXP[nxt]=PRE[u],NODE[nxt]=u;
		}
		else
		{
			Dfs(nxt,u);
			getmin(LOW[u],LOW[nxt]);
		}
	}
//	if(MXP[u])ANS.push_back(Pair(NODE[u],u));
}
int main()
{
	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d",&N,&M)==2);
		if(N==0&&M==0)break;
		assert(N>=2&&N<=1000);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			assert(scanf("%d%d",&a,&b)==2);
			a--,b--;
			assert(a>=0&&a<N&&b>=0&&b<N);
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)PRE[i]=MXP[i]=0;
		PRE_CNT=0;
		ANS.clear();
		Dfs(0,-1);
//		for(int i=0;i<N;i++)printf(" %d",PRE[i]);puts("");
//		for(int i=0;i<N;i++)printf(" %d",LOW[i]);puts("");
		static int kase=1;
		printf("%d\n\n",kase++);
		for(const Pair &p:ANS)printf("%d %d\n",p.a+1,p.b+1);
		puts("#");
	}
	assert(scanf("%d",&N)!=1);
	return 0;
}
