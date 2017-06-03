#include<cstdio>
#include<cassert>
#include<vector>
#include<stack>
#include<utility>
#include<algorithm> 
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M;
vector<int>ET[10000];
int PRE[10000],LOW[10000],PRE_CNT=0;
int ANS[10000];
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	int &ans=ANS[u]=(fa==-1?0:1);
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		if(!PRE[nxt])
		{
			Dfs(nxt,u);
			getmin(LOW[u],LOW[nxt]);
			if(LOW[nxt]>=PRE[u])ans++;
		}
		else getmin(LOW[u],PRE[nxt]);
	}
}
struct Ans
{
	int cnt,idx;
	Ans(){}
	Ans(const int _cnt,const int _idx):cnt(_cnt),idx(_idx){}
	bool operator<(const Ans &a)const{return cnt!=a.cnt?cnt>a.cnt:idx<a.idx;}
};
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int a,b;scanf("%d%d",&a,&b)==2&&!(a==-1&&b==-1);)
		{
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)PRE[i]=0;
		PRE_CNT=0;
		int p=0;
		for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1),p++;
		vector<Ans>ans;
		for(int i=0;i<N;i++)ans.push_back(Ans(ANS[i],i));
		sort(ans.begin(),ans.end());
		for(int i=0;i<M;i++)printf("%d %d\n",ans[i].idx,ans[i].cnt-1+p);
	}
	return 0;
}
