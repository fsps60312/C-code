#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,S[100000];
int Solve()
{
	int ans=1;
	for(int i=0;i<N;i++)
	{
		if(S[i]>=ans)++ans;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		printf("%d\n",Solve());
	}
	return 0;
}
