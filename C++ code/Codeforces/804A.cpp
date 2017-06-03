#include<cstdio>
#include<cassert>
using namespace std;
int N;
int Solve()
{
	assert(N>=1);
	if(N%2==0)return N/2-1;
	else return N/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		printf("%d\n",Solve());
	}
	return 0;
}
