#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int ans[1001],p[500];
int sumfactor(int a)
{
	vector<int> factor;
	for(int i=0,j,k;a>1;i++)
	{
		j=1,k=0;
		while(a%p[i]==0)
		{
			a/=p[i];
			k+=j;
			j*=p[i];
		}
		k+=j;
		if(j>1) factor.push_back(k);
	}
	int b=1;
	for(int i=0;i<factor.size();i++)
	{
		b*=factor[i];
	}
	return b;
}
int main()
{
	p[0]=2,p[1]=3;
	for(int i=2,j;;i++)
	{
		p[i]=p[i-1];
		do
		{
			p[i]+=2;
			for(j=0;p[j]*p[j]<=p[i];j++)
			{
				if(p[i]%p[j]==0) break;
			}
		}while(p[i]%p[j]==0);
		if(p[i]>1000) break;
	}
	for(int i=1;i<=1000;i++) ans[i]=-1;
	for(int i=1;i<=1000;i++)
	{
		int j=sumfactor(i);
		if(j<=1000) ans[j]=i;
	}
	int kase=1,S;
	while(scanf("%d",&S)==1&&S)
	{
		printf("Case %d: %d\n",kase++,ans[S]);
	}
	return 0;
}
