#include<bits/stdc++.h>
using namespace std;
int N,M;
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		double ans=(double)N*M;
		if(N&M&1)ans-=1.0,ans+=sqrt(2.0);
		if(N==1||M==1)ans=2.0*(max(N,M)-1);
		printf("%.2f\n",ans);
	}
	return 0;
}
