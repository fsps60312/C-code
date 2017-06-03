#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,M;
vector<int>ET[1000000];
bool VIS[1000000];
int KASE[1000000];
bool IsEndOfChain(const int u,const int parent,const int banned=-1,const int kase=-1)
{
	if(kase!=-1)
	{
		if(KASE[u]==kase)return false;
		KASE[u]=kase;
	}
	int nxt,cnt=0;
	for(const int v:ET[u])if(v!=parent&&v!=banned)nxt=v,++cnt;
	if(cnt==0)return true;
	else if(cnt==1)return IsEndOfChain(nxt,u,banned,kase);
	else return false;
}
bool IsEndOfChain(int u)
{
	return IsEndOfChain(u,-1);
}
void DfsMarkVIS(const int u,vector<int>&rec)
{
	if(VIS[u])return;
	VIS[u]=true;
	rec.push_back(u);
	for(const int nxt:ET[u])DfsMarkVIS(nxt,rec);
}
bool IsCycle(const vector<int>&s)
{
	for(const int u:s)if(ET[u].size()!=2)return false;
	return true;
}
bool Is3Fork(const vector<int>&s)
{
	for(const int u:s)
	{
		if(ET[u].size()==3)
		{
			for(int i=0;i<3;i++)if(!IsEndOfChain(ET[u][i],u))return false;
			return true;
		}
	}
	return false;
}
bool Is4Fork(const vector<int>&s)
{
	for(const int u:s)
	{
		if(ET[u].size()>3)
		{
			for(const int nxt:ET[u])if(!IsEndOfChain(nxt,u))return false;
			return true;
		}
	}
	return false;
}
bool IsMiddleOfChain(const int u,const int parent,const int kase)
{
	int cnt=0;
	for(const int nxt:ET[u])if(nxt!=parent)++cnt;
	if(cnt>2)return false;
	KASE[u]=kase;
	for(const int nxt:ET[u])if(nxt!=parent&&!IsEndOfChain(nxt,u,parent,kase))return false;
	return true;
}
bool IsCriticalPoint(const int u,const int kase)
{
	for(const int nxt:ET[u])if(KASE[nxt]!=kase&&!IsMiddleOfChain(nxt,u,kase))return false;
	return true;
}
int Solve()
{
	for(int i=0;i<N;i++)VIS[i]=false;
	vector<int>rec;
	for(int i=0;i<N;i++)if(IsEndOfChain(i))DfsMarkVIS(i,rec);
	rec.clear();
	{
		int cnt=0;
		for(int i=0;i<N;i++)if(!VIS[i])DfsMarkVIS(i,rec),++cnt;
		if(cnt==0)return N;
		if(cnt>1)return 0;
		assert(cnt==1);
	}
	if(IsCycle(rec))return (int)rec.size();
	if(Is3Fork(rec))return 4;
	if(Is4Fork(rec))return 1;
	for(const int i:rec)KASE[i]=-1;
	int ans=0;
//	puts("a");
	for(const int u:rec)if(IsCriticalPoint(u,u))++ans;
//	puts("b");
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int a,b;M--;)
		{
			scanf("%d",&a);
			if(a==-1)printf("%d\n",Solve());
			else
			{
				scanf("%d",&b);
				ET[a].push_back(b),ET[b].push_back(a);
			}
		}
	}
	return 0;
}
