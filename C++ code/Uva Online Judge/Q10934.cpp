#include<cstdio>
typedef long long LL;
int k;
LL n;
int main()
{
	freopen("in.txt","r",stdin); 
	while(scanf("%d%d",&k,&n)==2&&k)
	{
		for(int i=1;i<k;i++)
		{
			n=(n>>1);//+(n&1);
		}
		int ans=n+(k-1);
		printf("%d\n",ans);
	}
}
