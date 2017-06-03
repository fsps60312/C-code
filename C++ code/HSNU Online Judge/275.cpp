#include<cstdio>
#include<cmath>
#include<cassert>
typedef long long LL;
LL N,K;
int ANS[200000];
int main()
{
//	freopen("in.txt","r",stdin);
	{int x1,x2;scanf("%lld%lld%d%d",&N,&K,&x1,&x2);}
	LL v=sqrt(K*2LL);
	if((v+1LL)*v/2LL<=K)v++;
	assert(v*(v-1LL)/2LL<=K&&(v+1LL)*v/2LL>K);
	const LL remain=K-v*(v-1LL)/2LL;
	if(remain==0LL)
	{
		for(int i=0;i<v;i++)ANS[i]=v-1-i;
		for(int i=v;i<N;i++)ANS[i]=i;
	}
	else
	{
		ANS[0]=remain;
		for(int i=1,j=v;i<=v;i++,j--)
		{
			if(j==remain)j--;
			ANS[i]=j;
		}
		for(int i=v+1;i<N;i++)ANS[i]=i;
	}
	for(int i=0;i<N;i++)
	{
		if(i)putchar(' ');
		printf("%d",ANS[i]+1);
	}
	puts("");
	return 0;
}
