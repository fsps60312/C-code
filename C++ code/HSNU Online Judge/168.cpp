#include<cstdio>
int N;
int main()
{
	scanf("%d",&N);
	int ans=0;
	for(int i=0,a,b;i<N;i++)scanf("%d%d",&a,&b),ans+=a*b;
	printf("%d\n",ans);
	return 0;
}
