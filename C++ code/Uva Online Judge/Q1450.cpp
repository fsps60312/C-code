#include<cstdio>
int T,N,E[5000],W[5000],SUM;
bool fitans(int mx)
{
	int a=mx,b=SUM-mx;
	for(int i=N-1;i>=0;i--)
	{
		int &c=(a<b?a:b);
		c++;
		if(c>mx)return false;
		a-=E[i];
		b-=W[i];
	}
	return true;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		SUM=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&E[i],&W[i]);
			SUM+=E[i]+W[i];
		}
		SUM-=N;
		int l=(SUM+1)/2,r=SUM+1;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(fitans(mid))r=mid;
			else l=mid+1;
		}
		printf("%d\n",l-1);
	}
	return 0;
}
