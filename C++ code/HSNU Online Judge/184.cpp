#include<cstdio>
#include<algorithm>
using namespace std;
int N,M,S;
int A[100000],B[100000];
int main()
{
	scanf("%d%d%d",&N,&M,&S);
	for(int i=0;i<N;i++)scanf("%d",&A[i]);
	for(int i=0;i<M;i++)scanf("%d",&B[i]);
	sort(A,A+N),sort(B,B+M);
	long long ans=0LL;
	for(int i=N-1,j=0;i>=0;i--)
	{
		while(j<M&&B[j]+A[i]<=S)j++;
		ans+=j;
	}
	printf("%lld\n",ans);
	return 0;
}
