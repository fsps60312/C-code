#include<cstdio>
#include<cassert>
#include<deque>
using namespace std;
//const int INF=2147483647;
int N,S[100001];
deque<int>A;
bool GetFront(const int goal)
{
	assert(!A.empty());
	if(A.front()==goal)return true;
	if(A.front()>goal)
	{
		while(A.front()>goal)
		{
			if(A.front()<=1)return false;
			const int v=A.front();A.pop_front();
			A.push_front(v-2);
			A.push_front(v-1);
		}
		assert(A.front()==goal);
		return true;
	}
	else
	{
		while(A.front()<goal)
		{
			const int v=A.front();A.pop_front();
			if(!GetFront(v-1))return false;
			A.pop_front();
			A.push_front(v+1);
		}
		assert(A.front()==goal);
		return true;
	}
}
bool Solve()
{
	A.clear();
	A.push_back(10);
	for(int i=0;i<N;i++)
	{
		if(!GetFront(S[i]))return false;
		A.pop_front();
	}
//	for(int i=0;i<(int)A.size();i++)printf(" %d",A[i]);puts("");
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("slw2ocen.in","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		if(true)
		{
			int v,i=0;scanf("%d",&v);
			if(v==0)S[i]=1,i++,N++;
			S[i++]=v;
			for(;i<N;i++)scanf("%d",&S[i]);
		}
//		printf("S:");for(int i=0;i<N;i++)printf(" %d",S[i]);puts("");
		const bool ans=Solve();
		if(!ans)puts("NIE");
		else puts("TAK");//printf("%d\n",ans);
	}
	return 0;
}
/*
1
3
5 3 3
*/
