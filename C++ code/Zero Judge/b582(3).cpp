#include<bits/stdc++.h>
using namespace std;
int T,N;
long long X[1000000],Y[1000000];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		priority_queue<long long,vector<long long>,greater<long long> >rx,ry;
		priority_queue<long long>lx,ly;
		long long x,y;
		scanf("%lld%lld",&X[0],&Y[0]);
		x=X[0],y=Y[0];
		for(int i=1;i<N;i++)
		{
			scanf("%lld%lld",&X[i],&Y[i]);
			if(X[i]>=x)
			{
				if(rx.size()>lx.size())lx.push(x),rx.push(X[i]),x=rx.top(),rx.pop();
				else rx.push(X[i]);
			}
			else
			{
				if(lx.size()>rx.size())rx.push(x),lx.push(X[i]),x=lx.top(),lx.pop();
				else lx.push(X[i]);
			}
			if(Y[i]>=y)
			{
				if(ry.size()>ly.size())ly.push(y),ry.push(Y[i]),y=ry.top(),ry.pop();
				else ry.push(Y[i]);
			}
			else
			{
				if(ly.size()>ry.size())ry.push(y),ly.push(Y[i]),y=ly.top(),ly.pop();
				else ly.push(Y[i]);
			}
		}
		long long ans=0LL;
		for(int i=0;i<N;i++)ans+=abs(x-X[i])+abs(y-Y[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
