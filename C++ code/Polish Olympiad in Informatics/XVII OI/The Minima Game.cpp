#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,S[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		int mx=0;
		for(int i=0;i<N;i++)
		{
			S[i]=S[i]-mx;
			if(S[i]>mx)mx=S[i];
		}
		printf("%d\n",mx);
	}
	return 0;
}
