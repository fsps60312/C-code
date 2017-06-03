#include<cstdio>
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&N);
		int ans=1,lines=0;
		for(int i=0,a;i<N;i++)
		{
			scanf("%d",&a);
			for(int j=0;j<a+1;j++)
			{
				ans+=lines;
				if(j>=2)ans+=j-1;
			}
			ans++;
			lines+=a+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
