#include<bits/stdc++.h>
int T,N;
int main()
{
//	freopen("in.txt","r",stdin);
	//while(
	scanf("%d",&T);//==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			int f=0;
			for(int i=0,a=0,b;i<N;i++)
			{
				scanf("%d",&b);
//				assert(b&&b>=a);
				if(b>a&&!((N-1-i)&1))f^=b-a;
				a=b;
			}
			puts(f?"TAK":"NIE");
		}
	}
	return 0;
}
