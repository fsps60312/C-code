#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int N,A[10000],B[10000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<N;i++)scanf("%d",&B[i]);
		sort(A,A+N),sort(B,B+N);
		int ans=0;
		for(int i=0,j=0;i<N;i++)if(B[i]>A[j])
		{
			ans++,j++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
