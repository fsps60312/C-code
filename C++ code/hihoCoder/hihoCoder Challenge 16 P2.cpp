#include<cstdio>
#include<cassert>
using namespace std;
int N,S[2000],SUM,SEG[2001];
void Cut(const int n)
{
	SEG[n]=0;
	if(SUM%n!=0)return;
	int sum=0;
	for(int i=0;i<N;i++)
	{
		sum+=S[i];
		if(sum%n==0)SEG[n]++;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	SUM=0;
	for(int i=0;i<N;i++)
	{
		scanf("%d",&S[i]);
		SUM+=S[i];
	}
	for(int i=1;i<=N;i++)
	{
		Cut(i);
//		printf("SEG[%d]=%d\n",i,SEG[i]);
	}
	printf("%d\n",SUM);
	for(int n=2;n<=N;n++)
	{
		bool found=false;
		for(int i=N;i>=1;i--)if(SEG[i]>=n){printf("%d\n",i);found=true;break;}
		assert(found);
	}
//	puts("");
	return 0;
}
