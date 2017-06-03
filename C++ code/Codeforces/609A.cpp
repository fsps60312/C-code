#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,S[100];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		for(int i=N-1;;i--)if((M-=S[i])<=0)
		{
			printf("%d\n",N-i);
			break;
		}
	}
	return 0;
}
