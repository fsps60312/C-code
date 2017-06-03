#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
struct Bit
{
	int S[1000001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i,const int v){while(i<=N)S[i]+=v,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=S[i],i-=(i&(-i));return ans;}
}BIT;
int N,BOSS[1000001],SALARY[1000001];
int SZ[1000001];
vector<int>ET[1000001];
void BuildSZ()
{
	static int deg[1000001];
	for(int i=1;i<=N;i++)deg[i]=SZ[i]=0;
	for(int i=1;i<=N;i++)if(BOSS[i]!=i)deg[BOSS[i]]++,ET[BOSS[i]].push_back(i);
	queue<int>q;
	for(int i=1;i<=N;i++)if(ET[i].empty())SZ[i]++,q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(BOSS[u]==u){assert(q.empty());break;}
		SZ[BOSS[u]]+=SZ[u];
		if(!--deg[BOSS[u]])q.push(BOSS[u]);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%d%d",&BOSS[i],&SALARY[i]);
	for(int i=1;i<=N;i++)if(BOSS[i]==i){if(SALARY[i]==0)SALARY[i]=N;break;}
	BuildSZ();
	BIT.Clear(N);
	set<int>salaries;
	for(int i=1;i<=N;i++)BIT.Add(i,1),salaries.insert(i);
	for(int i=1;i<=N;i++)if(SALARY[i]!=0)BIT.Add(SALARY[i],-1),salaries.erase(SALARY[i]);
	vector<int>roots;
	for(int u=1;u<=N;u++)
	{
		if(SALARY[u]!=0)
		{
			for(int i=0;i<(int)ET[u].size();i++)
			{
				
			}
		}
		if(BOSS[i]!=i&&SALARY[i]==0&&bs!=0)ST.Set(1,1,N,bs,BIT.Query(bs-1)-SZ[i]),id[bs]=i;
	}
	while(ST.MN[1]==0)
	{
		const int bbs=ST.GetLoc(1,1,N);
		const int u=id[bbs];
		if(true)
		{
			set<int>::iterator it=salaries.upper_bound(bbs);it--;
			SALARY[u]=*it;
			salaries.erase(it);
		}
		const int bs=SALARY[u];
		for(int _i=0;_i<(int)ET[u].size();_i++)
		{
			const int i=ET[u][_i];
			ST.Set(1,1,N,bs,BIT.Query(bs-1)-SZ[i]),id[bs]=i;
		}
	}
	assert(ST.MN[1]>0);
	for(int i=1;i<=N;i++)printf("%d\n",SALARY[i]);
	return 0;
}
