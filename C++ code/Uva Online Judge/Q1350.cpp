#include<cstdio>
int T,K,CNT[38],SUM[38];
int main()
{
	CNT[0]=1,CNT[1]=1;
	SUM[0]=1,SUM[1]=2;
	for(int i=2;i<=37;i++)
	{
		int &c=CNT[i]=SUM[i-2];
		SUM[i]=SUM[i-1]+c;
//		printf("%d:%d\n",i,SUM[i]);
	}
	scanf("%d",&T);
	int l,r,mid,idx;
	while(T--)
	{
		scanf("%d",&K);
		idx=38;
		while(K)
		{
			l=0,r=idx-1;
			while(l<r)
			{
				mid=(l+r+1)/2;
				if(SUM[mid]>K)r=mid-1;
				else l=mid;
			}
			K-=SUM[l];
			if(idx<38)for(int i=idx-r-1;i>0;i--)printf("0");
			printf("1");
			idx=r;
		}
		for(int i=0;i<idx;i++)printf("0");
		printf("\n");
	}
	return 0;
}
