#include<cstdio>
#include<cassert>
#include<algorithm>
#include<set>
#include<functional>
using namespace std;
const int INF=2147483647;
int N,S[1000000],CNT[1000000],SUB[1000000];
bool Solve()
{
	if(N==1)return S[0]==0;
	sort(S,S+N,greater<int>());
	if(S[0]>=N||S[N-1]<=0)return false;
	multiset<int>L;
	for(int h=0,i=N-1;i>=0;i--)
	{
		for(;h<S[i];h++)L.insert(i);
	}
	for(int i=0;i<N;i++)SUB[i]=0;
	int sub=0;
	for(int i=0;i<N;sub-=SUB[i],i++)
	{
//		for(int v:L)printf(" %d",v);puts("");
		if(S[i]==sub)continue;
		const int goal=i+(S[i]-sub);
//		printf("i=%d,o=%d,s=%d,goal=%d\n",i,S[i],S[i]-sub,goal);
		assert(S[i]>=sub);
		multiset<int>::iterator it=L.lower_bound(goal),il;
		if(it==L.end())return false;
		if(*it==goal)++SUB[*it],L.erase(it),++sub;
		else
		{
			int gap=goal-i,add;
			if(it!=L.begin())
			{
				il=it;--il;
				if(*il>=i)gap=goal-*il,++sub;
				++SUB[*il],L.erase(il);
			}
			add=*it-gap;
//			printf("add=%d\n",add);
			assert(add>=i);
			++SUB[*it],L.erase(it);
			--SUB[add],L.insert(add);
		}
	}
	return true;
}
main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N!=0)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		puts(Solve()?"Possible":"Not possible");
	}
	return 0;
}
