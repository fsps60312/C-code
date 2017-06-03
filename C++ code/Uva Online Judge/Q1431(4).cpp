#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
LL N,D,E;
void GetLL(LL &ans)
{
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	ans=0LL;
	int cnt=0;
	while(c>='0'&&c<='9')ans=ans*10LL+(c-'0'),cnt++,c=getchar();
	assert(cnt<=20);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		GetLL(N),GetLL(D),GetLL(E);
		if(N==0LL&&D==0LL&&E==0LL)break;
	}
	return 0;
}
