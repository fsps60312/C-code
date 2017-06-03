#include<cstdio>
#include<cassert>
using namespace std;
int K,A,B;
int Solve()
{
	if(A<K&&B<K)return -1;
	if(A%K!=0)
	{
		if(B<K)return -1;
	}
	if(B%K!=0)
	{
		if(A<K)return -1;
	}
	return A/K+B/K;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&K,&A,&B)==3)
	{
		printf("%d\n",Solve());
	}
	return 0;
}
