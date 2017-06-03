#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
int N,C[100000],ANS[100000];
vector<int>ET[100000];
void Merge(map<int,int>*&asum,map<int,int>*&acnt,map<int,int>*&bsum,map<int,int>*&bcnt)
{
	if(acnt->size()<bcnt->size())swap(asum,bsum),swap(acnt,bcnt);
	for(const auto &p:*bcnt)
	{
		auto it=acnt->find(p.first);
		if(it==acnt->end())(*acnt)[p.first]=p.second,(*asum)[p.second]+=p.first;
		else
		{
			auto iu=asum->find(it->second);
			assert(iu!=asum->end());
			if(!(iu->second-=it->first))asum->erase(iu);
			it->second+=p.second;
			(*asum)[it->second]+=it->first;
		}
	}
	delete bsum;delete bcnt;
}
void Dfs(const int u,const int parent,map<int,int>*&sum,map<int,int>*&cnt)
{
	(*sum)[1]=C[u],(*cnt)[C[u]]=1;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		map<int,int>*chsum=new map<int,int>(),*chcnt=new map<int,int>();
		Dfs(nxt,u,chsum,chcnt);
		Merge(sum,cnt,chsum,chcnt);
	}
	ANS[u]=sum->rbegin()->second;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		{map<int,int>*a=new map<int,int>(),*b=new map<int,int>();Dfs(0,-1,a,b);delete a;delete b;}
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}
