#include<cstdio>
int N,A[100000],P[100000];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d%d",&A[i],&P[i]);
	int mn=2147483647;
	int ans=0;
	for(int i=0;i<N;i++)
	{
		if(P[i]<mn)mn=P[i];
		ans+=mn*A[i];
	}
	printf("%d\n",ans);
	return 0;
}
/*
3
1 3
2 2
3 1
*/ 
