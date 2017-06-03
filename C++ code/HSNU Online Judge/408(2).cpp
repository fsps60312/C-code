#include<bits/stdc++.h>
using namespace std;
int N,M;
int VIS[10000];
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<N;i++)VIS[i]=-1;
		for(int i=0;i<M;i++)
		{
			static int a,b;
			scanf("%d%d",&b,&a);
			if(a<=b)continue;
			VIS[b]=max(VIS[b],a);
		}
		int ans=N+1;
		for(int i=0,nx=-1;i<N;i++)
		{
			nx=max(nx,VIS[i]);
			if(i==nx)nx=-1;
			if(nx!=-1)ans+=2;
		}
		printf("%d\n",ans);
		break;
	}
	return 0;
}
