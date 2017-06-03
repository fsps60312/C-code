#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,S[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	sort(S,S+N);
	int ans=0;
	LL now=0LL;
	for(int i=0;i<N;i++)if(now<=S[i])
	{
		now+=S[i];
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
