#include<bits/stdc++.h>
using namespace std;
int N,M;
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		int l=N+2,r=-1;
		for(int i=0;i<M;i++)
		{
			static int a,b;
			scanf("%d%d",&b,&a);
			if(a<=b)continue;
			r=max(r,a),l=min(l,b);
		}
		int ans=N+1;
		if(r!=-1)ans+=(r-l)*2;
		printf("%d\n",ans);
	}
	return 0;
}
