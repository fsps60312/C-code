#include<cstdio>
#include<cstdlib>
int tmp[1000],a,b,n,Min,Max,mid;
int main()
{
	n=-1;
	for(int i=1;;i++)
	{
		tmp[++n]=i*i;
		if(tmp[n]>=100000) break;
	}
	while(scanf("%d%d",&a,&b)==2&&a&&b)
	{
		Min=0,Max=n;
		while(Min<Max)
		{
			mid=(Min+Max)/2;
			if(tmp[mid]<a) Min=mid+1;
			else Max=mid;
		}
		//tmp[Max]>=a
		a=Max;
		Min=0,Max=n;
		while(Min<Max)
		{
			mid=(Min+Max)/2;
			if(tmp[mid]<=b) Min=mid+1;
			else Max=mid;
		}
		//tmp[Max]>b
		printf("%d\n",Max-a);
	}
	return 0;
}
