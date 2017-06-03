#include<cstdio>
#include<cassert>
#include<algorithm>
#include<utility>
using namespace std;
#define int long long
int N;
pair<int,int>S[100];
bool Solve()
{
	int t=0;
	for(int i=0;i<N;i++)
	{
		t+=S[i].first;
		if(t>S[i].second)return false;
	}
	return true;
}
main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%lld",&testcount);
	while(testcount--)
	{
		scanf("%lld",&N);
		for(int i=0;i<N;i++)scanf("%lld",&S[i].first);
		for(int i=0;i<N;i++)scanf("%lld",&S[i].second);
		sort(S,S+N,[](pair<int,int>a,pair<int,int>b)->bool{return a.second-a.first<b.second-b.first;});
		puts(Solve()?"Yes":"No");
	}
	return 0;
}
