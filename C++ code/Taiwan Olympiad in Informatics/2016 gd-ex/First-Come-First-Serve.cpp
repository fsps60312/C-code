#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int N,D,S[100000];
int Solve(const int M)
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
		scanf("%d%d",&N,&D);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		int l=1,r=N+1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Solve(mid)<=D)r=mid;
			else l=mid+1;
		}
		if(r==N+1)puts("-1");
		else printf("%d\n",r);
	}
	return 0;
}
