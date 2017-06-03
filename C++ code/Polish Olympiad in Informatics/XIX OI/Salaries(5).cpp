#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int N,BOSS[1000001],SALARY[1000001];
int SZ[1000001];
vector<int>ET[1000001];
void BuildSZ()
{
	static int deg[1000001];
	for(int i=1;i<=N;i++)deg[i]=0,SZ[i]=1;
	for(int i=1;i<=N;i++)if(BOSS[i]!=i)deg[BOSS[i]]++,ET[BOSS[i]].push_back(i);
	queue<int>q;
	for(int i=1;i<=N;i++)if(ET[i].empty())q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(BOSS[u]==u){assert(q.empty());break;}
		SZ[BOSS[u]]+=SZ[u];
		if(!--deg[BOSS[u]])q.push(BOSS[u]);
	}
}
int CEO;
bool CmpBossSalary(const int a,const int b){return SALARY[BOSS[a]]<SALARY[BOSS[b]];}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%d%d",&BOSS[i],&SALARY[i]);
	for(int i=1;i<=N;i++)if(BOSS[i]==i){CEO=i;if(SALARY[i]==0)SALARY[i]=N;break;}
	BuildSZ();
	static bool vis[1000001];
	for(int i=1;i<=N;i++)vis[i]=false;
	for(int i=1;i<=N;i++)vis[SALARY[i]]=true;
	vector<int>trees;
	for(int i=1;i<=N;i++)if(i!=CEO&&SALARY[BOSS[i]]!=0&&SALARY[i]==0)trees.push_back(i);
	sort(trees.begin(),trees.end(),CmpBossSalary);
	vector<int>stk;
	for(int i=0,j=1;i<(int)trees.size();)
	{
		const int u=trees[i];
		for(;j<SALARY[BOSS[u]];j++)if(!vis[j])stk.push_back(j);
		int k=i+1,sz=SZ[u];
		for(;k<(int)trees.size()&&BOSS[trees[k]]==BOSS[u];k++)sz+=SZ[trees[k]];
		if((int)stk.size()==sz)
		{
			if(k==i+1)
			{
				SALARY[u]=stk.back(),stk.pop_back();
				for(int cur=u;(int)ET[cur].size()==1;cur=ET[cur][0])
				{
					SALARY[ET[cur][0]]=stk.back(),stk.pop_back();
				}
			}
			stk.clear();
		}
		else break;
		i=k;
	}
	for(int i=1;i<=N;i++)printf("%d\n",SALARY[i]);
	return 0;
}
