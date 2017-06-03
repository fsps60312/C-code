#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int N,M,S[100000];
int Solve()
{
	priority_queue<int,vector<int>,greater<int> >pq;
	int tick=0;
	for(int i=0;i<N;i++)
	{
		if((int)pq.size()==M)
		{
			tick=pq.top();pq.pop();
		}
		pq.push(tick+S[i]);
	}
	while(!pq.empty())tick=pq.top(),pq.pop();
	return tick;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		printf("%d\n",Solve());
	}
	return 0;
}
