#include<bits/stdc++.h>
using namespace std;
int T,N;
int X[1000000],Y[1000000];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		priority_queue<int>rx,ry;
		priority_queue<int,vector<int>,greater<int> >lx,ly;
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&X[i],&Y[i]);
			lx.push(X[i]),rx.push(X[i]),ly.push(Y[i]),ry.push(Y[i]);
		}
		long long ans=0LL;
		for(int i=0;i<N/2;i++)
		{
			ans+=rx.top();
			ans-=lx.top();
			ans+=ry.top();
			ans-=ly.top();
			rx.pop(),lx.pop(),ry.pop(),ly.pop();
		}
		printf("%lld\n",ans);
	}
	return 0;
}
