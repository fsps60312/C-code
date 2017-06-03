#include<cstdio>
#include<cassert>
#include<algorithm>
#include<queue>
#include<utility>
#include<set>
using namespace std;
const int INF=2147483647;
int N,Z[100000];
char S[100001];
multiset<int>GAP,LOC;
void Insert(const int loc)
{
	auto it=LOC.upper_bound(loc);
	assert(it!=LOC.end()&&it!=LOC.begin());
	const int r=*it,l=*--it;
	it=GAP.find(r-l);
	assert(it!=GAP.end());
	GAP.erase(it);
	GAP.insert(r-loc),GAP.insert(loc-l);
	LOC.insert(loc);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%s",&N,S);
		Z[0]=0;
		for(int i=1,mx=0;i<N;i++)
		{
			if(mx+Z[mx]>=i)Z[i]=min(mx+Z[mx]-i,Z[i-mx]);
			while(S[i+Z[i]]==S[Z[i]])Z[i]++;
			if(i+Z[i]>=mx+Z[mx])mx=i;
		}
		LOC.clear(),GAP.clear();
		LOC.insert(0),LOC.insert(N),GAP.insert(N);
		priority_queue<pair<int,int> >pq;
		int ans=N;
		for(int i=1;i<N;i++)pq.push(make_pair(Z[i],i));
		while(!pq.empty())
		{
			const auto p=pq.top();pq.pop();
			Insert(p.second);
			auto it=GAP.end();it--;
			if((*it)<=p.first)ans=p.first;
		}
		printf("%d\n",ans);
	}
	return 0;
}
