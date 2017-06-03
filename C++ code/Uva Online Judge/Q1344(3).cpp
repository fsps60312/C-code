#include<bits/stdc++.h>
using namespace std;
int N,A[1000],B[1000];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<N;i++)scanf("%d",&B[i]);
		sort(A,A+N),sort(B,B+N);
		int ans=0,a1=0,b1=0,a2=N-1,b2=N-1;
		for(int i=0;i<N;i++)
		{
			if(A[a1]>B[b1])a1++,b1++,ans++;
			else if(A[a1]<B[b1])a1++,b2--,ans--;
			else
			{
				if(A[a2]>B[b2])a2--,b2--,ans++;
				else if(A[a2]<B[b2])a1++,b2--,ans--;
				else
				{
					if(A[a1]<B[b2])ans--;
					a1++,b2--;
				}
			}
		}
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
