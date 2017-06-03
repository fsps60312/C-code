#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,S[1000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		int ans=0,sum=0;
		for(int i=0;i<N;i++)ans+=(sum+=S[i]),sum+=S[i];
		printf("%d\n",ans);
	}
	return 0;
}
