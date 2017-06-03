#include<cstdio>
int N,PN,P[1000];
int main()
{
	P[0]=2,P[1]=3;PN=2;
	for(int j;;PN++)
	{
		P[PN]=P[PN-1];
		do
		{
			P[PN]+=2;
			for(j=0;P[j]*P[j]<=P[PN]&&P[PN]%P[j];j++);
		}while(P[PN]%P[j]==0);
		if(P[PN]>=10000)break;
	}
//	for(int i=0;i<=100;i++)printf("%d\n",P[i]);
	while(scanf("%d",&N)==1)
	{
		int l=0,r=PN,mid;
		while(l<r)
		{
			mid=(l+r+1)>>1;
			if(P[mid]>N)r=mid-1;
			else l=mid;
		}
		l=0,mid=0;
		for(;r>=l;r--,mid++)
		{
			if(P[l]*P[r]<=N)l++;
		}
		printf("%d\n",mid);
	}
	return 0;
}
