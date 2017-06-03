#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N;
char A[1001],B[1001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%s%s",A,B);
		int ans=0;
		for(int i=0;i<N;i++)ans+=min((A[i]-B[i]+10)%10,(B[i]-A[i]+10)%10);
		printf("%d\n",ans);
	}
	return 0;
}
