#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M,Q;
vector<int>LOC[1000001];
bool Solve()
{
	scanf("%d",&M);
	static int s[1000000];
	for(int i=0;i<M;i++)scanf("%d",&s[i]);
	for(int i=0,cur=-1;i<M;i++)
	{
		const vector<int>&l=LOC[s[i]];
		const int j=(int)(upper_bound(l.begin(),l.end(),cur)-l.begin());
		if(j==(int)l.size())return false;
		cur=l[j];
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=1000000;i++)LOC[i].clear();
		for(int i=0,v;i<N;i++)scanf("%d",&v),LOC[v].push_back(i);
		scanf("%d",&Q);
		while(Q--)
		{
			puts(Solve()?"YES":"NO");
		}
	}
	return 0;
}
