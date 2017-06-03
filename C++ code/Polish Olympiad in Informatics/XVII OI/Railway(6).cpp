#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
int N,A[100000];
int ANS[100000];
vector<int>ET[100000];
bool Dfs(const int u,const int color)
{
	if(ANS[u]!=-1)return ANS[u]==color;
	ANS[u]=color;
	for(int i=0;i<(int)ET[u].size();i++)if(!Dfs(ET[u][i],color^1))return false;
	return true;
}
void Maintain(map<int,int>&inc,const pair<int,int>&p)
{
	map<int,int>::iterator it=inc.lower_bound(p.first);
	if(it!=inc.begin())
	{
		--it;
		if(it->second>=p.second)return;
	}
	it=inc.upper_bound(p.first);
	for(;it!=inc.end()&&p.second>=it->second;)inc.erase(it++);
	inc[p.first]=p.second;
}
bool Solve()
{
	static int mn[100000];
	mn[N-1]=A[N-1];
	for(int i=N-2;i>=0;i--)mn[i]=min(mn[i+1],A[i]);
	for(int i=0;i<N;i++)ET[i].clear();
	map<int,int>vals;
	map<int,int>inc;
	vals[A[0]]=0;
	for(int i=1;;i++)
	{
		map<int,int>::iterator it=vals.lower_bound(A[i]);
		if(it!=vals.begin())
		{
			const pair<int,int>&p=make_pair(A[i],(--it)->first);
			Maintain(inc,p);
			++it;
			while(it!=vals.begin())
			{
				--it;
				if(it->first<mn[i+1]||(A[i-1]<A[i]&&it->first<A[i-1]))break;
				ET[i].push_back(it->second);
				ET[it->second].push_back(i);
			}
		}
		if(i+2>=N)break;
		it=inc.lower_bound(A[i+1]);
		if(it!=inc.begin())
		{
			--it;
			if(mn[i+2]<it->second)return false;
		}
		vals[A[i]]=i;
	}
//	assert(0);
	for(int i=0;i<N;i++)ANS[i]=-1;
	for(int i=0;i<N;i++)if(ANS[i]==-1&&!Dfs(i,0))return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]),--A[i];
		if(!Solve())puts("NIE");
		else
		{
			puts("TAK");
			for(int i=0;i<N;i++)
			{
				if(i)putchar(' ');
				printf("%d",ANS[i]+1);
			}
			puts("");
		}
	}
	return 0;
}
