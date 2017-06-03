#include<cstdio>
#include<cassert>
using namespace std;
int A[3],B[3];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<3;i++)scanf("%d",&A[i]);
	for(int i=0;i<3;i++)scanf("%d",&B[i]);
	int a=0,b=0;
	for(int i=0;i<3;i++)
	{
		if(A[i]>B[i])++a;
		if(A[i]<B[i])++b;
	}
	printf("%d %d\n",a,b);
	return 0;
}
