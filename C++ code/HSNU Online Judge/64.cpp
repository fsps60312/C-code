#include<cstdio>
#include<algorithm>
using namespace std;
int N,S[30000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	sort(S,S+N);
	int ans=min(2,N);
	for(int i=0,r=2;i+2<N;i++)
	{
		while(r+1<N&&S[r+1]<S[i]+S[i+1])r++;
		ans=max(ans,r-i+1);
	}
	printf("%d\n",ans);
	return 0;
}
