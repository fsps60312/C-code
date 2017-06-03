#include<cstdio>
int T,N,A[47];
int getSG(int v)
{
//	if(v==1)return 0;
	return v-1;
}
bool solve()
{
	int ans=0;
	for(int i=0;i<N;i++)ans^=getSG(A[i]);
	return ans>0;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		printf(solve()?"John\n":"Brother\n");
	}
	return 0;
}
