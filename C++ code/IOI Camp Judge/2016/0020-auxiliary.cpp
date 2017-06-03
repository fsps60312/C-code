#include<cstdio>
typedef long long LL;
const LL INF=9223372036854775807LL;
int main()
{
	for(int i=2;i<=514;i++)
	{
		LL a=i,now=1LL;
		while(now<=INF/a)now*=a;
		if(now*a>now){printf("a=%lld,now=%lld,now*a=%lld\n",a,now,now*a);}
	}
	return 0;
}
