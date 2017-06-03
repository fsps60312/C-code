#include<cstdio>
#include<cassert>
#include<queue>
#include<utility>
using namespace std;
int N,K,DAD[1000000],DEG[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<N;i++)DEG[i]=0;
		for(int i=1;i<N;i++)scanf("%d",&DAD[i]),++DEG[DAD[i]];
		queue<pair<int,int> >q;
		for(int i=0;i<N;i++)if(DEG[i]==0)q.push(make_pair(i,1));//vertex number, length
		int ans=N-1,leafs=(int)q.size();
		while(leafs>K)
		{
			assert(!q.empty());
			const auto p=q.front();q.pop();
			if(--DEG[DAD[p.first]])ans-=p.second,--leafs;
			else if(DAD[p.first]!=0)q.push(make_pair(DAD[p.first],p.second+1));
			else ans-=p.second,--leafs;
		}
		printf("%d\n",ans);
	}
	return 0;
}
