#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
int N,BOSS[1000001],SALARY[1000001];
vector<int>ET[1000001];
int SZ[1000001];
int GetSize(const int u)
{
	int &ans=SZ[u];
	if(ans!=-1)return ans;
	ans=1;
	for(int i=0;i<(int)ET[u].size();i++)ans+=GetSize(ET[u][i]);
	return ans;
}
bool CmpSalary(const int a,const int b){return SALARY[a]<SALARY[b];}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("pen3a.in","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d",&BOSS[i],&SALARY[i]);
		if(BOSS[i]==i&&SALARY[i]==0)SALARY[i]=N;
	}
	for(int i=1;i<=N;i++)ET[i].clear(),SZ[i]=-1;
	for(int i=1;i<=N;i++)if(SALARY[i]==0)ET[BOSS[i]].push_back(i);
	vector<int>trees;
	for(int i=1;i<=N;i++)if(SALARY[i]!=0&&GetSize(i)>1)trees.push_back(i);
	sort(trees.begin(),trees.end(),CmpSalary);
	bool *vis=new bool[N+1];
	for(int i=1;i<=N;i++)vis[i]=false;
	for(int i=1;i<=N;i++)vis[SALARY[i]]=true;
	vector<int>stk;
	for(int i=0,bound=0,j=1,sz=0;i<(int)trees.size();i++)
	{
		const int u=trees[i];
		for(;j<SALARY[u];j++)if(!vis[j])stk.push_back(j),sz++;
		if(GetSize(u)-1==sz)
		{
			for(int cur=u;(int)ET[cur].size()==1&&stk.back()>bound;cur=ET[cur][0])
			{
				SALARY[ET[cur][0]]=stk.back(),stk.pop_back();
			}
		}
		sz-=GetSize(u)-1;
		bound=SALARY[u];
	}
	delete[]vis;
	for(int i=1;i<=N;i++)printf("%d\n",SALARY[i]);
	return 0;
}
