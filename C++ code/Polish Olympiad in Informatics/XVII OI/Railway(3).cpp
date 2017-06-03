#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
int N,A[100000];
int ANS[100000];
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
	set<int>vals;
	map<int,int>inc;
	vals.insert(A[0]);
	for(int i=1;i+2<N;i++)
	{
		set<int>::iterator it=vals.lower_bound(A[i]);
		if(it!=vals.begin())
		{
			const pair<int,int>&p=make_pair(A[i],*--it);
			Maintain(inc,p);
		}
		map<int,int>::iterator iu=inc.lower_bound(A[i+1]);
		if(iu!=inc.begin())
		{
			--iu;
			if(mn[i+2]<iu->second)return false;
		}
		vals.insert(A[i]);
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]),--A[i];
		for(int i=0;i<N;i++)ANS[i]=-1;
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
