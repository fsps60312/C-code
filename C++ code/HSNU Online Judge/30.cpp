#include<cstdio>
int N,S[100000],DP[100000],ANS;
int main()
{
	scanf("%d",&N);
	static int v;scanf("%d",&v);
	DP[0]=v;
	ANS=1;
	for(int i=1,l,r,mid;i<N;i++)
	{
		scanf("%d",&v);
		l=0,r=ANS;
		while(l<r)
		{
			mid=(l+r)>>1;
			if(v>DP[mid])l=mid+1;
			else r=mid;
		}
		if(l==ANS)DP[ANS++]=v;
		else if(v<DP[l])DP[l]=v;
	}
	printf("%d\n",ANS);
	return 0;
}
