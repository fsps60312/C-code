#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,A[10000],B[10000];
int Solve()
{
	int ans=0;
	for(int i=0,j=0;i<N;i++)
	{
		while(j<M&&B[j]<A[i])j++;
		if(j==M)return -1;
		ans+=B[j++];
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<M;i++)scanf("%d",&B[i]);
		sort(A,A+N),sort(B,B+M);
		printf("%d\n",Solve());
	}
	return 0;
}
