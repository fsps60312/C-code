#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N,X,Y,C;
LL Get(const LL &t)
{
	const LL D=max(Y-t,1LL),U=min(Y+t,N),L=max(X-t,1LL),R=min(X+t,N);
	LL ans=(U-D+1LL)*(R-L+1LL);
	const LL DD=D-(Y-t),UD=(Y+t)-U,LD=L-(X-t),RD=(X+t)-R;
	assert(DD>=0LL&&UD>=0LL&&LD>=0LL&&RD>=0LL);
//	printf("%lld %lld %lld %lld\n",D,U,L,R);
//	printf("%lld %lld %lld %lld\n",DD,UD,LD,RD);
	LL a,b;
	a=X-L-UD,b=U-Y-LD;
	if(a<0LL)a=0LL;if(b<0LL)b=0LL;
	assert(a==b);
	ans-=(a+1LL)*a/2LL;
	a=R-X-UD,b=U-Y-RD;
	if(a<0LL)a=0LL;if(b<0LL)b=0LL;
	assert(a==b);
	ans-=(a+1LL)*a/2LL;
	a=R-X-DD,b=Y-D-RD;
	if(a<0LL)a=0LL;if(b<0LL)b=0LL;
	assert(a==b);
	ans-=(a+1LL)*a/2LL;
	a=X-L-DD,b=Y-D-LD;
	if(a<0LL)a=0LL;if(b<0LL)b=0LL;
	assert(a==b);
	ans-=(a+1LL)*a/2LL;
	return ans;
}
LL Solve()
{
	LL l=0LL,r=2LL*N,mid;
	assert(Get(2LL*N)==Get(2LL*N-1LL)&&Get(2LL*N)==N*N);
	while(l<r)
	{
		mid=(l+r)>>1;
		if(Get(mid)>=C)r=mid;
		else l=mid+1; 
	}
	return l;
}
int main()
{
	while(scanf("%lld%lld%lld%lld",&N,&X,&Y,&C)==4)
	{
//		for(int i=0;i<N;i++)printf("%d:%lld\n",i,Get(i));puts("");
		printf("%lld\n",Solve());
	}
	return 0;
}
