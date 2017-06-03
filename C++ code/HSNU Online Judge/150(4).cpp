#include<cstdio>
#include<cassert>
#include<map>
#include<set>
#include<algorithm>
#include<stack>
using namespace std;
const int INF=2147483647;
int N,S[100001],LOC[100000],COLOR[100000],MN[100001];
bool HasSolution()
{
	MN[N]=S[N]=INF;
	for(int i=N-1;i>=0;i--)MN[i]=min(MN[i+1],S[i]);
	int *up_mnidx=new int[100000];
	if(true)
	{
		stack<int>stk;stk.push(N);
		for(int i=N-1;i>=0;i--)
		{
			while(S[i]>S[stk.top()])stk.pop();
			up_mnidx[i]=stk.top();
			stk.push(i);
		}
	}
	set<int>pre;
	for(int i=0;i<N;i++)
	{
		pre.insert(S[i]);
		auto it=pre.lower_bound(S[i]);
		if(it==pre.begin())continue;
		if(up_mnidx[i]<N&&MN[up_mnidx[i]+1]<*(--it))return false;
	}
	pre.clear();
	set<int>().swap(pre);
	delete[] up_mnidx;
	return true;
}
vector<int>ET[100000];
void AddEdge(const int a,const int b){ET[a].push_back(b),ET[b].push_back(a);}
void BuildET()
{
	for(int i=0;i<N;i++)ET[i].clear(),vector<int>().swap(ET[i]);
	set<int>pre;
	for(int i=0;i<N;i++)
	{
		pre.insert(S[i]);
		auto it=pre.lower_bound(S[i]);
		while(it!=pre.begin()&&*(--it)>MN[i+1])
		{
			AddEdge(LOC[*it],i);
			if(S[i-1]>S[i])break;
		}
	}
	pre.clear();
	set<int>().swap(pre);
}
bool Dfs(const int u,const int c)
{
	if(COLOR[u]!=-1)return COLOR[u]==c;
	COLOR[u]=c;
	for(const int nxt:ET[u])if(!Dfs(nxt,c^1))return false;
	return true;
}
bool Solve()
{
	if(!HasSolution())return false;
	BuildET();
	for(int i=0;i<N;i++)COLOR[i]=-1;
	for(int i=0;i<N;i++)if(COLOR[i]==-1)if(!Dfs(i,0))return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]),LOC[--S[i]]=i;
	if(Solve())
	{
		puts("TAK");
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",COLOR[i]+1);
		}
		puts("");
	}
	else puts("NIE");
	return 0;
}
