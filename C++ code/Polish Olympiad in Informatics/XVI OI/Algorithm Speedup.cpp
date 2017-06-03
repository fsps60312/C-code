#include<cstdio>
#include<cassert>
using namespace std;
int N,M,A[100000],B[100000];
int Solve(const int l1,const int r1,const int l2,const int r2)
{
//	printf("%d %d %d %d\n",l1,r1,l2,r2);
	int *CA=new int[100],*CB=new int[100];
	for(int i=0;i<100;i++)CA[i]=CB[i]=0;
	for(int i=l1;i<=r1;i++)++CA[A[i]];
	for(int i=l2;i<=r2;i++)++CB[B[i]];
	for(int i=0;i<100;i++)if((CA[i]>0)!=(CB[i]>0))return 0;
	int cnt=0;
	for(int i=0;i<100;i++)if(CA[i]>0)++cnt;
	if(cnt==1)return 1;
//	printf("%d %d %d %d\n",l1,r1,l2,r2);
//	puts("a");
	int i1=l1,i2=l2;
	for(;;i1++)if(!--CA[A[i1]])break;
	for(;;i2++)if(!--CB[B[i2]])break;
//	puts("b");
	int ans=Solve(i1+1,r1,i2+1,r2);
//	printf("%d %d %d %d\n",l1,r1,l2,r2);
//	puts("c");
	for(;i1>=l1;i1--)++CA[A[i1]];
	for(;i2>=l2;i2--)++CB[B[i2]];
	i1=r1,i2=r2;
	for(;;i1--)if(!--CA[A[i1]])break;
	for(;;i2--)if(!--CB[B[i2]])break;
//	puts("d");
	ans&=Solve(l1,i1-1,l2,i2-1);
	delete[]CA;
	delete[]CB;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("prz1.in","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",&A[i]),--A[i];
		for(int i=0;i<M;i++)scanf("%d",&B[i]),--B[i];
		printf("%d\n",Solve(0,N-1,0,M-1));
	}
	return 0;
}
