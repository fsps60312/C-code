#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
LL ReadInput()
{
	LL ans=0,n,b;
	if(scanf("%lld%lld",&n,&b)!=2)return -1;
	for(LL i=0,v;i<n;i++)
	{
		scanf("%lld",&v);
		ans=ans*b+v;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(LL a,b;(a=ReadInput())!=-1&&(b=ReadInput())!=-1;)
	{
		puts(a<b?"<":(a==b?"=":">"));
	}
	return 0;
}
