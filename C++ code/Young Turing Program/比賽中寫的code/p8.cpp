#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int main()
{
	LL b,x,y,z;scanf("%lld%lld%lld",&x,&y,&z);
	LL UP=7122LL;
	bool ok=false;
	for(b=0;b<=UP;b++)
		if(b*b*b - 2*x*b*b - 2*y*b - 2*z==0) {ok=1;break;}  
	assert(ok);
	printf("%lld %lld %lld\n",b*b,b,1LL);
}
