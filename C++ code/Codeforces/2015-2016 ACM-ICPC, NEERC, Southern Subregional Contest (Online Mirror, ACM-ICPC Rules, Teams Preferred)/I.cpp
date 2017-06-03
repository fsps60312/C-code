#include<cstdio>
#include<algorithm>
int N,K,CNT[101];
int main()
{
	scanf("%d%d",&N,&K);
	for(int i=0;i<K;i++)CNT[i]=0;
	for(int i=0,v;i<N;i++)
	{
		scanf("%d",&v);
		CNT[--v]++;
	}
	int ans=0;
	for(int i=0;i<K;i++)ans+=abs(CNT[i]-N/K);
	printf("%d\n",ans/2);
	return 0;
}
