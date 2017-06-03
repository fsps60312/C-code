#include<cstdio>
int T,N;
int C(const int a,const int b)
{
	if(a<b)return 0;
	int ans=1;
	for(int i=b+1;i<=a;i++)ans*=i,ans/=i-b;
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		bool found=false;
		for(int a=2;C(a,3)<=N&&!found;a++)
		{
			N-=C(a,3);
			for(int b=1;b<a&&C(b,2)<=N&&!found;b++)
			{
				N-=C(b,2);
				if(N<b)
				{
					printf("%d%d%d\n",a,b,N);
					found=true;
				}
				N+=C(b,2);
			}
			N+=C(a,3);
		}
	}
	return 0;
}
