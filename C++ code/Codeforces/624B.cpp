#include<cstdio>
#include<algorithm>
using namespace std;
int N,S[26];
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		for(int i=N-2;i>=0;i--)if(S[i]>S[i+1]-1)S[i]=S[i+1]-1;
		long long ans=0;
		for(int i=N-1;i>=0&&S[i]>0;i--)ans+=S[i];
		printf("%lld\n",ans);
	}
	return 0;
}
