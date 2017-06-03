#include<cstdio>
#include<cstdlib>
struct pairtype
{
	int n;
	int a;
	int b;
};
int n,tmp1[10000],tmp2[10000];
pairtype S[10000];
int main()
{
	while(scanf("%d",&n)==1)
	{
		for(int i=0;i<n;i++)
		{
			scanf("%d",&S[i].n);
			tmp1[i]=2147483647;
			tmp2[i]=2147483647;
		}
		int edge=0;
		for(int i=0;i<n;i++)
		{
			int Min=0,Max=edge,mid;
			while(Min<Max)
			{
				mid=(Min+Max)/2; 
				if(tmp1[mid]<S[i].n) Min=mid+1;
				else Max=mid;
			}
			tmp1[Max]=S[i].n;
			if(Max==edge) edge++;
			S[i].a=edge;
		}
		edge=0;
		for(int i=n-1;i>=0;i--)
		{
			int Min=0,Max=edge,mid;
			while(Min<Max)
			{
				mid=(Min+Max)/2; 
				if(tmp2[mid]<S[i].n) Min=mid+1;
				else Max=mid;
			}
			tmp2[Max]=S[i].n;
			if(Max==edge) edge++;
			S[i].b=edge;
		}
		int ans=0;
		for(int i=0;i<n;i++)
		{
			int j;
			if(S[i].a<S[i].b) j=S[i].a;
			else j=S[i].b;
			if(j>ans) ans=j;
		}
		printf("%d\n",ans*2-1);
	}
	return 0;
} 
