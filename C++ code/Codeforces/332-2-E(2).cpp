#include<cstdio>
#include<cassert>
#include<set>
#include<vector>
using namespace std;
typedef long long LL;
int N,M,Q;
LL DP[13][1<<13];//root,s
set<int>ET[13];
struct Lca
{
	int a,b;
	Lca(){}
	Lca(const int _a,const int _b):a(_a),b(_b){}
};
vector<Lca>LCA[13];
int Lowbit(const int a){return a&(-a);}
LL GetDP(const int root,const int s)
{
	assert(s&(1<<root));
	LL &dp=DP[root][s];
	if(dp!=-1LL)return dp;
	for(int i=0;i<LCA[root].size();i++)if(!(s&(1<<LCA[root][i].a))||!(s&(1<<LCA[root][i].b)))return dp=0LL;
	if(s==(1<<root))return dp=1LL;
	dp=0LL;
	for(int sch=s-(1<<root);sch;sch=(sch-1)&(s-(1<<root)))if(sch&Lowbit(s-(1<<root)))
	{
//		if(root==1&&s==14)printf("sch=%d\n",sch);
		vector<int>must;
		for(int i=0;i<N;i++)if((sch&(1<<i))&&ET[root].find(i)!=ET[root].end())must.push_back(i);
		if(must.size()>=2)continue;
//		if(root==1&&s==14)puts("a");
		bool valid=true;
		for(int i=0;i<LCA[root].size();i++)if((sch&(1<<LCA[root][i].a))&&(sch&(1<<LCA[root][i].b))){valid=false;break;}
		if(!valid)continue;
//		if(root==1&&s==14)puts("b");
//		LL tdp=dp;
		if(must.size()==1)
		{
			dp+=GetDP(must[0],sch)*GetDP(root,s^sch);
//		if(root==1&&s==14)puts("c");
		}
		else
		{
//		if(root==1&&s==14)puts("d");
			assert(must.empty());
			LL ta=0LL;
			for(int i=0;i<N;i++)if(sch&(1<<i))ta+=GetDP(i,sch);
//		if(root==1&&s==14)printf("ta=%lld,dp(%d,%d)=%lld\n",ta,root,s^sch,GetDP(root,s^sch));
			dp+=ta*GetDP(root,s^sch);
		}
//		if(root==1&&s==14)printf("gain %lld\n",dp-tdp);
	}
//	printf("(%d,%d)=%lld\n",root,s,dp);
	return dp;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&Q)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].insert(b),ET[b].insert(a);
		}
		for(int i=0;i<N;i++)LCA[i].clear();
		for(int i=0,a,b,c;i<Q;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--,c--;
			LCA[c].push_back(Lca(a,b));
		}
		for(int i=0;i<N;i++)for(int j=0;j<(1<<N);j++)DP[i][j]=-1LL;
		printf("%I64d\n",GetDP(0,(1<<N)-1));
	}
	return 0;
}
