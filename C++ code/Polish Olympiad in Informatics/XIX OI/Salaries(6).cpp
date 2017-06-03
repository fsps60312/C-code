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
	for(int i=1;i<=N;i++)deg[i]=0,SZ[i]=(SALARY[i]==0?1:0),ET[i].clear();
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
int FindZero(const int u)
{
	int ans=-2;
	for(int i=0;i<(int)ET[u].size();i++)if(SALARY[ET[u][i]]==0)
	{
		if(ans==-2)ans=ET[u][i];
		else ans=-1;
	}
	return ans;
}
bool CmpSalary(const int a,const int b){return SALARY[a]<SALARY[b];}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("pen2b.in","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%d%d",&BOSS[i],&SALARY[i]);
	for(int i=1;i<=N;i++)if(BOSS[i]==i){if(SALARY[i]==0)SALARY[i]=N;break;}
	BuildSZ();
	static bool vis[1000001];
	for(int i=1;i<=N;i++)vis[i]=false;
	for(int i=1;i<=N;i++)vis[SALARY[i]]=true;
	vector<int>trees;
	for(int i=1;i<=N;i++)if(SALARY[i]!=0)trees.push_back(i);
	sort(trees.begin(),trees.end(),CmpSalary);
	vector<int>stk;
	for(int i=0,j=1,bound=0;i<(int)trees.size();i++)
	{
		const int u=trees[i];
		for(;j<SALARY[u];j++)if(!vis[j])stk.push_back(j);
		printf("SZ[%d]=%d,stk.size=%d\n",u,SZ[u],(int)stk.size());
		if((int)stk.size()==SZ[u])
		{
			printf("u=%d\n",u);
			for(int cur=u,nxt;(nxt=FindZero(cur))>=1&&stk.back()>=bound;cur=nxt)
			{
				printf("nxt=%d,%d,%d,%d\n",nxt,(int)ET[nxt].size(),stk.back(),bound);
				SALARY[nxt]=stk.back(),stk.pop_back();
			}
			stk.clear();
			for(int cur=u;BOSS[cur]!=cur;cur=BOSS[cur])SZ[BOSS[cur]]-=SZ[u];
		}
		else if(SZ[u]==0)continue;
		else bound=SALARY[u];
	}
	for(int i=1;i<=N;i++)printf("%d\n",SALARY[i]);
	return 0;
}
