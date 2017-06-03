#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<queue>
using namespace std;
int N,FA[100000],A[100000];
set<int>ET[100000];
bool Solve()
{
	queue<int>q;
	for(int i=0;i<N;i++)if(ET[i].empty())
	{
		if(A[i]==1)return true;
		q.push(i);
	}
	int ans=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(A[FA[u]]==1&&(int)ET[FA[u]].size()==1)continue;
		ET[FA[u]].erase(u);
		ans++;
		if(ET[FA[u]].empty())q.push(FA[u]);
	}
	if(ans%2==1)return true;
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1;i<N;i++)scanf("%d",&FA[i]),ET[FA[i]].insert(i);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		puts(Solve()?"689":"bBg");
	}
	return 0;
}
