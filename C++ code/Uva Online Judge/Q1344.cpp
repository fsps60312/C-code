#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,A[1000],B[1000];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<N;i++)scanf("%d",&B[i]);
		sort(A,A+N),sort(B,B+N);
		int ans=-INF;
		for(int i=0,ta=0;i<N;i++,ta=-i)
		{
			for(int j=0;i+j<N;j++)
			{
				if(A[i+j]>B[j])ta++;
				else if(A[i+j]<B[j])ta--;
			}
//			printf("ta[%d]=%d\n",i,ta);
			ans=max(ans,ta);
		}
//		for(int i=N-1,j=N-1;i>=0;i--)
//		{
//			while(j>=0&&B[j]>=A[i])j--;
//			if(j==-1)break;
//			ans++;
//			j--;
//		}
		printf("%d\n",ans*200);
	}
	return 0;
}
/*
3
92 83 71
95 87 74
2
20 20
20 20
2
20 19
22 18
0
*/
