#include<cstdio>
int N,A[500000],TAG[499999];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&A[i]);
	int ans=0;
	for(int i=0,l,r;i+1<N;i++)
	{
		for(r=i;r+1<N&&A[r]!=A[r+1];r++);
		l=i;
		int i1=l+1,i2=r-1;
		int cnt=0;
		while(i1<=i2)
		{
			A[i1++]=A[l],A[i2--]=A[r];
			cnt++;
		}
		if(cnt>ans)ans=cnt;
	}
	printf("%d\n",ans);
	for(int i=0;i<N;i++)
	{
		if(i)printf(" ");
		printf("%d",A[i]);
	}
	puts("");
	return 0;
}
